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

class Semaphore_CBCL
{
   public:
    NOP::SharedAttribute<int> atSeconds;

   private:
    NOP::SharedAttribute<int> atHVSS;
    NOP::SharedAttribute<int> atSemaphoreState;
    NOP::SharedAttribute<int> atVVSS;
    const NOP::SharedPremise prSeconds;
    const NOP::SharedPremise prSemaphoreState;
    NOP::SharedRule rlCBCL1;
    const NOP::SharedPremise prSecondsCBCL6;
    const NOP::SharedPremise prSemaphoreStateCBCL6;
    NOP::SharedRule rlCBCL10;
    const NOP::SharedPremise prSeconds7;
    const NOP::SharedPremise prSemaphoreState7;
    const NOP::SharedPremise prVehicleSensorState7;
    NOP::SharedRule rlCBCL11;
    const NOP::SharedPremise prSeconds7Full;
    const NOP::SharedPremise prSemaphoreState7Full;
    const NOP::SharedPremise prVehicleSensorState7Full;
    NOP::SharedRule rlCBCL12;
    const NOP::SharedPremise prSeconds8;
    const NOP::SharedPremise prSecondsSup8;
    const NOP::SharedPremise prSemaphoreState8;
    const NOP::SharedPremise prVehicleSensorState8;
    NOP::SharedRule rlCBCL13;
    const NOP::SharedPremise prSeconds8Full;
    const NOP::SharedPremise prSecondsSup8Full;
    const NOP::SharedPremise prSemaphoreState8Full;
    const NOP::SharedPremise prVehicleSensorState8Full;
    NOP::SharedRule rlCBCL14;
    const NOP::SharedPremise prSeconds9;
    const NOP::SharedPremise prSemaphoreState9;
    const NOP::SharedPremise prVehicleSensorState9;
    NOP::SharedRule rlCBCL15;
    const NOP::SharedPremise prSeconds9Full;
    const NOP::SharedPremise prSemaphoreState9Full;
    const NOP::SharedPremise prVehicleSensorState9Full;
    NOP::SharedRule rlCBCL16;
    const NOP::SharedPremise prSeconds10;
    const NOP::SharedPremise prSecondsSup10;
    const NOP::SharedPremise prSemaphoreState10;
    const NOP::SharedPremise prVehicleSensorState10;
    NOP::SharedRule rlCBCL17;
    const NOP::SharedPremise prSeconds10Full;
    const NOP::SharedPremise prSecondsSup10Full;
    const NOP::SharedPremise prSemaphoreState10Full;
    const NOP::SharedPremise prVehicleSensorState10Full;
    NOP::SharedRule rlCBCL18;
    const NOP::SharedPremise prSeconds2;
    const NOP::SharedPremise prSemaphoreState2;
    NOP::SharedRule rlCBCL2;
    const NOP::SharedPremise prSecondsCBCL2;
    const NOP::SharedPremise prSemaphoreStateCBCL2;
    NOP::SharedRule rlCBCL3;
    const NOP::SharedPremise prSeconds3;
    const NOP::SharedPremise prSemaphoreState3;
    NOP::SharedRule rlCBCL4;
    const NOP::SharedPremise prSecondsCBCL3;
    const NOP::SharedPremise prSemaphoreStateCBCL3;
    NOP::SharedRule rlCBCL5;
    const NOP::SharedPremise prSeconds4;
    const NOP::SharedPremise prSemaphoreState4;
    NOP::SharedRule rlCBCL6;
    const NOP::SharedPremise prSeconds5;
    const NOP::SharedPremise prSemaphoreState5;
    NOP::SharedRule rlCBCL7;
    const NOP::SharedPremise prSecondsCBCL5;
    const NOP::SharedPremise prSemaphoreStateCBCL5;
    NOP::SharedRule rlCBCL8;
    const NOP::SharedPremise prSeconds6;
    const NOP::SharedPremise prSemaphoreState6;
    NOP::SharedRule rlCBCL9;

   public:
    Semaphore_CBCL();

   private:
    void mtHTLG();
    void mtHTLGCBCL();
    void mtHTLR();
    void mtHTLY();
    void mtHTLYCBCL();
    void mtRT();
    void mtVTLG();
    void mtVTLGCBCL();
    void mtVTLR();
    void mtVTLY();
    void mtVTLYCBCL();
};

Semaphore_CBCL::Semaphore_CBCL()
    : atSeconds{NOP::BuildAttribute<int>(0)},
      atHVSS{NOP::BuildAttribute<int>(0)},
      atSemaphoreState{NOP::BuildAttribute<int>(5)},
      atVVSS{NOP::BuildAttribute<int>(0)},
      prSeconds{NOP::BuildPremise<int>(atSeconds, 2, NOP::Equal())},
      prSemaphoreState{
          NOP::BuildPremise<int>(atSemaphoreState, 5, NOP::Equal())},
      prSecondsCBCL6{NOP::BuildPremise<int>(atSeconds, 6, NOP::Equal())},
      prSemaphoreStateCBCL6{
          NOP::BuildPremise<int>(atSemaphoreState, 9, NOP::Equal())},
      prSeconds7{NOP::BuildPremise<int>(atSeconds, 17, NOP::LessEqual())},
      prSemaphoreState7{
          NOP::BuildPremise<int>(atSemaphoreState, 0, NOP::Equal())},
      prVehicleSensorState7{NOP::BuildPremise<int>(atVVSS, 1, NOP::Equal())},
      prSeconds7Full{NOP::BuildPremise<int>(atSeconds, 17, NOP::LessEqual())},
      prSemaphoreState7Full{
          NOP::BuildPremise<int>(atSemaphoreState, 0, NOP::Equal())},
      prVehicleSensorState7Full{
          NOP::BuildPremise<int>(atVVSS, 2, NOP::Equal())},
      prSeconds8{NOP::BuildPremise<int>(atSeconds, 18, NOP::GreaterEqual())},
      prSecondsSup8{NOP::BuildPremise<int>(atSeconds, 32, NOP::Less())},
      prSemaphoreState8{
          NOP::BuildPremise<int>(atSemaphoreState, 0, NOP::Equal())},
      prVehicleSensorState8{NOP::BuildPremise<int>(atVVSS, 1, NOP::Equal())},
      prSeconds8Full{
          NOP::BuildPremise<int>(atSeconds, 18, NOP::GreaterEqual())},
      prSecondsSup8Full{NOP::BuildPremise<int>(atSeconds, 32, NOP::Less())},
      prSemaphoreState8Full{
          NOP::BuildPremise<int>(atSemaphoreState, 0, NOP::Equal())},
      prVehicleSensorState8Full{
          NOP::BuildPremise<int>(atVVSS, 2, NOP::Equal())},
      prSeconds9{NOP::BuildPremise<int>(atSeconds, 17, NOP::LessEqual())},
      prSemaphoreState9{
          NOP::BuildPremise<int>(atSemaphoreState, 3, NOP::Equal())},
      prVehicleSensorState9{
          NOP::BuildPremise<int>(atSemaphoreState, 1, NOP::Equal())},
      prSeconds9Full{NOP::BuildPremise<int>(atSeconds, 77, NOP::LessEqual())},
      prSemaphoreState9Full{
          NOP::BuildPremise<int>(atSemaphoreState, 3, NOP::Equal())},
      prVehicleSensorState9Full{
          NOP::BuildPremise<int>(atSemaphoreState, 2, NOP::Equal())},
      prSeconds10{NOP::BuildPremise<int>(atSeconds, 18, NOP::GreaterEqual())},
      prSecondsSup10{NOP::BuildPremise<int>(atSeconds, 32, NOP::Less())},
      prSemaphoreState10{
          NOP::BuildPremise<int>(atSemaphoreState, 3, NOP::Equal())},
      prVehicleSensorState10{NOP::BuildPremise<int>(atHVSS, 1, NOP::Equal())},
      prSeconds10Full{
          NOP::BuildPremise<int>(atSeconds, 18, NOP::GreaterEqual())},
      prSecondsSup10Full{NOP::BuildPremise<int>(atSeconds, 32, NOP::Less())},
      prSemaphoreState10Full{
          NOP::BuildPremise<int>(atSemaphoreState, 3, NOP::Equal())},
      prVehicleSensorState10Full{
          NOP::BuildPremise<int>(atHVSS, 2, NOP::Equal())},
      prSeconds2{NOP::BuildPremise<int>(atSeconds, 38, NOP::Equal())},
      prSemaphoreState2{
          NOP::BuildPremise<int>(atSemaphoreState, 0, NOP::Equal())},
      prSecondsCBCL2{NOP::BuildPremise<int>(atSeconds, 30, NOP::Equal())},
      prSemaphoreStateCBCL2{
          NOP::BuildPremise<int>(atSemaphoreState, 6, NOP::Equal())},
      prSeconds3{NOP::BuildPremise<int>(atSeconds, 5, NOP::Equal())},
      prSemaphoreState3{
          NOP::BuildPremise<int>(atSemaphoreState, 1, NOP::Equal())},
      prSecondsCBCL3{NOP::BuildPremise<int>(atSeconds, 6, NOP::Equal())},
      prSemaphoreStateCBCL3{
          NOP::BuildPremise<int>(atSemaphoreState, 7, NOP::Equal())},
      prSeconds4{NOP::BuildPremise<int>(atSeconds, 2, NOP::Equal())},
      prSemaphoreState4{
          NOP::BuildPremise<int>(atSemaphoreState, 2, NOP::Equal())},
      prSeconds5{NOP::BuildPremise<int>(atSeconds, 38, NOP::Equal())},
      prSemaphoreState5{
          NOP::BuildPremise<int>(atSemaphoreState, 3, NOP::Equal())},
      prSecondsCBCL5{NOP::BuildPremise<int>(atSeconds, 30, NOP::Equal())},
      prSemaphoreStateCBCL5{
          NOP::BuildPremise<int>(atSemaphoreState, 8, NOP::Equal())},
      prSeconds6{NOP::BuildPremise<int>(atSeconds, 5, NOP::Equal())},
      prSemaphoreState6{
          NOP::BuildPremise<int>(atSemaphoreState, 4, NOP::Equal())}
{
    rlCBCL1 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds && *prSemaphoreState),
                            prSeconds, prSemaphoreState),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(METHOD(mtHTLG();),
                                                              METHOD(mtRT();)))

    );
    rlCBCL10 =
        NOP::BuildRule(NOP::BuildCondition(
                           CONDITION(*prSecondsCBCL6 && *prSemaphoreStateCBCL6),
                           prSecondsCBCL6, prSemaphoreStateCBCL6),
                       NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
                           METHOD(mtVTLR();), METHOD(mtRT();)))

        );
    rlCBCL11 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds7 && *prSemaphoreState7 &&
                                      *prVehicleSensorState7),
                            prSeconds7, prSemaphoreState7,
                            prVehicleSensorState7),
        NOP::BuildAction(
            NOP::BuildInstigation<NOP::Parallel>(METHOD(mtHTLGCBCL();)))

    );
    rlCBCL12 = NOP::BuildRule(
        NOP::BuildCondition(
            CONDITION(*prSeconds7Full && *prSemaphoreState7Full &&
                      *prVehicleSensorState7Full),
            prSeconds7Full, prSemaphoreState7Full, prVehicleSensorState7Full),
        NOP::BuildAction(
            NOP::BuildInstigation<NOP::Parallel>(METHOD(mtHTLGCBCL();)))

    );
    rlCBCL13 = NOP::BuildRule(
        NOP::BuildCondition(
            CONDITION(*prSeconds8 && *prSecondsSup8 && *prSemaphoreState8 &&
                      *prVehicleSensorState8),
            prSeconds8, prSecondsSup8, prSemaphoreState8,
            prVehicleSensorState8),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtHTLYCBCL();), METHOD(mtRT();)))

    );
    rlCBCL14 = NOP::BuildRule(
        NOP::BuildCondition(
            CONDITION(*prSeconds8Full && *prSecondsSup8Full &&
                      *prSemaphoreState8Full && *prVehicleSensorState8Full),
            prSeconds8Full, prSecondsSup8Full, prSemaphoreState8Full,
            prVehicleSensorState8Full),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtHTLYCBCL();), METHOD(mtRT();)))

    );
    rlCBCL15 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds9 && *prSemaphoreState9 &&
                                      *prVehicleSensorState9),
                            prSeconds9, prSemaphoreState9,
                            prVehicleSensorState9),
        NOP::BuildAction(
            NOP::BuildInstigation<NOP::Parallel>(METHOD(mtVTLGCBCL();)))

    );
    rlCBCL16 = NOP::BuildRule(
        NOP::BuildCondition(
            CONDITION(*prSeconds9Full && *prSemaphoreState9Full &&
                      *prVehicleSensorState9Full),
            prSeconds9Full, prSemaphoreState9Full, prVehicleSensorState9Full),
        NOP::BuildAction(
            NOP::BuildInstigation<NOP::Parallel>(METHOD(mtVTLGCBCL();)))

    );
    rlCBCL17 = NOP::BuildRule(
        NOP::BuildCondition(
            CONDITION(*prSeconds10 && *prSecondsSup10 && *prSemaphoreState10 &&
                      *prVehicleSensorState10),
            prSeconds10, prSecondsSup10, prSemaphoreState10,
            prVehicleSensorState10),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtVTLYCBCL();), METHOD(mtRT();)))

    );
    rlCBCL18 = NOP::BuildRule(
        NOP::BuildCondition(
            CONDITION(*prSeconds10Full && *prSecondsSup10Full &&
                      *prSemaphoreState10Full && *prVehicleSensorState10Full),
            prSeconds10Full, prSecondsSup10Full, prSemaphoreState10Full,
            prVehicleSensorState10Full),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
            METHOD(mtVTLYCBCL();), METHOD(mtRT();)))

    );
    rlCBCL2 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds2 && *prSemaphoreState2),
                            prSeconds2, prSemaphoreState2),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(METHOD(mtHTLY();),
                                                              METHOD(mtRT();)))

    );
    rlCBCL3 =
        NOP::BuildRule(NOP::BuildCondition(
                           CONDITION(*prSecondsCBCL2 && *prSemaphoreStateCBCL2),
                           prSecondsCBCL2, prSemaphoreStateCBCL2),
                       NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
                           METHOD(mtHTLY();), METHOD(mtRT();)))

        );
    rlCBCL4 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds3 && *prSemaphoreState3),
                            prSeconds3, prSemaphoreState3),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(METHOD(mtHTLR();),
                                                              METHOD(mtRT();)))

    );
    rlCBCL5 =
        NOP::BuildRule(NOP::BuildCondition(
                           CONDITION(*prSecondsCBCL3 && *prSemaphoreStateCBCL3),
                           prSecondsCBCL3, prSemaphoreStateCBCL3),
                       NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
                           METHOD(mtHTLR();), METHOD(mtRT();)))

        );
    rlCBCL6 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds4 && *prSemaphoreState4),
                            prSeconds4, prSemaphoreState4),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(METHOD(mtVTLG();),
                                                              METHOD(mtRT();)))

    );
    rlCBCL7 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds5 && *prSemaphoreState5),
                            prSeconds5, prSemaphoreState5),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(METHOD(mtVTLY();),
                                                              METHOD(mtRT();)))

    );
    rlCBCL8 =
        NOP::BuildRule(NOP::BuildCondition(
                           CONDITION(*prSecondsCBCL5 && *prSemaphoreStateCBCL5),
                           prSecondsCBCL5, prSemaphoreStateCBCL5),
                       NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(
                           METHOD(mtVTLY();), METHOD(mtRT();)))

        );
    rlCBCL9 = NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prSeconds6 && *prSemaphoreState6),
                            prSeconds6, prSemaphoreState6),
        NOP::BuildAction(NOP::BuildInstigation<NOP::Parallel>(METHOD(mtVTLR();),
                                                              METHOD(mtRT();)))

    );
}

void Semaphore_CBCL::mtHTLG() { atSemaphoreState->SetValue<NOP::Parallel>(0); }

void Semaphore_CBCL::mtHTLGCBCL()
{
    atSemaphoreState->SetValue<NOP::Parallel>(6);
}

void Semaphore_CBCL::mtHTLR() { atSemaphoreState->SetValue<NOP::Parallel>(2); }

void Semaphore_CBCL::mtHTLY() { atSemaphoreState->SetValue<NOP::Parallel>(1); }

void Semaphore_CBCL::mtHTLYCBCL()
{
    atSemaphoreState->SetValue<NOP::Parallel>(7);
}

void Semaphore_CBCL::mtRT() { atSeconds->SetValue<NOP::Parallel>(0); }

void Semaphore_CBCL::mtVTLG() { atSemaphoreState->SetValue<NOP::Parallel>(3); }

void Semaphore_CBCL::mtVTLGCBCL()
{
    atSemaphoreState->SetValue<NOP::Parallel>(8);
}

void Semaphore_CBCL::mtVTLR() { atSemaphoreState->SetValue<NOP::Parallel>(5); }

void Semaphore_CBCL::mtVTLY() { atSemaphoreState->SetValue<NOP::Parallel>(4); }

void Semaphore_CBCL::mtVTLYCBCL()
{
    atSemaphoreState->SetValue<NOP::Parallel>(9);
}


