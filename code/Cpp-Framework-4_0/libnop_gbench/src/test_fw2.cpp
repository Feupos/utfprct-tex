#ifdef LIBNOP_FW2_TEST_ENABLE

#include "test_fw2.h"

#include <iostream>

MarksmanApp::MarksmanApp(int count) : NOPApplication(), elements{count}
{
    initStartApplicationComponents();
}

MarksmanApp::~MarksmanApp(void) {}

void MarksmanApp::initStartApplicationComponents()
{
    SingletonFactory::changeStructure(SingletonFactory::NOPVECTOR);
    SingletonScheduler::changeScheduler(SchedulerStrategy::NO_ONE);
}

void MarksmanApp::initFactBase()
{
    referee = std::make_shared<FW2Referee>();
    for (int i = 0; i < elements; i++)
    {
        auto target = std::make_shared<FW2Target>();
        auto marksman = std::make_shared<FW2Marksman>(target);
        targets.push_back(target);
        marksmen.push_back(marksman);
    }
}
void MarksmanApp::codeApplication()
{
    for (auto& it : targets)
    {
        it->atReady->setValue(true);
    }
    referee->atReady->setValue(true);
}
void MarksmanApp::initSharedEntities()
{
    PREMISE(prRefereeReady, referee->atReady, true, Premise::EQUAL,
            Premise::STANDARD, false);
    for (int i = 0; i < elements; i++)
    {
        PREMISE(marksmen[i]->prTargetReady, targets[i]->atReady, true,
                Premise::EQUAL, Premise::STANDARD, false);
        PREMISE(marksmen[i]->prTargetNotShot, targets[i]->atReady, false,
                Premise::EQUAL, Premise::STANDARD, false);
    }
}

void MarksmanApp::initRules()
{
    Scheduler* scheduler = SingletonScheduler::getInstance();
    for (int i = 0; i < elements; i++)
    {
        RULE(marksmen[i]->rlShootTarget, scheduler, Condition::CONJUNCTION);
        marksmen[i]->rlShootTarget->addPremise(marksmen[i]->prTargetReady);
        marksmen[i]->rlShootTarget->addPremise(marksmen[i]->prTargetNotShot);
        marksmen[i]->rlShootTarget->addPremise(prRefereeReady);
        marksmen[i]->rlShootTarget->addInstigation(marksmen[i]->inShootTarget);
        marksmen[i]->rlShootTarget->end();
    }
}

SensorApp::SensorApp(int count) : NOPApplication(), elements{count}
{
    initStartApplicationComponents();
    initFactBase();
    initSharedEntities();
    initRules();
}

SensorApp::~SensorApp(void) {}

void SensorApp::initStartApplicationComponents()
{
    SingletonFactory::changeStructure(SingletonFactory::NOPVECTOR);
    SingletonScheduler::changeScheduler(SchedulerStrategy::NO_ONE);
}

void SensorApp::initFactBase()
{
    for (int i = 0; i < elements; i++)
    {
        sensors.push_back(std::make_shared<NOP2Sensor>());
    }
}
void SensorApp::codeApplication() {}
void SensorApp::initSharedEntities() {}

void SensorApp::initRules() {}

#endif
