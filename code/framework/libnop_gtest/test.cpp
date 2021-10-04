#include <atomic>
#include <queue>
#include <random>
#include <thread>

#include "gtest/gtest.h"
#include "libnop/framework.h"

TEST(Attribute, Int)
{
    const int val{123456};
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(val);
    EXPECT_EQ(at1->GetValue(), val);
}

TEST(Attribute, Bool)
{
    const bool val{true};
    NOP::SharedAttribute<bool> at1 = NOP::BuildAttribute(val);
    EXPECT_EQ(at1->GetValue(), val);
}

TEST(Attribute, Class)
{
    class Rectangle
    {
        int width, height;

       public:
        Rectangle(int w, int h) : width{w}, height{h} {};
        inline bool operator==(Rectangle i) const
        {
            return (width == i.width) && (height == i.height);
        }
        inline bool operator!=(Rectangle i) const
        {
            return (width != i.width) || (height != i.height);
        }
    };

    const Rectangle val1{1, 2};
    NOP::SharedAttribute<Rectangle> at1 = NOP::BuildAttribute(val1);
    EXPECT_EQ(at1->GetValue(), val1);

    const Rectangle val2{3, 4};
    NOP::SharedAttribute<Rectangle> at2 = NOP::BuildAttribute(val2);
    EXPECT_NE(at1->GetValue(), at2->GetValue());

    at2->SetValue(val1);
    EXPECT_EQ(at1->GetValue(), at2->GetValue());
}

TEST(Attribute, String)
{
    const std::string val{"test"};
    NOP::SharedAttribute<std::string> at1 = NOP::BuildAttribute(val);
    EXPECT_EQ(at1->GetValue(), val);
}

TEST(Premise, Simple)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);

    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());

    // On initialization should not be approved
    EXPECT_FALSE(pr1->Approved());
    at1->SetValue(1);
    EXPECT_FALSE(pr1->Approved());
    at2->SetValue(1);
    EXPECT_TRUE(pr1->Approved());
}

TEST(Premise, Custom)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(1);
    NOP::SharedPremise prDouble = NOP::BuildPremise(
        at1, at2, [](auto a1, auto a2) { return a1 == 2 * a2; });

    // On initialization should not be approved
    EXPECT_FALSE(prDouble->Approved());
    at1->SetValue(2 * at2->GetValue());
    EXPECT_TRUE(prDouble->Approved());
    at1->SetValue(0);
    EXPECT_FALSE(prDouble->Approved());
}

TEST(Condition, Conjunction)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 =
        NOP::BuildCondition(CONDITION(*pr1 && *pr2), pr1, pr2);

    // On initialization should not be approved
    EXPECT_FALSE(cn1->Approved());
    at1->SetValue(1);
    at2->SetValue(1);
    EXPECT_FALSE(cn1->Approved());
    at3->SetValue(1);
    at4->SetValue(1);
    EXPECT_TRUE(cn1->Approved());
}

TEST(Condition, Disjunction)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 =
        NOP::BuildCondition(CONDITION(*pr1 || *pr2), pr1, pr2);

    // On initialization should not be approved
    EXPECT_FALSE(cn1->Approved());
    at1->SetValue(1);
    at2->SetValue(1);
    EXPECT_TRUE(cn1->Approved());
    at3->SetValue(1);
    at4->SetValue(1);
    EXPECT_TRUE(cn1->Approved());
    at1->SetValue(-1);
    EXPECT_TRUE(cn1->Approved());
    at3->SetValue(-1);
    EXPECT_FALSE(cn1->Approved());
}

TEST(Condition, SubCondition)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    NOP::SharedCondition cn2 =
        NOP::BuildCondition(CONDITION(*pr2 && *cn1), pr2, cn1);

    // On initialization should not be approved
    EXPECT_FALSE(cn2->Approved());
    at1->SetValue(1);
    at2->SetValue(1);
    EXPECT_TRUE(cn1->Approved());
    EXPECT_FALSE(cn2->Approved());
    at3->SetValue(1);
    at4->SetValue(1);
    EXPECT_TRUE(cn2->Approved());
}

TEST(Condition, MasterRule)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    NOP::SharedRule rl1 =
        NOP::BuildRule(cn1, NOP::BuildAction(NOP::BuildInstigation()));

    NOP::SharedCondition cn2 =
        NOP::BuildCondition(CONDITION(*pr2 && *rl1), pr2, rl1);

    EXPECT_FALSE(cn2->Approved());
    at1->SetValue(1);
    at2->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(rl1->Approved());
    EXPECT_FALSE(cn2->Approved());
    at3->SetValue(1);
    at4->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(cn2->Approved());
}

TEST(Complete, Basic)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::Scheduler::Instance().FinishAll();

    // Nothing should be approved upon initialization
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();

    // Nothing should be approved yet
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    at2->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();

    // Everything should be approved
    EXPECT_TRUE(pr1->Approved());
    EXPECT_TRUE(cn1->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 1);

    at2->SetValue(10);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    at1->SetValue(10);
    NOP::Scheduler::Instance().FinishAll();

    // Everything should be approved
    EXPECT_TRUE(pr1->Approved());
    EXPECT_TRUE(cn1->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 2);
}

#ifdef LIBNOP_LOG_ENABLE
TEST(Complete, Logger)
{
    NOP::Logger::Instance().SetLogFileName("test.log");
    NOP::Logger::Instance().SetLogFileName("test2.log");
    NOP::Logger::Instance().SetLogFileName("test.log");

    struct Test : NOP::FBE
    {
        explicit Test(const std::string_view name) : FBE(name) {}
        NOP::SharedAttribute<int> at1 =
            NOP::BuildAttributeNamed("at1", this, -1);
        // Build without parent
        NOP::SharedAttribute<int> at2 =
            NOP::BuildAttributeNamed("at2", nullptr, -2);
        NOP::SharedPremise pr1 =
            NOP::BuildPremiseNamed("pr1", this, at1, at2, NOP::Equal());
        NOP::SharedCondition cn1 =
            NOP::BuildConditionNamed("cn1", this, CONDITION(*pr1), pr1);

        std::atomic<int> executionCounter{0};
        NOP::Method mt = [&] { executionCounter++; };
        NOP::SharedInstigation in1 =
            NOP::BuildInstigationNamed("in1", this, mt);
        NOP::SharedAction ac1 = NOP::BuildActionNamed("ac1", this, in1);

        NOP::SharedRule rl1 = NOP::BuildRuleNamed("rl1", this, cn1, ac1);
    };

    Test test{"TestFBE"};

    NOP::Scheduler::Instance().FinishAll();

    // Nothing should be approved upon initialization
    EXPECT_FALSE(test.pr1->Approved());
    EXPECT_FALSE(test.cn1->Approved());
    EXPECT_FALSE(test.rl1->Approved());

    test.at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();

    // Nothing should be approved yet
    EXPECT_FALSE(test.pr1->Approved());
    EXPECT_FALSE(test.cn1->Approved());
    EXPECT_FALSE(test.rl1->Approved());

    test.at2->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();

    // Everything should be approved
    EXPECT_TRUE(test.pr1->Approved());
    EXPECT_TRUE(test.cn1->Approved());
    EXPECT_TRUE(test.rl1->Approved());
    EXPECT_EQ(test.executionCounter, 1);

    test.at2->SetValue(10);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_FALSE(test.pr1->Approved());
    EXPECT_FALSE(test.cn1->Approved());
    EXPECT_FALSE(test.rl1->Approved());

    test.at1->SetValue(10);
    NOP::Scheduler::Instance().FinishAll();

    // Everything should be approved
    EXPECT_TRUE(test.pr1->Approved());
    EXPECT_TRUE(test.cn1->Approved());
    EXPECT_TRUE(test.rl1->Approved());
    EXPECT_EQ(test.executionCounter, 2);
}
#endif

TEST(Complete, MultipleCycles)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    for (int i = 1; i <= INT16_MAX; i++)
    {
        at1->SetValue(1);
        NOP::Scheduler::Instance().FinishAll();

        at1->SetValue(-1);
        EXPECT_EQ(executionCounter, i);
    }

    EXPECT_EQ(executionCounter, INT16_MAX);
}

TEST(Counter, Default)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::Scheduler::Instance().FinishAll();

    constexpr int executions{INT8_MAX};
    for (int i = 0; i < executions; i++)
    {
        at2->SetValue(-1);
        at2->SetValue(1);
        NOP::Scheduler::Instance().FinishAll();
    }
    EXPECT_EQ(executionCounter, executions);
}

TEST(Complete, InitialStatesDisapproved)
{
    NOP::Scheduler& scheduler = NOP::Scheduler::Instance();

    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    scheduler.FinishAll();

    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_EQ(executionCounter, 0);
}

TEST(Complete, InitialStatesApproved)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    NOP::Scheduler::Instance().FinishAll();

    EXPECT_TRUE(pr1->Approved());
    EXPECT_TRUE(cn1->Approved());
    EXPECT_TRUE(rl1->Approved());

    EXPECT_EQ(executionCounter, 1);
}

TEST(Complete, SharedEntities1)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    // clone methods
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac2);

    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 2);
}

TEST(Complete, SharedEntities2)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    NOP::SharedCondition cn2 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    // clone methods
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn2, ac1);

    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 2);
}

TEST(Complete, Renotification)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    std::atomic<int> executionCounter{0};
    NOP::SharedInstigation in1 =
        NOP::BuildInstigation([&] { executionCounter++; });
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at1->SetValue(1, false);
    at2->SetValue(1, false);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 1);

    at2->SetValue(1, true);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_EQ(executionCounter, 2);

    at2->SetValue(1, true);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_EQ(executionCounter, 3);
}

TEST(Complete, RecursiveRule)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(0);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, std::less<>());
    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);
    int executionCounter{0};
    auto test = [&]()
    {
        executionCounter++;
        at1->SetValue<NOP::ReNotify>(at1->GetValue() + 1);
    };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(test);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at2->SetValue(10);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 10);
}
TEST(Condition, Composition)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise(at3, at4, NOP::Equal());

    NOP::SharedAttribute<int> at5 = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> at6 = NOP::BuildAttribute<int>(0);
    NOP::SharedPremise pr3 = NOP::BuildPremise(at5, at6, NOP::Equal());

    NOP::SharedCondition cn1 =
        NOP::BuildCondition(CONDITION((*pr1 || *pr2) && !*pr3), pr1, pr2, pr3);

    at1->SetValue(1);
    at2->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(pr1->Approved());
    EXPECT_FALSE(pr2->Approved());
    EXPECT_TRUE(pr3->Approved());
    EXPECT_FALSE(cn1->Approved());

    at5->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_FALSE(pr3->Approved());
    EXPECT_TRUE(cn1->Approved());

    at2->SetValue(-1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());

    at3->SetValue(1);
    at4->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(pr2->Approved());
    EXPECT_TRUE(cn1->Approved());
}
TEST(Flag, Exclusive)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(0);

    NOP::SharedAttribute<bool> atExclusive = NOP::BuildAttribute(false);

    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());
    NOP::SharedPremise pr2 = NOP::BuildPremise(at2, 2, NOP::Equal());

    NOP::SharedPremise prExclusive =
        NOP::BuildPremise(atExclusive, true, NOP::Equal());

    NOP::SharedCondition cn1 =
        NOP::BuildCondition<NOP::Conjunction>(pr1, prExclusive);
    NOP::SharedCondition cn2 =
        NOP::BuildCondition<NOP::Conjunction>(pr2, prExclusive);

    std::atomic<int> executionCounter1{0};
    auto test1 = [&]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        EXPECT_TRUE(atExclusive->GetValue());
        atExclusive->SetValue<NOP::Exclusive>(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        ++executionCounter1;
        at1->SetValue(0);
        atExclusive->SetValue<NOP::Exclusive>(true);
    };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(test1);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    std::atomic<int> executionCounter2{0};
    auto test2 = [&]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        EXPECT_TRUE(atExclusive->GetValue());
        atExclusive->SetValue<NOP::Exclusive>(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++executionCounter2;
        at2->SetValue(0);
        atExclusive->SetValue<NOP::Exclusive>(true);
    };

    NOP::SharedInstigation in2 = NOP::BuildInstigation(test2);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);
    NOP::SharedRule rl2 = NOP::BuildRule(cn2, ac2);

    atExclusive->SetValue<NOP::Exclusive>(true);
    {
        std::thread t1{[&]() { at1->SetValue<NOP::Exclusive>(1); }};
        std::thread t2{[&]() { at2->SetValue<NOP::Exclusive>(2); }};
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        t1.join();
        t2.join();
    }

    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter1, 1);
    EXPECT_EQ(executionCounter2, 1);
}

TEST(Example, Alarm)
{
    struct Alarm
    {
        int alarmCount{0};

        NOP::SharedAttribute<bool> atState{NOP::BuildAttribute<bool>(false)};
        NOP::SharedPremise prAlarm{
            NOP::BuildPremise(atState, true, NOP::Equal())};
        NOP::SharedCondition cnAlarm{
            NOP::BuildCondition(CONDITION(*prAlarm), prAlarm)};
        NOP::Method mtNotify { METHOD(alarmCount++;) };
        NOP::SharedInstigation inAlarm{NOP::BuildInstigation(mtNotify)};
        NOP::SharedAction acAlarm{NOP::BuildAction(inAlarm)};
        NOP::SharedRule rlAlarm{NOP::BuildRule(cnAlarm, acAlarm)};
    };

    Alarm al1;
    Alarm al2;

    for (int i = 0; i < 10; i++)
    {
        al1.atState->SetValue(!al1.atState->GetValue());
        al2.atState->SetValue<NOP::ReNotify>(true);
        NOP::Scheduler::Instance().FinishAll();
    }
    EXPECT_EQ(al1.alarmCount, 5);
    EXPECT_EQ(al2.alarmCount, 10);
}

TEST(Example, AlarmSimplified)
{
    struct Alarm
    {
        int alarmCount{0};

        NOP::SharedAttribute<bool> atState{NOP::BuildAttribute<bool>(false)};
        NOP::SharedPremise prAlarm{
            NOP::BuildPremise(atState, true, NOP::Equal())};
        NOP::SharedRule rlAlarm
        {
            NOP::BuildRule(
                NOP::BuildCondition(CONDITION(*prAlarm), prAlarm),
                NOP::BuildAction(NOP::BuildInstigation(METHOD(alarmCount++;))))
        };
    };

    Alarm al1;
    Alarm al2;

    for (int i = 0; i < 10; i++)
    {
        al1.atState->SetValue(!al1.atState->GetValue());
        al2.atState->SetValue<NOP::ReNotify>(true);
        NOP::Scheduler::Instance().FinishAll();
    }
    EXPECT_EQ(al1.alarmCount, 5);
    EXPECT_EQ(al2.alarmCount, 10);
}

#ifdef LIBNOP_SCHEDULER_ENABLE
TEST(Complete, Competing)
{
    NOP::SharedAttribute<bool> atShouldExecute = NOP::BuildAttribute(true);
    NOP::SharedAttribute<bool> atResourceAvailable = NOP::BuildAttribute(false);
    NOP::SharedPremise prShouldExecute =
        NOP::BuildPremise(atShouldExecute, true, NOP::Equal());
    NOP::SharedPremise prResourceAvailable =
        NOP::BuildPremise(atResourceAvailable, true, NOP::Equal());

    NOP::SharedCondition cn1 =
        NOP::BuildCondition(CONDITION(*prShouldExecute && *prResourceAvailable),
                            prShouldExecute, prResourceAvailable);

    std::atomic<int> executionCounter1{0};
    NOP::Method mt1 = [&]()
    {
        atResourceAvailable->SetValue(false);
        ++executionCounter1;
    };
    NOP::Method mt2 = [&]()
    {
        atResourceAvailable->SetValue(false);
        ++executionCounter1;
    };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt1);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt2);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac2);

    atResourceAvailable->SetValue(true);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter1, 1);

    // Use function just to apply code coverage
    mt1();
    mt2();
}
#endif

TEST(Condition, EnumConjunction)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());
    NOP::SharedPremise pr2 = NOP::BuildPremise(at2, 2, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Conjunction>(pr1, pr2);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { ++executionCounter; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);

    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);

    at2->SetValue(2);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 1);
}

TEST(Condition, EnumDisjunction)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());
    NOP::SharedPremise pr2 = NOP::BuildPremise(at2, 2, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Disjunction>(pr1, pr2);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { ++executionCounter; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);

    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 1);

    at2->SetValue(2);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 1);
}

TEST(Flag, NoNotify)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    at1->SetValue<NOP::Default>(1);
    at2->SetValue<NOP::NoNotify>(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);
}

TEST(Flag, ParallelNoNotify)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at1->SetValue<NOP::Parallel>(1);
    at2->SetValue<NOP::Parallel | NOP::NoNotify>(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);
}

TEST(Flag, ReNotify)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at1->SetValue<NOP::Default>(1);
    at2->SetValue<NOP::Default>(1);

    NOP::Scheduler::Instance().FinishAll();

    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 1);

    at2->SetValue<NOP::ReNotify>(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 2);
}

TEST(Flag, Parallel)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac1);

    at1->SetValue<NOP::Parallel>(1);
    at2->SetValue<NOP::Parallel>(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_TRUE(rl2->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 2);
}

TEST(Flag, ReNotifyParallel)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);
    auto ptr = NOP::BuildPremise(at1, 1, NOP::Equal());

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac1);

    at1->SetValue<NOP::Parallel>(1);
    at2->SetValue<NOP::Parallel>(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_TRUE(rl2->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 2);

    at1->SetValue<NOP::Parallel | NOP::ReNotify>(1);
    NOP::Scheduler::Instance().FinishAll();

    // Everything should be approved
    EXPECT_TRUE(rl2->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 4);
}

TEST(Flag, ReNotifyNoNotify)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at1->SetValue<NOP::NoNotify | NOP::ReNotify>(1);
    at2->SetValue<NOP::NoNotify | NOP::ReNotify>(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);
}

#ifdef LIBNOP_SCHEDULER_ENABLE
TEST(Scheduler, FIFO)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::FIFO);
    NOP::SharedAttribute<bool> atDelay = NOP::BuildAttribute(false);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(0);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());
    NOP::SharedPremise pr2 = NOP::BuildPremise(at2, 2, NOP::Equal());
    NOP::SharedPremise prDelay = NOP::BuildPremise(atDelay, true, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);
    NOP::SharedCondition cn2 = NOP::BuildCondition<NOP::Single>(pr2);
    NOP::SharedCondition cnDelay = NOP::BuildCondition<NOP::Single>(prDelay);

    std::atomic<int> executionCounter{0};
    NOP::Method mt1 = [&] { EXPECT_EQ(1, ++executionCounter); };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt1);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::Method mt2 = [&] { EXPECT_EQ(2, ++executionCounter); };
    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt2);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn2, ac2);

    NOP::Method mtDelay = [&]
    { std::this_thread::sleep_for(std::chrono::milliseconds(10)); };
    NOP::SharedInstigation inDelay = NOP::BuildInstigation(mtDelay);
    NOP::SharedAction acDelay = NOP::BuildAction(inDelay);
    NOP::SharedRule rlDelay = NOP::BuildRule(cnDelay, acDelay);

    atDelay->SetValue(true);
    at1->SetValue(1);
    at2->SetValue(2);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 2);
}

TEST(Scheduler, LIFO)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::LIFO);
    NOP::SharedAttribute<bool> atDelay = NOP::BuildAttribute(false);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(0);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());
    NOP::SharedPremise pr2 = NOP::BuildPremise(at2, 2, NOP::Equal());
    NOP::SharedPremise prDelay = NOP::BuildPremise(atDelay, true, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);
    NOP::SharedCondition cn2 = NOP::BuildCondition<NOP::Single>(pr2);
    NOP::SharedCondition cnDelay = NOP::BuildCondition<NOP::Single>(prDelay);

    std::atomic<int> executionCounter{0};
    NOP::Method mt1 = [&] { EXPECT_EQ(2, ++executionCounter); };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt1);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::Method mt2 = [&] { EXPECT_EQ(1, ++executionCounter); };
    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt2);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn2, ac2);

    NOP::Method mtDelay = [&]
    { std::this_thread::sleep_for(std::chrono::milliseconds(100)); };
    NOP::SharedInstigation inDelay = NOP::BuildInstigation(mtDelay);
    NOP::SharedAction acDelay = NOP::BuildAction(inDelay);
    NOP::SharedRule rlDelay = NOP::BuildRule(cnDelay, acDelay);

    atDelay->SetValue(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    at1->SetValue(1);
    at2->SetValue(2);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 2);
}

TEST(Scheduler, Priority)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::Priority);
    NOP::SharedAttribute<bool> atDelay = NOP::BuildAttribute(false);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());
    NOP::SharedPremise prDelay = NOP::BuildPremise(atDelay, true, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);
    NOP::SharedCondition cnDelay = NOP::BuildCondition<NOP::Single>(prDelay);

    std::atomic<int> executionCounter{0};
    NOP::Method mt1 = [&] { EXPECT_EQ(2, ++executionCounter); };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt1);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::Method mt2 = [&] { EXPECT_EQ(1, ++executionCounter); };
    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt2);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);

    NOP::Method mt3 = [&] { EXPECT_EQ(3, ++executionCounter); };
    NOP::SharedInstigation in3 = NOP::BuildInstigation(mt3);
    NOP::SharedAction ac3 = NOP::BuildAction(in3);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1, 0);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac2, 123);
    NOP::SharedRule rl3 = NOP::BuildRule(cn1, ac3, -1);

    NOP::Method mtDelay = [&]
    { std::this_thread::sleep_for(std::chrono::milliseconds(10)); };
    NOP::SharedInstigation inDelay = NOP::BuildInstigation(mtDelay);
    NOP::SharedAction acDelay = NOP::BuildAction(inDelay);
    NOP::SharedRule rlDelay = NOP::BuildRule(cnDelay, acDelay);

    atDelay->SetValue(true);
    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();

    EXPECT_EQ(executionCounter, 3);
}
#endif

TEST(Methods, Async)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::SharedInstigation in1 =
        NOP::BuildInstigation(ASYNC_METHOD(++executionCounter;));
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_TRUE(rl1->Approved());
    // Should not be executed yet
    EXPECT_EQ(executionCounter, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_EQ(executionCounter, 1);
}

TEST(Methods, AsyncMultiple)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::EStrategy::None);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::SharedInstigation in1 =
        NOP::BuildInstigation(ASYNC_METHOD(++executionCounter;));
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_EQ(executionCounter, 3);
}

TEST(Methods, AsyncMultipleSlow)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::EStrategy::None);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::SharedInstigation in1 = NOP::BuildInstigation(
        ASYNC_METHOD(std::this_thread::sleep_for(std::chrono::milliseconds(10));
                     ++executionCounter;));
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_EQ(executionCounter, 3);
}

TEST(Parallel, Action)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::EStrategy::None);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::SharedInstigation in1 =
        NOP::BuildInstigation(METHOD(++executionCounter;));
    NOP::SharedInstigation in2 =
        NOP::BuildInstigation(METHOD(++executionCounter;));
    NOP::SharedAction ac1 = NOP::BuildAction<NOP::Parallel>(in1, in2);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_EQ(executionCounter, 6);
}

TEST(Parallel, Instigation)
{
    NOP::Scheduler::Instance().SetStrategy(NOP::EStrategy::None);
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedPremise pr1 = NOP::BuildPremise(at1, 1, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition<NOP::Single>(pr1);

    std::atomic<int> executionCounter{0};
    NOP::SharedInstigation in1 = NOP::BuildInstigation<NOP::Parallel>(
        METHOD(++executionCounter;), METHOD(++executionCounter;));

    NOP::SharedAction ac1 = NOP::BuildAction<NOP::Parallel>(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    at1->SetValue(0);
    at1->SetValue(1);
    NOP::Scheduler::Instance().FinishAll();
    EXPECT_EQ(executionCounter, 6);
}
