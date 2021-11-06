#include "Jumper.h"
#include "other.h"

void Jumper::setup()
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    colorText(15, name + " " + surname + " (" + nationality + ")\n");
    SetConsoleTextAttribute(hcon, 7);
}

void Jumper::jump()
{
    hill.startup();
    hill.setType();

    wind += normalRandom(0, hill.windChange);
    windB = wind + normalRandom(0, hill.windFaulty);

    setTakeoffPower();
    setTakeoffTechnique();
    setFlightTechnique();
    setGateAndWindMeters();

    int rd;

    if (flightStyle > 4)
        flightStyle = 2; // Styl "nowoczesne V 1"
    if (lean > 14)
        lean = 10;

    takeoffPowerDiff = (takeoffPower - hill.optimalTakeoffPower);

    if (takeoffPowerDiff < 0)
        (takeoffPowerDiff *= 0.6456);
    else
        takeoffPowerDiff *= 0.44;

    takeoffPowerDiff = round(takeoffPowerDiff);

    basicDistance();
    land();
    setPoints();
    setToBeat();
}

void Jumper::setTakeoffPower()
{
    if (takeoffPowerS > 120)
        takeoffPowerS = 120;
    if (takeoffPowerS < 1)
        takeoffPowerS = 1;

    takeoffPower = (takeoffPowerS);
    takeoffPower += normalRandom(0, 5);
    takeoffPower = round(takeoffPower);
    if (takeoffPower > 160)
        takeoffPower = 160;
    else if (takeoffPower < 1)
        takeoffPower = 1;
}
void Jumper::setTakeoffTechnique()
{
    if (takeoffTechniqueS > 120)
        takeoffTechniqueS = 120;
    if (takeoffTechniqueS < 1)
        takeoffTechniqueS = 1;

    takeoffTechnique = (takeoffTechniqueS * 0.980) + (form * 1.057);
    takeoffTechnique += normalRandom(0, 7);
    takeoffTechnique = round(takeoffTechnique);
    if (takeoffTechnique > 280)
        takeoffTechnique = 280;
    if (takeoffTechnique < 1)
        takeoffTechnique = 1;
}

void Jumper::setFlightTechnique()
{
    if (flightTechniqueS > 120)
        flightTechniqueS = 120;
    if (flightTechniqueS < 1)
        flightTechniqueS = 1;

    flightTechnique = (flightTechniqueS * 0.875) + (form * 1.162);
    if (flightStyle == 0)
        flightTechnique += randomInt(-17, -9);
    else if (flightStyle == 1)
        flightTechnique += randomInt(-3, 3);
    else if (flightStyle == 2)
        flightTechnique += randomInt(-4, 4);
    else if (flightStyle == 3)
        flightTechnique += randomInt(-5, 5);
    else if (flightStyle == 4)
        flightTechnique += randomInt(-6, 6);

    flightTechnique += normalRandom(0, 7);
    flightTechnique = round(flightTechnique);
    if (flightTechnique > 280)
        flightTechnique = 280;
    if (flightTechnique < 1)
        flightTechnique = 1;
}

void Jumper::setGateAndWindMeters()
{
    if (hill.gateMeters == (-1))
    {
        hill.gateMeters = (hill.gatePoints / hill.metersPoints);
    }
    if (hill.windMetersBack == (-1))
    {
        hill.windMetersBack = (hill.windMetersBack / hill.metersPoints);
    }
    if (hill.windMetersFront == (-1))
    {
        hill.windMetersFront = (hill.windMetersFront / hill.metersPoints);
    }
}

void Jumper::setPoints()
{
    if (hill.windComp == 1)
    {
        if (windB < 0)
            compensationWind = -windB * hill.windPointsBack;
        else if (windB > 0)
            compensationWind = -windB * hill.windPointsFront;
    }
    if (hill.gateComp == 1)
        compensationGate = (gateDiff)*hill.gatePoints;

    points = (hill.pointsForK + (hill.metersPoints * (distance - hill.kpoint)));
    if (hill.isJudges == 1)
        points += judgesAll;
    if (hill.gateComp == 1)
        points += compensationGate;
    if (hill.windComp == 1)
        points += compensationWind;

    if (points < 0)
        points = 0;
}

void Jumper::setGate()
{
    cout << "Podaj belke: ";
    cin >> gate;
}

void Jumper::land()
{
    int rd, rd1;

    landRating = landSkill + (form / 13) + (landStyle / 25);
    landRating += normalRandom(0, 3);

    if (landRating > 80)
        landRating = 80;
    else if (landRating < 1)
        landRating = 1;

    judgeRating = 4.9;
    judgeRating += (double)landStyle / 5.5;
    judgeRating += landRating / 20.755;
    judgeRating += ((distance - hill.kpoint) / hill.judgeDivider);

    judgeRating = (round(judgeRating) * 2) / 2;

    rd = randomInt(0, 100000);
    rd1 = 63000 - (landRating * 440);
    rd1 += ((distance - hill.maxdist) * 16 * hill.landDifficulty);

    //cout << "rd1: " << rd1 << endl;
    //getch();
    if (rd < rd1)
    {
        landType = 4;
        judgeRating -= (9 + (randomInt(1, 1) / 2));
    }
    else
    {
        rd = randomInt(1, 100000);
        rd1 = 63000 - (landRating * 440); // - (expernice * 300);
        rd1 += ((distance - hill.maxdist) * 16 * hill.landDifficulty);
        //cout << "rd1: " << rd1 << endl;
        //getch();
        if (rd < rd1)
        {
            landType = 3;
            judgeRating -= (7 + (randomInt(1, 1) / 2));
        }
        else
        {
            rd = randomInt(1, 100000);
            rd1 = 78000 - (landRating * 480); // - (expernice * 300);
            rd1 += ((distance - hill.maxdist) * 19 * hill.landDifficulty);

            //cout << "rd1: " << rd1 << endl;
            //getch();
            if (rd < rd1)
            {
                landType = 2;
                judgeRating -= randomInt(1, 2);
                rd = randomInt(1, 30);
                if (rd == 1)
                    judgeRating -= 1;
                else
                {
                    landType = 2;
                    judgeRating -= (randomInt(-1, 1) / 2);
                }
            }
            else
                landType = 1;
        }
    }
    if (hill.isJudges == 1)
    {
        for (auto &jdg : judges)
        {
            jdg = judgeRating;
            rd = randomInt(1, 5);
            if (rd == 1)
                jdg += (-0.5);
            if (rd == 2 || rd == 3 || rd == 4)
                jdg += (0);
            if (rd == 5)
                jdg += (0.5);

            rd = (randomInt(1, 20));
            if (rd == 1)
                jdg += (-1);
            if (rd == 2)
                jdg += (1);

            if (jdg > 20)
                jdg = 20;
            else if (jdg < 1)
                jdg = 1;
        }

        minJudge = judges[0];
        maxJudge = judges[0];
        for (auto jg : judges)
        {
            if (jg < minJudge)
                minJudge = jg;
            if (jg > maxJudge)
                maxJudge = jg;
        }
        judgesAll = 0;
        for (auto jg : judges)
        {
            judgesAll += jg;
        }
        judgesAll -= (minJudge + maxJudge);
    }
}

void Jumper::showResult()
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << name << " " << surname << " (" << nationality << ")" << endl;
    cout << "Odleglosc: " << distance << "m"
         << " (Belka " << gate << " (";

         int t = -gateDiff;
    if (t > 0)
    {
        colorText(2, "+");
        colorText(2, to_string(t));
    }
    if (t == 0)
    {
        colorText(7, "+0");
    }
    if (t < 0)
    {
        colorText(4, to_string(t));
    }
    SetConsoleTextAttribute(hcon, 15);
    cout << "))" << endl;

    if (hill.isJudges == 1)
    {
        cout << "| ";
        for (auto jdg : judges)
        {
            cout << jdg << " | ";
            Sleep(300);
        }
        cout << endl;
    }

    if (windB < 0)
    {
        colorText(12, "Wiatr: ");
        colorText(12, to_string(windB));
    }

    else if (windB > 0)
    {
        colorText(10, "Wiatr: ");
        colorText(10, to_string(windB));
    }
    else
    {
        colorText(7, "Wiatr: ");
        colorText(7, to_string(windB));
    }
    cout << endl;
    if (compensationGate < 0)
    {
        colorText(12, "Za belke: ");
        colorText(12, to_string(compensationGate));
    }
    else if (compensationGate > 0)
    {
        colorText(10, "Za belke: ");
        colorText(10, to_string(compensationGate));
    }
    else
    {
        colorText(7, "Za belke: ");
        colorText(7, to_string(compensationGate));
    }
    cout << endl;
    if (compensationWind < 0)
    {
        colorText(12, "Za wiatr: ");
        colorText(12, to_string(compensationWind));
    }
    else if (compensationWind > 0)
    {
        colorText(10, "Za wiatr: ");
        colorText(10, to_string(compensationWind));
    }
    else
    {
        colorText(7, "Za wiatr: ");
        colorText(7, to_string(compensationWind));
    }
    cout << endl;
    if ((compensationWind + compensationGate) < 0)
    {
        colorText(12, "Lacznie: ");
        colorText(12, to_string((compensationWind + compensationGate)));
    }
    else if ((compensationWind + compensationGate) > 0)
    {
        colorText(10, "Lacznie: ");
        colorText(10, to_string((compensationWind + compensationGate)));
    }
    else
    {
        colorText(7, "Lacznie: ");
        colorText(7, to_string((compensationWind + compensationGate)));
    }

    SetConsoleTextAttribute(hcon, 15);
    cout << "\nPunkty: " << points << endl;

    cout << "Skok zakonczony ";
    if (landType == 1)
        colorText(11, "telemarkiem");
    else if (landType == 2)
        colorText(3, "ladowaniem na dwie nogi");
    else if (landType == 3)
        colorText(5, "podporka");
    else if (landType == 4)
        colorText(12, "upadkiem");

    SetConsoleTextAttribute(hcon, 15);
}

void Jumper::showHideInfo()
{
    cout << "Moc wybicia: " << takeoffPower << ", Technika wybicia: " << takeoffTechnique << ", Technika lotu: " << flightTechnique << endl;
}

void Jumper::showDistanceAndToBeat()
{
    for (int i = 0; i <= distance; i++)
    {
        cout << "Do objecia prowadzenia: " << toBeat << endl;
        if (i == distance)
        {
            cout << "| " << i << "m |" << endl;
        }
        else
            cout << i << "m" << endl;

        if (distance - i < 5 + (randomInt(-12, 12)))
            Sleep(80.5);
        else if (distance - i < 10 + (randomInt(-12, 12)))
            Sleep(72);
        else if (distance - i < 25 + (randomInt(-12, 12)))
            Sleep(60);
        else if (distance - i < 45 + (randomInt(-12, 12)))
            Sleep(47);
        else if (distance - i < 70 + (randomInt(-12, 12)))
            Sleep(30);
        else if (distance - i < 100 + (randomInt(-12, 12)))
            Sleep(16);
        else if (distance - i < 150 + (randomInt(-12, 12)))
            Sleep(12);
        else
            Sleep(8);

        cls;
    }
    cls;
}

void Jumper::setHill(Hill &h)
{
    hill = h;
}
void Jumper::basicDistance()
{
    distance = hill.startDist;
    distance += (gate * hill.gateMeters);

    if (windB > 0)
        distance += (windB * hill.windMetersFront);
    else if (windB < 0)
        distance += (windB * hill.windMetersBack);

    distance -= (abs(hill.optimalTakeoffPower - takeoffPower) * hill.takeoffPowerImportance);
    distance += takeoffTechnique * hill.takeoffTechniqueMeters;
    distance += flightTechnique * hill.flightTechniqueMeters;

    for (int i = 0; i < 5; i++)
    {
        if (flightStyle == i)
        {
            distance += hill.flightStyleMeters[i];
        }
    }

    if (distance > hill.maxdist)
        distance = hill.maxdist + normalRandom(0, hill.maxdistRandom);
    distance = round(distance * 2) / 2;
}

void Jumper::setToBeat()
{
    toBeat = hill.leaderPoints - hill.pointsForK;
    if (hill.isJudges == 1)
        toBeat -= 54;

    if (hill.gateComp == 1)
        toBeat -= compensationGate;

    if (hill.windComp == 1)
        toBeat -= compensationWind;

    toBeat /= hill.metersPoints;
    toBeat += hill.kpoint;
    toBeat = ceil(toBeat * 2) / 2;
}