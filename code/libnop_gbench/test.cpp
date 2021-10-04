#include "gtest/gtest.h"

#include <benchmark/benchmark.h>
#include <vector>
#include <random>

#include "test.h"

static const int64_t TEST_ELEMS{ 10 };
static const int64_t PERCENT_VAL{ 0 };

void NOPArcherTest(std::vector<NOPArcher>& archers, std::vector<int>& input)
{
    for (const auto& val : input)
    {
        archers[val].atAppleReady->SetValue(true);
    }
}

static void BM_NOPArcher(benchmark::State& state) {
    std::vector<NOPArcher> archers(state.range(0));
    std::vector<int> input;
    auto gen = std::bind(std::uniform_int_distribution<>(
        0, static_cast<int>(archers.size()-1)), std::default_random_engine());
    for (int i = 0; i < state.range(1); ++i) {
        input.push_back(gen());
    }
    for (auto _ : state)
    {
        NOPArcherTest(archers, input);
    }
}

void OOPArcherTest(std::vector<OOPArcher>& archers, std::vector<int>& input)
{
    for (const auto& val : input)
    {
        archers[val].bAppleIsReady = true;

        for (auto& archer : archers)
        {
            if (archer.bAppleIsReady)
            {
                archer.ShootApple();
            }
        }
    }
}

static void BM_OOPArcher(benchmark::State& state) {
    std::vector<OOPArcher> archers(state.range(0));
    std::vector<int> input;
    auto gen = std::bind(std::uniform_int_distribution<>(0, static_cast<int>(archers.size()-1)), std::default_random_engine());
    for (int i = 0; i < state.range(1); ++i) {
        input.push_back(gen());
    }
    for (auto _ : state)
    {
        OOPArcherTest(archers, input);
    }
}

static void BM_NOPMarksman(benchmark::State& state) {
    std::vector<std::shared_ptr<NOPMarksman>> marksmans;
    std::vector<std::shared_ptr<NOPTarget>> targets;
    std::shared_ptr<NOPReferee> referee = std::make_shared<NOPReferee>();

    for (int i = 0; i < state.range(0); i++)
    {
        auto target = std::make_shared<NOPTarget>();
        marksmans.push_back(std::make_shared<NOPMarksman>(referee, target));
        targets.push_back(target);
    }

    for (auto _ : state)
    {
        for (auto& it : targets)
        {
            it->atReady->SetValue(true);
        }
        referee->atReady->SetValue(true);
    }
}

static void BM_OOPMarksman(benchmark::State& state) {
    std::vector<std::shared_ptr<OOPMarksman>> marksmans;
    std::vector<std::shared_ptr<OOPTarget>> targets;
    std::shared_ptr<OOPReferee> referee = std::make_shared<OOPReferee>();
    for (int i = 0; i < state.range(0); i++)
    {
        auto target = std::make_shared<OOPTarget>();
        marksmans.push_back(std::make_shared<OOPMarksman>(referee, target));
        targets.push_back(target);
    }

    for (auto _ : state)
    {
        for (auto& it : targets)
        {
            it->Ready = true;
        }
        referee->Ready = true;
        for(auto& it : marksmans)
        {
            if(it->CheckCanShoot())
            {
                it->Shoot();
            }
        }
    }
}

// Register the function as a benchmark
//BENCHMARK(BM_NOPArcher)->Args({ TEST_ELEMS, TEST_ITER });//, PERCENT_VAL });
//BENCHMARK(BM_OOPArcher)->Args({ TEST_ELEMS, TEST_ITER });//, PERCENT_VAL });

BENCHMARK(BM_NOPMarksman)->Range(0x100, 0x100 << 4);
BENCHMARK(BM_OOPMarksman)->Range(0x100, 0x100 << 4);

// Run the benchmark
BENCHMARK_MAIN();