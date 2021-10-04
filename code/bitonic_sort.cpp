
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


template <typename T = int>
struct NOPBitonicSorterStages
{
    std::vector<NOP::SharedAttribute<bool>> stages;
    std::map<int, NOP::SharedPremise> stage_premises;

    std::vector<NOP::SharedAttribute<T>> elements;
    std::vector<NOP::SharedPremise> premises;
    std::vector<NOP::SharedRule> rules;

    std::vector<int> out{};
    size_t size;

    NOPBitonicSorterStages(size_t len) : size{len}
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
