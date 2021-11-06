#pragma once
#include <iostream>
#include "Hill.h"
using namespace std;

class Jumper
{
public:
    string name, surname, nationality;
    int takeoffPowerS, takeoffTechniqueS;
    int takeoffPower, takeoffTechnique;
    int lean, flightStyle;
    int flightTechniqueS, flightTechnique;
    int landSkill, landStyle, landType;
    double landRating, takeoffPowerDiff;
    int form;
    int gate, gateDiff;
    double distance, toBeat;
    double judges[5], minJudge, maxJudge, wind, windB, windBonus, judgeRating, judgesPoints, judgesAll;
    double points, compensationGate, compensationWind;
    bool dsq;
    int importance;
    Hill hill;

    void setup();
    void setTakeoffPower();
    void setTakeoffTechnique();
    void setFlightTechnique();
    void setGateAndWindMeters();
    void setPoints();
    void setGate();
    void land();
    void showResult();
    void showHideInfo();
    void showDistanceAndToBeat();
    void basicDistance();
    void setToBeat();
    void jump();
    void setHill(Hill &h);
};