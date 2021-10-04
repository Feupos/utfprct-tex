#include "gtest/gtest.h"

#include "NOPFramework.h"

#include <queue>
#include <random>
#include <thread>
#include <atomic>

TEST(Attribute, Int) {
    const int val{ 123456 };
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(val);
    EXPECT_EQ(at1->GetValue(), val);
}

TEST(Attribute, Bool) {
    const bool val{ true };
    NOP::SharedAttribute<bool> at1 = NOP::BuildAttribute(val);
    EXPECT_EQ(at1->GetValue(), val);
}

TEST(Attribute, Class) {
    class Rectangle {
        int width, height;
    public:
        Rectangle(int w, int h) : width{ w }, height{ h } {};;
        inline bool operator== (Rectangle i) const
        {
            return (width == i.width) && (height == i.height);
        }
        inline bool operator!= (Rectangle i) const
        {
            return (width != i.width) || (height != i.height);
        }
    };

    const Rectangle val1{ 1,2 };
    NOP::SharedAttribute<Rectangle> at1 = NOP::BuildAttribute(val1);
    EXPECT_EQ(at1->GetValue(), val1);

    const Rectangle val2{ 3,4 };
    NOP::SharedAttribute<Rectangle> at2 = NOP::BuildAttribute(val2);
    EXPECT_NE(at1->GetValue(), at2->GetValue());

    at2->SetValue(val1);
    EXPECT_EQ(at1->GetValue(), at2->GetValue());

}

TEST(Attribute, String) {
    const std::string val{ "test" };
    NOP::SharedAttribute<std::string> at1 = NOP::BuildAttribute(val);
    EXPECT_EQ(at1->GetValue(), val);
}

TEST(Premise, Simple)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);

    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());

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
    NOP::SharedPremise prDouble = NOP::BuildPremise<int>(at1, at2, 
        [](auto a1, auto a2) { return a1 == 2 * a2; });

    // On initialization should not be approved
    EXPECT_FALSE(prDouble->Approved());
    at1->SetValue(2*at2->GetValue());
    EXPECT_TRUE(prDouble->Approved());
    at1->SetValue(0);
    EXPECT_FALSE(prDouble->Approved());
}

TEST(Condition, Conjunction)
{
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise<int>(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(
        CONDITION (*pr1 && *pr2), pr1, pr2);

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
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise<int>(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1 || *pr2), pr1, pr2);

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
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise<int>(at3, at4, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    NOP::SharedCondition cn2 = NOP::BuildCondition(CONDITION(*pr2 && *cn1), pr2, cn1);


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

TEST(Complete, BasicRuleSingleCondition) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{0};
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    // Nothing should be approved upon initialization
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    at1->SetValue(1);

    // Nothing should be approved yet
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    at2->SetValue(1);

    // Everything should be approved
    EXPECT_TRUE(pr1->Approved());
    EXPECT_TRUE(cn1->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 1);

    at2->SetValue(10);
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    at1->SetValue(10);

    // Everything should be approved
    EXPECT_TRUE(pr1->Approved());
    EXPECT_TRUE(cn1->Approved());
    EXPECT_TRUE(rl1->Approved());
    EXPECT_EQ(executionCounter, 2);
}

TEST(Complete, InitialStatesDisapproved) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(2);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{ 0 };
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());

    EXPECT_EQ(executionCounter, 0);
}

TEST(Complete, InitialStatesApproved) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{ 0 };
    NOP::Method mt = [&] { executionCounter++; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    EXPECT_TRUE(pr1->Approved());
    EXPECT_TRUE(cn1->Approved());
    EXPECT_TRUE(rl1->Approved());

    EXPECT_EQ(executionCounter, 1);
}

TEST(Complete, SharedEntities1) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);

    std::atomic<int> executionCounter{ 0 };
    NOP::Method mt = [&] { executionCounter++; };
    // clone methods
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac2);

    EXPECT_EQ(executionCounter, 2);
}

TEST(Complete, SharedEntities2) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    NOP::SharedCondition cn2 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    std::atomic<int> executionCounter{ 0 };
    NOP::Method mt = [&] { executionCounter++; };
    // clone methods
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn2, ac1);

    EXPECT_EQ(executionCounter, 2);
}

TEST(Complete, Renotification) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    std::atomic<int> executionCounter{ 0 };
    NOP::SharedInstigation in1 = NOP::BuildInstigation([&] { executionCounter++; });
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at1->SetValue(1);
    at2->SetValue(1);

    EXPECT_EQ(executionCounter, 1);

    at2->SetValue(1, true);
    EXPECT_EQ(executionCounter, 2);

    at2->SetValue(1, true);
    EXPECT_EQ(executionCounter, 3);
}

TEST(Complete, RecursiveRule) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(0);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, std::less<>());
    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1), pr1);
    std::atomic<int> executionCounter{ 0 };
    auto test = [&]()
    {
        executionCounter++;
        at1->SetValue(at1->GetValue() + 1, true);
    };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(test);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    at2->SetValue(10);

    EXPECT_EQ(executionCounter, 10);
}

TEST(Overload, OperatorPlus) {
    NOP::Attribute<int> at1(1);
    NOP::Attribute<int> at2(2);
    EXPECT_EQ(at1 + at2, 3);
}

TEST(Premise, Composition) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute<int>(-1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute<int>(-2);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());

    NOP::SharedAttribute<int> at3 = NOP::BuildAttribute<int>(-3);
    NOP::SharedAttribute<int> at4 = NOP::BuildAttribute<int>(-4);
    NOP::SharedPremise pr2 = NOP::BuildPremise<int>(at3, at4, NOP::Equal());

    NOP::SharedAttribute<int> at5 = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> at6 = NOP::BuildAttribute<int>(0);
    NOP::SharedPremise pr3 = NOP::BuildPremise<int>(at5, at6, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(
        CONDITION( (*pr1 || *pr2) && !*pr3 ),
        pr1, pr2, pr3);

    at1->SetValue(1);
    at2->SetValue(1);
    EXPECT_TRUE(pr1->Approved());
    EXPECT_FALSE(pr2->Approved());
    EXPECT_TRUE(pr3->Approved());
    EXPECT_FALSE(cn1->Approved());

    at5->SetValue(1);
    EXPECT_FALSE(pr3->Approved());
    EXPECT_TRUE(cn1->Approved());

    at2->SetValue(-1);
    EXPECT_FALSE(pr1->Approved());
    EXPECT_FALSE(cn1->Approved());

    at3->SetValue(1);
    at4->SetValue(1);
    EXPECT_TRUE(pr2->Approved());
    EXPECT_TRUE(cn1->Approved());
}


TEST(Threads, Basic) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(0);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(1);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedCondition cn1 = NOP::BuildCondition([&]() { return bool(*pr1); }, pr1);
    std::atomic<int> executionCounter{ 0 };
    auto test = [&]()
    {
        ++executionCounter;
    };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(test);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    for (int i = 0; i < 100; i++)
    {
        executionCounter = 0;
        // 2000 values, 1000 times value 1
        std::deque<int> test_values{
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
        };
        std::mutex mutex;

        auto getval{ [&]()
            {
                int val = 0;
                mutex.lock();
                if (!test_values.empty())
                {
                    val = test_values.back();
                    test_values.pop_back();
                }
                mutex.unlock();
                return val;
            }
        };

        auto tester{ [&]()
            {
                while (!test_values.empty())
                {
                    at1->SetValue(getval(), true);
                }
            }
        };

        std::vector<std::thread> threads;

        for (int j = 0; j < 10; j++)
        {
            std::thread task{ tester };
            threads.push_back(std::move(task));
        }

        for(auto& it : threads)
        {
            it.join();
        }

        ASSERT_EQ(executionCounter, 1000);
    }
}

TEST(Example, Alarm)
{
    struct Alarm
    {
        int alarmCount{ 0 };

        NOP::SharedAttribute<bool> atState{ NOP::BuildAttribute<bool>(false) };
        NOP::SharedPremise prAlarm{ NOP::BuildPremise<bool>(atState, true, NOP::Equal()) };
        NOP::SharedCondition cnAlarm{ NOP::BuildCondition(CONDITION(*prAlarm), prAlarm) };
        NOP::Method mtNotify{ METHOD(alarmCount++;) };
        NOP::SharedInstigation inAlarm{ NOP::BuildInstigation(mtNotify) };
        NOP::SharedAction acAlarm{ NOP::BuildAction(inAlarm) };
        NOP::SharedRule rlAlarm{ NOP::BuildRule(cnAlarm, acAlarm) };
    };

    Alarm al1;
    Alarm al2;

    for (int i = 0; i < 10; i++)
    {
        al1.atState->SetValue(!al1.atState->GetValue());
        al2.atState->SetValue(true, true);
    }

    EXPECT_EQ(al1.alarmCount, 5);
    EXPECT_EQ(al2.alarmCount, 10);
}

TEST(Example, AlarmSimplified)
{
    struct Alarm
    {
        int alarmCount{ 0 };

        NOP::SharedAttribute<bool> atState{ NOP::BuildAttribute<bool>(false) };
        NOP::SharedPremise prAlarm{ NOP::BuildPremise<bool>(atState, true, NOP::Equal()) };
        NOP::SharedRule rlAlarm{ NOP::BuildRule( NOP::BuildCondition(CONDITION(*prAlarm), prAlarm),
            NOP::BuildAction(NOP::BuildInstigation(METHOD(alarmCount++;))) ) };
    };

    Alarm al1;
    Alarm al2;

    for (int i = 0; i < 10; i++)
    {
        al1.atState->SetValue(!al1.atState->GetValue());
        al2.atState->SetValue(true, true);
    }

    EXPECT_EQ(al1.alarmCount, 5);
    EXPECT_EQ(al2.alarmCount, 10);
}

TEST(Complete, Contradiction) {
    NOP::SharedAttribute<int> at1 = NOP::BuildAttribute(1);
    NOP::SharedAttribute<int> at2 = NOP::BuildAttribute(2);
    NOP::SharedPremise pr1 = NOP::BuildPremise<int>(at1, at2, NOP::Equal());
    NOP::SharedPremise pr2 = NOP::BuildPremise<int>(at1, at2, NOP::Different());

    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*pr1 && *pr2), pr1, pr2);

    std::atomic<int> executionCounter{ 0 };
    NOP::Method mt = [&] { ++executionCounter; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);

    EXPECT_FALSE(pr1->Approved());
    EXPECT_TRUE(pr2->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);

    at1->SetValue(2);
    EXPECT_TRUE(pr1->Approved());
    EXPECT_FALSE(pr2->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);

    at2->SetValue(1);
    EXPECT_FALSE(pr1->Approved());
    EXPECT_TRUE(pr2->Approved());
    EXPECT_FALSE(cn1->Approved());
    EXPECT_FALSE(rl1->Approved());
    EXPECT_EQ(executionCounter, 0);
}

TEST(Complete, Competing) {
    NOP::SharedAttribute<bool> atShouldExecute = NOP::BuildAttribute(true);
    NOP::SharedAttribute<bool> atResourceAvailable = NOP::BuildAttribute(false);
    NOP::SharedPremise prShouldExecute = NOP::BuildPremise<bool>(atShouldExecute, true, NOP::Equal());
    NOP::SharedPremise prResourceAvailable = NOP::BuildPremise<bool>(atResourceAvailable, true, NOP::Equal());

    NOP::SharedCondition cn1 = NOP::BuildCondition(CONDITION(*prShouldExecute && *prResourceAvailable), prShouldExecute, prResourceAvailable);

    NOP::Method mt = []() { printf("Calling function with parameter"); };
    std::atomic<int> executionCounter1{ 0 };
    NOP::Method mt1 = [&]() { atResourceAvailable->SetValue(false);  ++executionCounter1; };
    std::atomic<int> executionCounter2{ 0 };
    NOP::Method mt2 = [&]() { atResourceAvailable->SetValue(false);  ++executionCounter1; };
    NOP::SharedInstigation in1 = NOP::BuildInstigation(mt1);
    NOP::SharedAction ac1 = NOP::BuildAction(in1);
    NOP::SharedInstigation in2 = NOP::BuildInstigation(mt2);
    NOP::SharedAction ac2 = NOP::BuildAction(in2);

    NOP::SharedRule rl1 = NOP::BuildRule(cn1, ac1);
    NOP::SharedRule rl2 = NOP::BuildRule(cn1, ac2);

    atResourceAvailable->SetValue(true);

    EXPECT_EQ(executionCounter2, 0);
    EXPECT_EQ(executionCounter1, 1);
}