// C++ Framework NOP 4.0
//
// Copyright (c) 2020 - present, Felipe dos Santos Neves
// All rights reserved.
//
// For the license information refer to framework.h

#pragma once

#ifdef LIBNOP_FW2_TEST_ENABLE
#pragma warning(disable : 4005)
#pragma warning(disable : 4250)
#pragma warning(disable : 4263)
#pragma warning(disable : 4264)
#pragma warning(disable : 4267)
#pragma warning(disable : 4244)

#include <vector>
#include <memory>
#include <atomic>

#include "framework/NOPApplication.h"
#include "framework/elements/abstract/MethodPointer.h"
#include "framework/utils/SingleInclude.h"

struct FW2Referee : public FBE
{
    Boolean* atReady;

    FW2Referee() { BOOLEAN(this, atReady, false); }
};

struct FW2Target : public FBE
{
    Boolean* atReady;
    Boolean* atIsShot;

    FW2Target()
    {
        BOOLEAN(this, atReady, false);
        BOOLEAN(this, atIsShot, false);
    }
};

struct FW2Marksman : public FBE
{
    std::shared_ptr<FW2Target> Target_;

    Premise* prTargetReady;
    Premise* prTargetNotShot;

    Instigation* inShootTarget;
    RuleObject* rlShootTarget;

    Method* mtShootTarget;

    void ShootTarget() { Target_->atIsShot->setValue(true); }

    FW2Marksman(std::shared_ptr<FW2Target> Target) : Target_{Target}
    {
        mtShootTarget =
            new MethodPointer<FW2Marksman>(this, &FW2Marksman::ShootTarget);
    }
};

class MarksmanApp : public NOPApplication
{
   public:
    MarksmanApp(int count);

    virtual ~MarksmanApp();

   public:
    void initStartApplicationComponents();

    void initFactBase();

    void initRules();

    void initSharedEntities();

    void codeApplication();

   public:
    std::shared_ptr<FW2Referee> referee;
    std::vector<std::shared_ptr<FW2Target>> targets;
    std::vector<std::shared_ptr<FW2Marksman>> marksmen;
    Premise* prRefereeReady;
    int elements;
};

struct NOP2Sensor : public FBE
{
    inline static std::atomic<int> counter{0};
    Boolean* atIsActivated;
    Boolean* atIsRead;

    Premise* prIsActivated;
    Premise* prIsNotRead;

    Instigation* inSensor;
    RuleObject* rlSensor;

    Method* mtSensor;

    NOP2Sensor()
    {
        BOOLEAN(this, atIsActivated, false);
        BOOLEAN(this, atIsRead, false);
        mtSensor =
            new MethodPointer<NOP2Sensor>(this, &NOP2Sensor::SensorMethod);
        PREMISE(this->prIsActivated, this->atIsActivated, true,
                Premise::EQUAL, Premise::STANDARD, false);
        PREMISE(this->prIsNotRead, this->atIsRead, false, Premise::EQUAL,
                Premise::STANDARD, false);
        INSTIGATION_NAMED(this->inSensor, this->mtSensor);
        RULE(this->rlSensor, SingletonScheduler::getInstance(),
             Condition::CONJUNCTION);
        this->rlSensor->addPremise(this->prIsActivated);
        this->rlSensor->addPremise(this->prIsNotRead);
        this->rlSensor->addInstigation(this->inSensor);
        this->rlSensor->end();
    }

    ~NOP2Sensor()
    {
        delete (atIsActivated);
        delete (atIsRead);

        delete (prIsActivated);
        delete (prIsNotRead);

        delete (inSensor);
        delete (rlSensor);

        delete (mtSensor);
    }

    void Read() const { atIsRead->setValue(true); }
    void Activate() const
    {
        atIsActivated->setValue(true);
        atIsRead->setValue(false);
    }
    void Deactivate() const { atIsActivated->setValue(false); }
    void SensorMethod()
    {
        Read();
        Deactivate();
        ++counter;
    }
};

class SensorApp : public NOPApplication
{
   public:
    SensorApp(int count);

    virtual ~SensorApp();

   public:
    void initStartApplicationComponents();

    void initFactBase();

    void initRules();

    void initSharedEntities();

    void codeApplication();

    int elements{0};

   public:
    std::vector<std::shared_ptr<NOP2Sensor>> sensors;
};

#endif
