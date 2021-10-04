#pragma once
#include <array>
#include <execution>
#include <map>
#include <random>

#include "libnop/framework.h"

struct OOPArcher
{
    bool bAppleIsReady{false};
    bool bBowIsDrawn{true};

    void ShootApple() { bAppleIsReady = false; };
    void DrawBow() { bBowIsDrawn = true; };
};

struct NOPArcher
{
    NOP::SharedAttribute<bool> atAppleReady{NOP::BuildAttribute(false)};
    NOP::SharedPremise prAppleReady{
        NOP::BuildPremise(atAppleReady, true, std::equal_to<>())};
    NOP::SharedCondition cnShotReady{
        NOP::BuildCondition(CONDITION(*prAppleReady), prAppleReady)};
    NOP::Method mtShootApple { METHOD(atAppleReady->SetValue(false);) };
    NOP::SharedInstigation inShootApple{NOP::BuildInstigation(mtShootApple)};
    NOP::SharedAction acShotReady{NOP::BuildAction(inShootApple)};
    NOP::SharedRule rlDrawBow{NOP::BuildRule(cnShotReady, acShotReady)};
};

struct NOPReferee
{
    NOP::SharedAttribute<bool> atReady{NOP::BuildAttribute(false)};
    NOP::SharedPremise prRefereeReady{
        NOP::BuildPremise(atReady, true, NOP::Equal())};
};

struct NOPTarget
{
    inline static int hitCount{0};
    NOP::SharedAttribute<bool> atReady{NOP::BuildAttribute<bool>(false)};
    NOP::SharedAttribute<bool> atIsShot{NOP::BuildAttribute<bool>(false)};
};

struct NOPMarksman
{
    std::shared_ptr<NOPTarget> Target_;

    NOP::SharedPremise prRefereeReady;
    NOP::SharedPremise prTargetReady{
        NOP::BuildPremise(Target_->atReady, true, NOP::Equal())};
    NOP::SharedPremise prTargetShot{
        NOP::BuildPremise(Target_->atIsShot, true, NOP::Equal())};

    NOP::SharedCondition cnCanShoot{NOP::BuildCondition(
        CONDITION(*prTargetReady && *prRefereeReady && !(*prTargetShot)),
        prTargetReady, prRefereeReady, prTargetShot)};
    NOP::Method mtShootTarget
    {
        METHOD(Target_->atIsShot->SetValue(true); NOPTarget::hitCount++;)
    };
    NOP::SharedInstigation inShootTarget{NOP::BuildInstigation(mtShootTarget)};
    NOP::SharedAction acShootTarget{NOP::BuildAction(inShootTarget)};
    NOP::SharedRule rlShootTarget{NOP::BuildRule(cnCanShoot, acShootTarget)};

    NOPMarksman(NOP::SharedPremise RefereeReady,
                std::shared_ptr<NOPTarget> Target)
        : prRefereeReady{std::move(RefereeReady)}, Target_{std::move(Target)}
    {
    }
};

struct OOPTarget
{
    bool Ready{false};
    bool IsShot{false};
};

struct OOPReferee
{
    bool Ready{false};
};

struct OOPMarksman
{
    std::shared_ptr<OOPReferee> Referee;
    std::shared_ptr<OOPTarget> Target;

    OOPMarksman(std::shared_ptr<OOPReferee> Referee,
                std::shared_ptr<OOPTarget> Target)
        : Referee{std::move(Referee)}, Target{std::move(Target)}
    {
    }

    [[nodiscard]] bool CheckCanShoot() const
    {
        return (Referee->Ready) && (Target->Ready) && !(Target->IsShot);
    }

    void Shoot() const { Target->IsShot = true; }
};

struct OOPSensor
{
    inline static std::atomic<int> counter{0};

    bool isRead{false};
    bool isActivated{false};

    void Read() { isRead = true; }
    void Activate()
    {
        isActivated = true;
        isRead = false;
    }
    void Deactivate() { isActivated = false; }
};

struct NOPSensor: NOP::FBE
{
    inline static std::atomic<int> counter{0};
    NOP::SharedAttribute<bool> atIsRead{NOP::BuildAttribute(false)};
    NOP::SharedAttribute<bool> atIsActivated{NOP::BuildAttribute(false)};
    NOP::SharedPremise prIsActivated{
        NOP::BuildPremise(atIsActivated, true, NOP::Equal())};
    NOP::SharedPremise prIsNotRead{
        NOP::BuildPremise(atIsRead, false, NOP::Equal())};
    NOP::SharedRule rlSensor{NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(prIsActivated, prIsNotRead),
        NOP::BuildAction(NOP::BuildInstigation([&]() {
            this->Read(), this->Deactivate();
            ++NOPSensor::counter;
        })))};
    void Activate() const
    {
        atIsActivated->SetValue(true);
        atIsRead->SetValue(false);
    }
    void Read() const { atIsRead->SetValue(false); }
    void Deactivate() const { atIsActivated->SetValue(false); }

    NOPSensor()
    {
        static int instance{0};
        DEBUG_FBE_NAME(this, fmt::format("NOPSensor{}", instance++))
        DEBUG_ENTITY_FBE(rlSensor)
        DEBUG_ENTITY_FBE(prIsNotRead)
        DEBUG_ENTITY_FBE(prIsActivated)
    }
};

void SwapAttributes(NOP::SharedAttribute<int> at1,
                    NOP::SharedAttribute<int> at2)
{
    // swap values
    auto tmp = at1->GetValue();
    at1->SetValue(at2->GetValue());
    at2->SetValue(tmp);
};

template <typename T = int>
struct NOPBitonicSorterLegacy
{
    std::vector<NOP::SharedAttribute<bool>> stages;
    std::map<int, NOP::SharedPremise> stage_premises;

    std::vector<NOP::SharedAttribute<T>> elements;
    std::vector<NOP::SharedPremise> premises;
    std::vector<NOP::SharedRule> rules;

    std::vector<int> out{};
    size_t size;

    NOPBitonicSorterLegacy(size_t len) : size{len}
    {
        Init();
        out.resize(len);
    }

    void Input(std::vector<T>& input)
    {
        for (size_t i = 0; i < input.size(); i++)
        {
            elements[i]->SetValue(input[i], NOP::NoNotify);
        }
    }

    auto ParallelSort()
    {
        for (const auto& stage : stages)
        {
            stage->SetValue<NOP::Parallel>(true);
            stage->SetValue<NOP::Parallel>(false);
        }
        for (auto i = 0; i < elements.size(); i++)
        {
            out[i] = elements[i]->GetValue();
        }
        return out;
    }

    auto Sort()
    {
        for (const auto& stage : stages)
        {
            stage->SetValue(true);
            stage->SetValue(false);
        }
        for (auto i = 0; i < elements.size(); i++)
        {
            out[i] = elements[i]->GetValue();
        }
        return out;
    }

    void Init()
    {
        elements.clear();
        premises.clear();
        rules.clear();

        for (auto i = 0; i < size; i++)
        {
            elements.push_back(NOP::BuildAttribute(T()));
        }
        const size_t half = size / 2;
        const size_t quarter = size / 4;

        int n = 1;
        int total_stages = 0;
        for (int i = 1; i < log2(size); i++)
        {
            total_stages += n++;
        }

        for (int s = 0; s < total_stages; s++)
        {
            NOP::SharedAttribute<bool> atStage{NOP::BuildAttribute(false)};
            stages.push_back(atStage);
            NOP::SharedPremise prStage =
                NOP::BuildPremise(atStage, true, NOP::Equal());
            stage_premises[s] = prStage;
        }

        int stage = 0;
        for (auto div = half; div > 1; div = div / 2)
        {
            bool reverse{false};
            int internal_stage = stage;
            for (auto start = 0; start < size; start += size / div)
            {
                internal_stage = stage;
                for (auto step = half / div; step > 0; step = step / 2)
                {
                    for (auto i = 0; i < step; i++)
                    {
                        for (auto j = 0; j < size / div; j = j + 2 * step)
                        {
                            auto x = start + i + j;
                            auto y = start + i + j + step;
                            auto& at1 = elements[x];
                            auto& at2 = elements[y];
                            NOP::SharedPremise pr;
                            if (reverse)
                            {
                                pr = NOP::BuildPremise(at1, at2, NOP::Less());
                            }
                            else
                            {
                                pr =
                                    NOP::BuildPremise(at1, at2, NOP::Greater());
                            }
                            premises.push_back(pr);

                            rules.push_back(NOP::BuildRule(
                                NOP::BuildCondition<NOP::Conjunction>(
                                    pr, stage_premises[internal_stage]),
                                NOP::BuildAction(NOP::BuildInstigation(
                                    METHOD(SwapAttributes(at1, at2);)))));
                        }
                    }
                    internal_stage++;
                }
                reverse = !reverse;
            }
            stage += (internal_stage - stage);
        }

        int sort_stages = log2(size);
        int curr_stage = total_stages;
        for (int s = 0; s < sort_stages; s++)
        {
            NOP::SharedAttribute<bool> atStage{NOP::BuildAttribute(false)};
            stages.push_back(atStage);
            NOP::SharedPremise prStage =
                NOP::BuildPremise(atStage, true, NOP::Equal());
            stage_premises[curr_stage + s] = prStage;
        }

        stage = curr_stage;
        for (auto start = 0; start < size; start += size)
        {
            for (auto step = half; step > 0; step = step / 2)
            {
                for (auto i = 0; i < step; i++)
                {
                    for (auto j = 0; j < size; j = j + 2 * step)
                    {
                        auto x = start + i + j;
                        auto y = start + i + j + step;
                        auto& at1 = elements[x];
                        auto& at2 = elements[y];
                        NOP::SharedPremise pr =
                            NOP::BuildPremise(at1, at2, NOP::Greater());
                        premises.push_back(pr);
                        rules.push_back(NOP::BuildRule(
                            NOP::BuildCondition<NOP::Conjunction>(
                                pr, stage_premises[stage]),
                            NOP::BuildAction(NOP::BuildInstigation(
                                METHOD(SwapAttributes(at1, at2);)))));
                    }
                }
                stage++;
            }
        }
    }
};

template <typename T = int>
struct NOPBitonicSorter
{
    std::map<int, std::vector<NOP::SharedAttribute<T>>> elements;
    std::vector<NOP::SharedPremise> premises;
    std::vector<NOP::SharedRule> rules;
    int stages{0};
    std::vector<T> out;
    size_t size;
    std::vector<int> indexes;

    NOPBitonicSorter(size_t len) : size{len}
    {
        out.resize(size);
        indexes.resize(len);
        std::iota(indexes.begin(), indexes.end(), 0);

        Init();
    }

    auto Sort(const std::vector<T>& input)
    {
        for (auto i = 0; i < input.size(); i++)
        {
            elements[0][i]->SetValue(input[i], (i % 2));
        }
        return out;
    }

    auto ParallelSort(const std::vector<T>& input)
    {
        std::for_each(
            std::execution::par_unseq, indexes.begin(), indexes.end(),
            [&](int i) {
                elements[0][i]->template SetValue<NOP::ReNotify>(input[i]);
            });
        return out;
    }

    void MoveAttributes(NOP::SharedAttribute<T>& at1,
                        NOP::SharedAttribute<T>& at2, int stage, int x, int y)
    {
        if (stage < stages - 1)
        {
            elements[stage + 1][x]->template SetValue<NOP::ReNotify>(
                at1->GetValue());
            elements[stage + 1][y]->template SetValue<NOP::ReNotify>(
                at2->GetValue());
        }
        else
        {
            out[x] = at1->GetValue();
            out[y] = at2->GetValue();
        }
    }

    void CreateComparatorFBE(int x, int y, int stage, bool reverse = false)
    {
        auto& at1 = elements[stage][x];
        auto& at2 = elements[stage][y];
        NOP::SharedPremise pr1;
        NOP::SharedPremise pr2;
        if (!reverse)
        {
            pr1 = NOP::BuildPremise(at2, at1, NOP::Greater());
            pr2 = NOP::BuildPremise(at2, at1, NOP::LessEqual());
        }
        else
        {
            pr2 = NOP::BuildPremise(at2, at1, NOP::Greater());
            pr1 = NOP::BuildPremise(at2, at1, NOP::LessEqual());
        }
        premises.push_back(pr1);
        premises.push_back(pr2);

        // Rule to move
        rules.push_back(NOP::BuildRule(
            NOP::BuildCondition(CONDITION(*pr1), pr1),
            NOP::BuildAction(NOP::BuildInstigation([&, stage, x, y]() {
                MoveAttributes(at1, at2, stage, x, y);
            }))));
        // Rule to swap
        rules.push_back(NOP::BuildRule(
            NOP::BuildCondition(CONDITION(*pr2), pr2),
            NOP::BuildAction(NOP::BuildInstigation([&, stage, x, y]() {
                MoveAttributes(at1, at2, stage, y, x);
            }))));
    }

    void Init()
    {
        elements.clear();
        premises.clear();
        rules.clear();

        const size_t half = size / 2;
        const size_t quarter = size / 4;

        int n = 1;
        for (int i = 1; i < log2(size); i++)
        {
            stages += n++;
        }
        for (int s = 0; s < stages; s++)
        {
            elements[s].resize(size);
            for (int i = 0; i < size; i++)
            {
                elements[s][i] = NOP::BuildAttribute(T());
            }
        }

        int stage = 0;
        for (auto div = half; div > 1; div = div / 2)
        {
            bool reverse{false};
            int internal_stage = stage;
            for (auto start = 0; start < size; start += size / div)
            {
                internal_stage = stage;
                for (auto step = half / div; step > 0; step = step / 2)
                {
                    for (auto i = 0; i < step; i++)
                    {
                        for (auto j = 0; j < size / div; j = j + 2 * step)
                        {
                            int x = start + i + j;
                            int y = start + i + j + step;
                            CreateComparatorFBE(x, y, internal_stage, reverse);
                        }
                    }
                    internal_stage++;
                }
                reverse = !reverse;
            }
            stage += (internal_stage - stage);
        }

        int sort_stages = log2(size);
        int curr_stage = stages;
        for (int s = 0; s < sort_stages; s++)
        {
            stages++;
            elements[curr_stage + s].resize(size);
            for (int i = 0; i < size; i++)
            {
                elements[curr_stage + s][i] = NOP::BuildAttribute(T());
            }
        }

        stage = curr_stage;
        for (auto start = 0; start < size; start += size)
        {
            for (auto step = half; step > 0; step = step / 2)
            {
                for (auto i = 0; i < step; i++)
                {
                    for (auto j = 0; j < size; j = j + 2 * step)
                    {
                        auto x = start + i + j;
                        auto y = start + i + j + step;
                        CreateComparatorFBE(x, y, stage);
                    }
                }
                stage++;
            }
        }
    }
};

/* C++ Program for Bitonic Sort. Note that this program
   works only when size of input is a power of 2. */

/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir)
{
    if (dir == (a[i] > a[j])) std::swap(a[i], a[j]);
}

/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) compAndSwap(a, i, i + k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

/* This function first produces a bitonic sequence by recursively
    sorting its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order */
void bitonicSort(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);

        // sort in descending order since dir here is 0
        bitonicSort(a, low + k, k, 0);

        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(a, low, cnt, dir);
    }
}

/* Caller of bitonicSort for sorting the entire array of
   length N in ASCENDING order */
void sort(int a[], int N, int up) { bitonicSort(a, 0, N, up); }

inline auto GetRandomVector(size_t size)
{
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist{1, 52};

    auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

    std::vector<int> vec(size);
    generate(begin(vec), end(vec), gen);

    return vec;
}
