#include "semaphore_cta.h"

SemaphoreCTA::SemaphoreCTA()
    : atSeconds{NOP::BuildAttribute<int>(0)},
      atSemaphoreState{NOP::BuildAttribute<int>(5)},
      prSeconds{NOP::BuildPremise<>(atSeconds, 2, NOP::Equal())},
      prSemaphoreState{
          NOP::BuildPremise<int>(atSemaphoreState, 5, NOP::Equal())},
      prAtSeconds3{NOP::BuildPremise<int>(atSeconds, 45, NOP::Equal())},
      prSemaphoreState3{
          NOP::BuildPremise<int>(atSemaphoreState, 1, NOP::Equal())},
      prSeconds2{NOP::BuildPremise<int>(atSeconds, 40, NOP::Equal())},
      prSemaphoreState2{
          NOP::BuildPremise<int>(atSemaphoreState, 0, NOP::Equal())},
      prAtSeconds4{NOP::BuildPremise<int>(atSeconds, 47, NOP::Equal())},
      prSemaphoreState4{
          NOP::BuildPremise<int>(atSemaphoreState, 2, NOP::Equal())},
      prAtSeconds6{NOP::BuildPremise<int>(atSeconds, 90, NOP::Equal())},
      prSemaphoreState6{
          NOP::BuildPremise<int>(atSemaphoreState, 4, NOP::Equal())},
      prAtSeconds5{NOP::BuildPremise<int>(atSeconds, 85, NOP::Equal())},
      prSemaphoreState5{
          NOP::BuildPremise<int>(atSemaphoreState, 3, NOP::Equal())}
{
    rlHorizontalTrafficLightGreen = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds && *prSemaphoreState),
                            prSeconds, prSemaphoreState),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtHorizontalTrafficLightGREEN();)))

    );
    rlHorizontalTrafficLightRed = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prAtSeconds3 && *prSemaphoreState3),
                            prAtSeconds3, prSemaphoreState3),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtHorizontalTrafficLightRED();)))

    );
    rlHorizontalTrafficLightYellow = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds2 && *prSemaphoreState2),
                            prSeconds2, prSemaphoreState2),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtHorizontalTrafficLightYELLOW();)))

    );
    rlVerticalTrafficLightGreen = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prAtSeconds4 && *prSemaphoreState4),
                            prAtSeconds4, prSemaphoreState4),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtVerticalTrafficLightGREEN();)))

    );
    rlVerticalTrafficLightRed = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prAtSeconds6 && *prSemaphoreState6),
                            prAtSeconds6, prSemaphoreState6),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtVerticalTrafficLightRED();), METHOD(mtResetTimer();)))

    );
    rlVerticalTrafficLightYellow = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prAtSeconds5 && *prSemaphoreState5),
                            prAtSeconds5, prSemaphoreState5),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtVerticalTrafficLightYELLOW();)))

    );
}

void SemaphoreCTA::mtHorizontalTrafficLightGREEN()
{
    atSemaphoreState->SetValue<NOP::Parallel>(0);
}

void SemaphoreCTA::mtHorizontalTrafficLightRED()
{
    atSemaphoreState->SetValue<NOP::Parallel>(2);
}

void SemaphoreCTA::mtHorizontalTrafficLightYELLOW()
{
    atSemaphoreState->SetValue<NOP::Parallel>(1);
}

void SemaphoreCTA::mtResetTimer() { atSeconds->SetValue<NOP::Parallel>(0); }

void SemaphoreCTA::mtVerticalTrafficLightGREEN()
{
    atSemaphoreState->SetValue<NOP::Parallel>(3);
}

void SemaphoreCTA::mtVerticalTrafficLightRED()
{
    atSemaphoreState->SetValue<NOP::Parallel>(5);
}

void SemaphoreCTA::mtVerticalTrafficLightYELLOW()
{
    atSemaphoreState->SetValue<NOP::Parallel>(4);
}
