#include "App.h"
#include "JumpData.h"
#include "Jumper.h"
#include "Competition.h"
#include "CompetitionConfig.h"
#include "Hill.h"

#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

#define sclear system("cls")
#define getchText cout<<"Kliknij dowolny przycisk... "

App::App()
{
}

App::~App()
{
}

void App::start()
{
    using namespace std;
    loadJumpersFromFile();
    loadHillsFromFile();
    loadCompetitionConfigFromFile();

    while (true)
    {
        cout << "Witaj w symulatorze skok�w narciarskich! Co chcesz zrobi�?\n";
        cout << "1. Symuluj sezon (niedost�pne)\n2. Symuluj pojedynczy konkurs\n3. Symyluj pojedyncze skoki (niedost�pne)\n4. Ustawienia (niedost�pne)";

        switch (numberChoice("\n", 1))
        {
        case 1:
            break;
        case 2:
            singleCompetitionChoice();
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }
    }

    getch();
}

void App::loadJumpersFromFile()
{
    using namespace std;
    string name, surname, nationality, tps, tts, fts, fs, ls, f;

    ifstream ifs;
    ifs.open("resources/jumpers.csv");
    if (ifs.good() == false)
    {
        cout << "Nie uda�o si� otworzy� pliku jumpers.csv!\n";
        getch();
    }

    jumpersList.erase(jumpersList.begin(), jumpersList.end());

    while (getline(ifs, name, ','))
    {
        getline(ifs, surname, ',');
        getline(ifs, nationality, ',');
        getline(ifs, tps, ',');
        getline(ifs, tts, ',');
        getline(ifs, fts, ',');
        getline(ifs, fs, ',');
        getline(ifs, ls, ',');
        getline(ifs, f);
        jumpersList.push_back(Jumper(name, surname, nationality, stoi(tps), stoi(tts), stoi(fts), stoi(fs), stoi(ls), stoi(f)));
    }
    ifs.close();
}

void App::loadHillsFromFile()
{
    using namespace std;
    string name, country, k, hs, gp, fwp, md, sd, otp, tpi, ttm, ftm;
    ifstream ifs;
    ifs.open("resources/hills.csv");
    if (ifs.good() == false)
        cout << "Nie uda�o si� otworzy� pliku hills.csv!\n";

    hillsList.erase(hillsList.begin(), hillsList.end());

    while (getline(ifs, name, ','))
    {
        getline(ifs, country, ',');
        getline(ifs, k, ',');
        getline(ifs, hs, ',');
        getline(ifs, gp, ',');
        getline(ifs, fwp, ',');
        getline(ifs, md, ',');
        getline(ifs, sd, ',');
        getline(ifs, otp, ',');
        getline(ifs, tpi, ',');
        getline(ifs, ttm, ',');
        getline(ifs, ftm);
        hillsList.push_back(Hill(name, country, stoi(k), stoi(hs), stod(md), stod(gp), stod(fwp), stod(sd), stod(ttm), stod(ftm), stod(otp), stod(tpi)));
    }
    ifs.close();
}

void App::loadCompetitionConfigFromFile()
{
    using namespace std;

    ifstream ifs;
    ifs.open("resources/competitionConfig.csv");
    if (ifs.good() == false)
        cout << "Nie uda�o si� otworzy� pliku competitionConfig.csv!\n";

    competitionConfigList.erase(competitionConfigList.begin(), competitionConfigList.end());

    string line;
    vector<string> lines;
    vector<string> result;

    while (getline(ifs, line))
    {
        if (line.size() > 0)
            lines.push_back(line);
    }
    for (const auto &l : lines)
    {
        CompetitionConfig config;
        boost::split(result, l, boost::is_any_of(","));
        config.setName(result[0]);
        config.setIsQualifications(stoi(result[1]));
        result.erase(result.begin(), result.begin() + 2);
        for (const auto &num : result)
        {
            config.addRoundsData(stoi(num));
        }
        competitionConfigList.push_back(config);
    }

    ifs.close();
}

void App::singleCompetitionChoice()
{
    using std::cout;

    sclear;
    cout << "Wybierz skocznie: \n";
    selectHill(&singleCompetition);
    sclear;

    cout << "Wybierz konfiguracj� konkursu: \n";
    selectCompetitionConfig(&singleCompetition);
    sclear;

    cout << "Lista startowa konkursu: \n";
    showJumpers();
    getch();
    getchText;
    sclear;

    singleCompetition.loadParametersFromFile();
    cout << "Parametry konkursu: (1 - tak, 0 - nie)\n";
    singleCompetition.showParameters();
    getch();
    sclear;

    cout<<"Rozpocz�to konkurs...\n";
    Sleep(1200);
    singleCompetition.setJumpers(jumpersList);
    singleCompetition.startCompetition();

    getch();
}

void App::selectHill(Competition *comp)
{
    showHills();
    comp->setHill(&hillsList[numberChoice("\n", 1) - 1]);
    std::cout << "Wybrano skoczni� " << comp->getHill()->getName() << " K" << comp->getHill()->getKPoint() << " HS" << comp->getHill()->getHsPoint() << "\n";
    Sleep(1200);
}

void App::selectCompetitionConfig(Competition *comp)
{
    showCompetitionConfigs();
    comp->setCompetitionConfig(competitionConfigList[numberChoice("\n", 1) - 1]);
    std::cout << "Wybrano konfiguracj� " << comp->getCompetitionConfig().getName() << "\n";
    Sleep(1200);
}

void App::showJumpers()
{
    using std::cout;

    int i = 1;
    for (const auto &jp : jumpersList)
    {
        cout << i << ". " << jp.getName() << " " << jp.getSurname() << " (" << jp.getNationality() << ")\n";
        i++;
    }
}
void App::showHills()
{
    using std::cout;

    int i = 1;
    for (const auto &hl : hillsList)
    {
        cout << i << ". " << hl.getName() << " (" << hl.getCountry() << ") K" << hl.getKPoint() << " HS" << hl.getHsPoint() << "\n";
        i++;
    }
}
void App::showCompetitionConfigs()
{
    using std::cout;

    int i = 1;
    for (const auto &cf : competitionConfigList)
    {
        cout << i << ". " << cf.getName() << " (" << cf.getRoundsCount() << " rundy ";
        if (cf.getIsQualifications())
            cout << "+ kwalifikacje) ";
        else
            cout << "bez kwalifikacji) ";

        cout << "(";
        for (const auto &r : cf.getRoundsData())
        {
            cout << r << ",";
        }
        cout << ")\n";
        i++;
    }
}

int App::numberChoice(std::string text, bool enter)
{
    using std::cin;
    using std::cout;

    int choice;

    cout << text;
    cout << "Wyb�r: ";

    if (enter)
    {
        cin >> choice;
    }
    else
        choice = getch() - '0';

    return choice;
}