#pragma once
#include "NOPFramework.h"

struct OOPArcher
{
    bool bAppleIsReady{ false };
    bool bBowIsDrawn{ true };

    void ShootApple() { bAppleIsReady = false; };
    void DrawBow() { bBowIsDrawn = true; };
};


struct NOPArcher
{
    NOP::SharedAttribute<bool> atAppleReady{ NOP::BuildAttribute<bool>(false) };
    NOP::SharedPremise prAppleReady{ NOP::BuildPremise<bool>(atAppleReady, true, std::equal_to<>()) };
    NOP::SharedCondition cnShotReady{ NOP::BuildCondition(CONDITION(*prAppleReady), prAppleReady) };
    NOP::Method mtShootApple{ METHOD(atAppleReady->SetValue(false);) };
    NOP::SharedInstigation inShootApple{NOP::BuildInstigation(mtShootApple)};
    NOP::SharedAction acShotReady{ NOP::BuildAction(inShootApple) };
    NOP::SharedRule rlDrawBow{ NOP::BuildRule(cnShotReady, acShotReady) };
};

struct NOPReferee
{
    NOP::SharedAttribute<bool> atReady{ NOP::BuildAttribute<bool>(false) };
};

struct NOPTarget
{
    NOP::SharedAttribute<bool> atReady{ NOP::BuildAttribute<bool>(false) };
    NOP::SharedAttribute<bool > atIsShot{ NOP::BuildAttribute<bool>(false) };
};

struct NOPMarksman
{
    std::shared_ptr<NOPReferee> Referee_;
    std::shared_ptr<NOPTarget> Target_;

    NOP::SharedPremise prRefereeReady{ NOP::BuildPremise<bool>(Referee_->atReady, true, NOP::Equal()) };
    NOP::SharedPremise prTargetReady{ NOP::BuildPremise<bool>(Target_->atReady, true, NOP::Equal()) };
    NOP::SharedPremise prTargetShot{ NOP::BuildPremise<bool>(Target_->atIsShot, true, NOP::Equal()) };

    NOP::SharedCondition cnCanShoot{ NOP::BuildCondition(CONDITION(*prTargetReady && *prRefereeReady && !(*prTargetShot)),
        prTargetReady, prRefereeReady, prTargetShot) };
    NOP::Method mtShootTarget{ METHOD(Target_->atIsShot->SetValue(true);) };
    NOP::SharedInstigation inShootTarget{ NOP::BuildInstigation(mtShootTarget) };
    NOP::SharedAction acShootTarget{ NOP::BuildAction(inShootTarget) };
    NOP::SharedRule rlShootTarget{ NOP::BuildRule(cnCanShoot, acShootTarget) };

    NOPMarksman(std::shared_ptr<NOPReferee> Referee, std::shared_ptr<NOPTarget> Target) :
                Referee_{std::move(Referee)}, Target_{std::move(Target)}
    {
    }
};

struct OOPTarget
{
    bool Ready{ false };
    bool IsShot{ false };
};

struct OOPReferee
{
    bool Ready{ false };
};

struct OOPMarksman
{
    std::shared_ptr<OOPReferee> Referee;
    std::shared_ptr<OOPTarget> Target;

    OOPMarksman(std::shared_ptr<OOPReferee> Referee, std::shared_ptr<OOPTarget> Target) :
        Referee{ std::move(Referee) }, Target{ std::move(Target) }
    {

    }

    [[nodiscard]] bool CheckCanShoot() const
    {
        return (Referee->Ready) && (Target->Ready) && !(Target->IsShot);
    }

    void Shoot() const
    {
        Target->IsShot = true;
    }
};
