#pragma once
#include "libnop/framework.h"

std::vector<std::vector<int>> test_data{
    {580, 280, 509, 240}, {600, 220, 400, 100}, {550, 420, 140, 20},
    {730, 290, 630, 180}, {500, 340, 150, 20},  {630, 330, 600, 250},
    {500, 350, 130, 30},  {670, 310, 470, 150}, {680, 280, 480, 140},
    {610, 280, 400, 130}, {610, 260, 560, 140}, {640, 320, 450, 150},
    {610, 280, 470, 120}, {650, 280, 459, 150}, {610, 290, 470, 140},
    {490, 360, 140, 10},  {600, 290, 450, 150}, {550, 260, 440, 120},
    {480, 300, 140, 30},  {540, 390, 130, 40},  {560, 280, 490, 200},
    {560, 300, 450, 150}, {480, 340, 190, 20},  {440, 290, 140, 20},
    {620, 280, 480, 180}, {459, 360, 100, 20},  {509, 380, 190, 40},
    {620, 290, 430, 130}, {500, 229, 330, 100}, {500, 340, 160, 40}};
std::vector<int> result_data{2, 1, 0, 2, 0, 2, 0, 1, 1, 1, 2, 1, 1, 1, 1,
                             0, 1, 1, 0, 0, 2, 1, 0, 0, 2, 0, 0, 1, 1, 0};

struct Forest
{
    int result_class{-1};

    NOP::SharedAttribute<int> attr0 = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> attr1 = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> attr2 = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> attr3 = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> count_setosa = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> count_versicolor = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<int> count_virginica = NOP::BuildAttribute<int>(0);
    NOP::SharedAttribute<bool> trigger_tree_0 =
        NOP::BuildAttribute<bool>(false);
    NOP::SharedAttribute<bool> trigger_tree_1 =
        NOP::BuildAttribute<bool>(false);
    NOP::Method mt_count_setosa = [&]() {
        count_setosa->SetValue(count_setosa->GetValue() + 1);
    };
    NOP::Method mt_rst_count_setosa = [&]() { count_setosa->SetValue(0); };
    NOP::Method mt_count_versicolor = [&]() {
        count_versicolor->SetValue(count_versicolor->GetValue() + 1);
    };
    NOP::Method mt_rst_count_versicolor = [&]() {
        count_versicolor->SetValue(0);
    };
    NOP::Method mt_count_virginica = [&]() {
        count_virginica->SetValue(count_virginica->GetValue() + 1);
    };
    NOP::Method mt_rst_count_virginica = [&]() {
        count_virginica->SetValue(0);
    };
    NOP::Method mtTrigger0 = [&]() { trigger_tree_0->SetValue(true); };
    NOP::Method mtRstTrigger0 = [&]() { trigger_tree_0->SetValue(false); };
    NOP::Method mtTrigger1 = [&]() { trigger_tree_1->SetValue(true); };
    NOP::Method mtRstTrigger1 = [&]() { trigger_tree_1->SetValue(false); };

    NOP::SharedRule rlTree_0_1 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::LessEqual()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(
            NOP::BuildInstigation(mt_count_setosa, mtTrigger1, mtRstTrigger0)));

    NOP::SharedRule rlTree_0_5 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 165, NOP::LessEqual()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_versicolor, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_7 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 165, NOP::Greater()),
            NOP::BuildPremise(attr1, 310, NOP::LessEqual()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_virginica, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_8 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 165, NOP::Greater()),
            NOP::BuildPremise(attr1, 310, NOP::Greater()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_versicolor, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_11 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::Greater()),
            NOP::BuildPremise(attr2, 505, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 185, NOP::LessEqual()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_versicolor, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_12 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::Greater()),
            NOP::BuildPremise(attr2, 505, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 185, NOP::Greater()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_virginica, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_15 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::Greater()),
            NOP::BuildPremise(attr2, 505, NOP::Greater()),
            NOP::BuildPremise(attr1, 275, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 175, NOP::LessEqual()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_versicolor, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_16 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::Greater()),
            NOP::BuildPremise(attr2, 505, NOP::Greater()),
            NOP::BuildPremise(attr1, 275, NOP::LessEqual()),
            NOP::BuildPremise(attr3, 175, NOP::Greater()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_virginica, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlTree_0_14 = NOP::BuildRule(
        NOP::BuildCondition<NOP::Conjunction>(
            NOP::BuildPremise(attr3, 75, NOP::Greater()),
            NOP::BuildPremise(attr2, 495, NOP::Greater()),
            NOP::BuildPremise(attr2, 505, NOP::Greater()),
            NOP::BuildPremise(attr1, 275, NOP::Greater()),
            NOP::BuildPremise(trigger_tree_0, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(mt_count_virginica, mtTrigger1,
                                               mtRstTrigger0)));

    NOP::SharedRule rlEnd = NOP::BuildRule(
        NOP::BuildCondition<NOP::Single>(
            NOP::BuildPremise(trigger_tree_1, true, NOP::Equal())),
        NOP::BuildAction(NOP::BuildInstigation(
            [&]() {
                result_class =
                    count_setosa->GetValue() < count_versicolor->GetValue() ? 1
                                                                            : 0;
                result_class =
                    count_setosa->GetValue() < count_virginica->GetValue() &&
                            count_versicolor->GetValue() <
                                count_virginica->GetValue()
                        ? 2
                        : result_class;
            },
            mt_rst_count_setosa, mt_rst_count_versicolor,
            mt_rst_count_virginica, mtRstTrigger1)));

    int Classify(int a0, int a1, int a2, int a3)
    {
        attr0->SetValue(a0);
        attr1->SetValue(a1);
        attr2->SetValue(a2);
        attr3->SetValue(a3);
        trigger_tree_0->SetValue(true);
        return result_class;
    }
};