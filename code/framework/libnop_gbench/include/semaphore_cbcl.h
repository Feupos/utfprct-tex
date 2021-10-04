#pragma once
#include "libnop/framework.h"

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
