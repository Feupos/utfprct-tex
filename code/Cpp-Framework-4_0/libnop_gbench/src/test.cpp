#include "test.h"
#ifdef LIBNOP_BENCHMARK_RANDOMFOREST_ENABLE
#include "random_forest_vivado.h"
#include "test_random_forest.h"
#endif
#include <benchmark/benchmark.h>

#include <chrono>
#include <random>
#include <vector>

#include "gtest/gtest.h"
#ifdef LIBNOP_FW2_TEST_ENABLE
#include "test_fw2.h"
#endif

#define TEST_RANGE             \
    Args({10, 10})             \
        ->Args({100, 100})     \
        ->Args({1000, 1000})   \
        ->Args({10000, 10000}) \
        ->Args({10000, 10})    \
        ->Args({10000, 100})   \
        ->Args({10000, 1000})
#define TEST_ELEMS             \
    Args({100, 100})           \
        ->Args({1000, 1000})   \
        ->Args({10000, 10000}) \
        ->Args({100000, 100000})
#define TEST_RATE               \
    Args({100000, 1})           \
        ->Args({100000, 10})    \
        ->Args({100000, 100})   \
        ->Args({100000, 1000})  \
        ->Args({100000, 10000}) \
        ->Args({100000, 100000})

#ifdef LIBNOP_BENCHMARK_SENSOR_ENABLE

static void BM_FW4Sensor(benchmark::State& state)
{
    std::vector<std::shared_ptr<NOPSensor>> sensors;
    for (int i = 0; i < state.range(0); i++)
    {
        sensors.push_back(std::make_shared<NOPSensor>());
    }

    for (auto _ : state)
    {
        NOPSensor::counter = 0;
        for (int i = 0; i < state.range(1); i++)
        {
            sensors[i]->Activate();
        }
    }
}

static void BM_FW4SensorMemory(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<std::shared_ptr<NOPSensor>> sensors;
        for (int i = 0; i < state.range(0); i++)
        {
            sensors.push_back(std::make_shared<NOPSensor>());
        }
    }
}

static void BM_OOPSensor(benchmark::State& state)
{
    std::vector<std::shared_ptr<OOPSensor>> sensors;
    for (int i = 0; i < state.range(0); i++)
    {
        sensors.push_back(std::make_shared<OOPSensor>());
    }

    for (auto _ : state)
    {
        for (int i = 0; i < state.range(1); i++)
        {
            sensors[i]->Activate();
        }

        for (auto& sensor : sensors)
        {
            if (sensor->isActivated && !sensor->isRead)
            {
                sensor->Read();
                sensor->Deactivate();
                ++OOPSensor::counter;
            }
        }
        ASSERT_EQ(OOPSensor::counter, state.range(1));
        OOPSensor::counter = 0;
    }
}

static void BM_OOPSensorMemory(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<std::shared_ptr<OOPSensor>> sensors;
        for (int i = 0; i < state.range(0); i++)
        {
            sensors.push_back(std::make_shared<OOPSensor>());
        }
    }
}

BENCHMARK(BM_FW4Sensor)->TEST_RATE;
BENCHMARK(BM_OOPSensor)->TEST_RATE;

/*BENCHMARK(BM_FW4Sensor)->TEST_ELEMS;
BENCHMARK(BM_OOPSensor)->TEST_ELEMS;*/

#endif

#ifdef LIBNOP_FW2_TEST_ENABLE
static void BM_FW2Marksman(benchmark::State& state)
{
    MarksmanApp main((int)state.range(0));

    for (auto _ : state)
    {
        main.startApplication();
    }
}

static void BM_FW2Sensor(benchmark::State& state)
{
    SensorApp sensorApp(state.range(0));

    for (auto _ : state)
    {
        for (int i = 0; i < state.range(1); i++)
        {
            sensorApp.sensors[i]->Activate();
        }
        ASSERT_EQ(NOP2Sensor::counter, state.range(1));
        NOP2Sensor::counter = 0;
    }
}

static void BM_FW2SensorMemory(benchmark::State& state)
{
    // for (auto _ : state)
    {
        SensorApp sensorApp(state.range(0));
    }
}
// BENCHMARK(BM_FW2Marksman)->Range(0x1000, 0x1000 << 3);
// BENCHMARK(BM_FW2Sensor)->TEST_ELEMS;
#ifdef LIBNOP_BENCHMARK_SENSOR_ENABLE
BENCHMARK(BM_FW2Sensor)->TEST_RATE;
#endif

#endif

#ifdef LIBNOP_BENCHMARK_BITONIC_ENABLE
static void BM_NOPBitonic(benchmark::State& state)
{
    NOPBitonicSorter<int> sorter(state.range(0));

    for (auto _ : state)
    {
        std::vector<int> input = GetRandomVector(
            state.range(0));  // { 35, 16, 31, 4, 4, 31, 17, 16 };
        auto out = sorter.Sort(input);
        /*ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
        ASSERT_FALSE(std::all_of(out.begin(), out.end(), [](int i) { return i ==
        0; }));*/
    }
}

static void BM_NOPBitonicOld(benchmark::State& state)
{
    NOPBitonicSorterLegacy<int> sorter(state.range(0));

    for (auto _ : state)
    {
        std::vector<int> input = GetRandomVector(
            state.range(0));  // { 35, 16, 31, 4, 4, 31, 17, 16 };
        sorter.Input(input);
        auto out = sorter.Sort();
        /*ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
        ASSERT_FALSE(std::all_of(out.begin(), out.end(), [](int i) { return i ==
        0; }));*/
    }
}

static void BM_NOPBitonicOldParallel(benchmark::State& state)
{
    NOPBitonicSorterLegacy<int> sorter(state.range(0));

    for (auto _ : state)
    {
        std::vector<int> input = GetRandomVector(
            state.range(0));  // { 35, 16, 31, 4, 4, 31, 17, 16 };
        sorter.Input(input);
        auto out = sorter.ParallelSort();
        /*ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
        ASSERT_FALSE(
            std::all_of(out.begin(), out.end(), [](int i) { return i == 0;
        }));*/
    }
}

static void BM_NOPBitonicParallel(benchmark::State& state)
{
    NOPBitonicSorter<int> sorter(state.range(0));

    for (auto _ : state)
    {
        const std::vector<int> input = GetRandomVector(
            state.range(0));  // { 35, 16, 31, 4, 4, 31, 17, 16 };

        auto out = sorter.ParallelSort(input);
        /*ASSERT_TRUE(std::is_sorted(out.begin(), out.end()));
        ASSERT_FALSE(std::all_of(out.begin(), out.end(), [](int i) { return i ==
        0; }));*/
    }
}

static void BM_NOPBitonicMemory(benchmark::State& state)
{
    for (auto _ : state)
    {
        NOPBitonicSorter<int> sorter(state.range(0));
        benchmark::DoNotOptimize(sorter);
    }
}

static void BM_NOPBitonicOldMemory(benchmark::State& state)
{
    for (auto _ : state)
    {
        NOPBitonicSorterLegacy<int> sorter(state.range(0));
        benchmark::DoNotOptimize(sorter);
    }
}

static void BM_OOPBitonic(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::vector<int> input = GetRandomVector(
            state.range(0));  // { 35, 16, 31, 4, 4, 31, 17, 16 };

        sort(input.data(), input.size(), 1);
        /*ASSERT_TRUE(std::is_sorted(input.begin(), input.end()));
        ASSERT_FALSE(std::all_of(input.begin(), input.end(), [](int i) { return
        i == 0; }));*/
    }
}
/*
BENCHMARK(BM_OOPBitonic)->RangeMultiplier(2)->Range(8, 8 << 9);
BENCHMARK(BM_NOPBitonicOld)->RangeMultiplier(2)->Range(8, 8 << 9);
BENCHMARK(BM_NOPBitonicOldParallel)->RangeMultiplier(2)->Range(8, 8 << 9);
BENCHMARK(BM_NOPBitonicParallel)->RangeMultiplier(2)->Range(8, 8 << 3);
BENCHMARK(BM_NOPBitonic)->RangeMultiplier(2)->Range(8, 8 << 3);
*/
//BENCHMARK(BM_NOPBitonicOld)->Arg(4096)->MinTime(5);
//BENCHMARK(BM_NOPBitonicOldParallel)->Arg(4096)->MinTime(5);

// BENCHMARK(BM_NOPBitonicMemory)->Arg(1024)->MinTime(5);
// BENCHMARK(BM_NOPBitonicOldMemory)->Arg(1024)->MinTime(5);

// Memory benchmark
// BENCHMARK(BM_OOPSensorMemory)->Args({ 10000, 0 })->MinTime(10);
// BENCHMARK(BM_FW2SensorMemory)->Args({ 10000, 0 })->MinTime(10);
// BENCHMARK(BM_FW4SensorMemory)->Args({ 10000, 0 })->MinTime(10);

#endif

#ifdef LIBNOP_BENCHMARK_RANDOMFOREST_ENABLE

#define RANDOM_FOREST_MACRO(n)                                                \
    static void BM_RandomForest##n(benchmark::State& state)                   \
    {                                                                         \
        Forest##n classifier{};                                               \
        for (auto _ : state)                                                  \
        {                                                                     \
            for (auto& item : test_data)                                      \
            {                                                                 \
                benchmark::DoNotOptimize(                                     \
                    classifier.Classify(item[0], item[1], item[2], item[3])); \
            }                                                                 \
        }                                                                     \
    }                                                                         \
    BENCHMARK(BM_RandomForest##n)

#define RANDOM_FOREST_MACRO_PARALLEL(n)                                       \
    static void BM_RandomForestParallel##n(benchmark::State& state)           \
    {                                                                         \
        ParallelForest##n classifier{};                                       \
        for (auto _ : state)                                                  \
        {                                                                     \
            for (auto& item : test_data)                                      \
            {                                                                 \
                benchmark::DoNotOptimize(                                     \
                    classifier.Classify(item[0], item[1], item[2], item[3])); \
            }                                                                 \
        }                                                                     \
    }                                                                         \
    BENCHMARK(BM_RandomForestParallel##n)
/*
RANDOM_FOREST_MACRO(1);
RANDOM_FOREST_MACRO(10);
RANDOM_FOREST_MACRO(20);
RANDOM_FOREST_MACRO(50);
RANDOM_FOREST_MACRO(100);
RANDOM_FOREST_MACRO_PARALLEL(1);
RANDOM_FOREST_MACRO_PARALLEL(10);
RANDOM_FOREST_MACRO_PARALLEL(20);
RANDOM_FOREST_MACRO_PARALLEL(50);
RANDOM_FOREST_MACRO_PARALLEL(100);*/

RANDOM_FOREST_MACRO_PARALLEL(100)->MinTime(5);

#define RANDOM_FOREST_VIVADO_MACRO(n)                               \
    static void BM_RandomForestVivado##n(benchmark::State& state)   \
    {                                                               \
        for (auto _ : state)                                        \
        {                                                           \
            for (auto& item : test_data)                            \
            {                                                       \
                int test[4] = {item[0], item[1], item[2], item[3]}; \
                benchmark::DoNotOptimize(                           \
                    VIVADO##n::randomForestClassifier(test));       \
            }                                                       \
        }                                                           \
    }                                                               \
    BENCHMARK(BM_RandomForestVivado##n);
/*
RANDOM_FOREST_VIVADO_MACRO(1);
RANDOM_FOREST_VIVADO_MACRO(10);
RANDOM_FOREST_VIVADO_MACRO(20);
RANDOM_FOREST_VIVADO_MACRO(50);
RANDOM_FOREST_VIVADO_MACRO(100);
*/
#endif

// Run the benchmark
BENCHMARK_MAIN();
