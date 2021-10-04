#pragma once

#include "libnop/framework.h"

class SemaphoreCTA
{
   public:
    NOP::SharedAttribute<int> atSeconds;

   private:
    NOP::SharedAttribute<int> atSemaphoreState;
    const NOP::SharedPremise prSeconds;
    const NOP::SharedPremise prSemaphoreState;
    NOP::SharedRule rlHorizontalTrafficLightGreen;
    const NOP::SharedPremise prAtSeconds3;
    const NOP::SharedPremise prSemaphoreState3;
    NOP::SharedRule rlHorizontalTrafficLightRed;
    const NOP::SharedPremise prSeconds2;
    const NOP::SharedPremise prSemaphoreState2;
    NOP::SharedRule rlHorizontalTrafficLightYellow;
    const NOP::SharedPremise prAtSeconds4;
    const NOP::SharedPremise prSemaphoreState4;
    NOP::SharedRule rlVerticalTrafficLightGreen;
    const NOP::SharedPremise prAtSeconds6;
    const NOP::SharedPremise prSemaphoreState6;
    NOP::SharedRule rlVerticalTrafficLightRed;
    const NOP::SharedPremise prAtSeconds5;
    const NOP::SharedPremise prSemaphoreState5;
    NOP::SharedRule rlVerticalTrafficLightYellow;

   public:
    SemaphoreCTA();

   private:
    void mtHorizontalTrafficLightGREEN();
    void mtHorizontalTrafficLightRED();
    void mtHorizontalTrafficLightYELLOW();
    void mtResetTimer();
    void mtVerticalTrafficLightGREEN();
    void mtVerticalTrafficLightRED();
    void mtVerticalTrafficLightYELLOW();
};
