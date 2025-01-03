#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "event.h"
using namespace std;

extern const int CHANCE_CNT; //number of chances, must >= 1
extern const int DESTINY_CNT; //number of destinies, must >= 1

void displayEvent(ifstream& inFile) {
    string readFile;
    getline(inFile, readFile, '#');
    cout << readFile;
}

void displayChoiceChance(ifstream& inFile, string choice) {
    string readFile;

    if ((choice == "Y") || (choice == "y")) {
        // chosen Y
        getline(inFile, readFile, '#');
        cout << readFile;
    }
    else {
        //chosen N
        getline(inFile, readFile, '#'); // ignore Y choice section
        getline(inFile, readFile, '#');
        cout << readFile;
    }
}

void displayChoiceDestiny(ifstream& inFile, string choice) {
    string readFile;

    //forced to choose Y
    getline(inFile, readFile, '#');
    cout << readFile;
}

void modifyParameters(Player& player, int parameters[], string choice) {
    int oriAca = player.getAcademic();
    int oriSoc = player.getSocial();
    int oriEmo = player.getEmo();
    if (choice == "Y" || choice == "y") {
        player.modifyAcademic(parameters[0]);
        player.modifySocial(parameters[1]);
        player.modifyEmo(parameters[2]);
    }
    else {
        player.modifyAcademic(parameters[3]);
        player.modifySocial(parameters[4]);
        player.modifyEmo(parameters[5]);
    }
    player.printStatRight(oriAca, oriSoc, oriEmo);
}

void parseChance(ifstream& inFile, Player& player, int& skillNumber) {
    string choice = "";

    int parameters[6] = {0}; // acaTrue, socTrue, emoTrue, acaFalse, socFalse, emoFalse
    for (int i = 0; i < 6; i++) {
        inFile >> parameters[i];
    }

    // print the event
    displayEvent(inFile);

    // choose [Y | N]
    while (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) {
        cout << string(30, ' ');
        cin >> choice;
        if (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) {
            cout << string(30, ' ') << "Wrong input. Please try again.\n";
        }
    }

    // print result based on choice
    displayChoiceChance(inFile, choice);
    modifyParameters(player, parameters, choice);
    cout << string(30, ' ');
    player.getExp(10);
    cout << endl;
    skillNumber = getSkillNum(inFile, choice);
}

void parseDestiny(ifstream& inFile, Player& player, int& skillNumber) {
    const string choice = "Y"; //forced to choose Y

    int parameters[3] = {0}; // acaTrue, socTrue, emoTrue
    for (int i = 0; i < 3; i++) {
        inFile >> parameters[i];
    }

    // print the event
    displayEvent(inFile);

    // print result based on choice
    //displayChoiceChance(inFile, choice);
    modifyParameters(player, parameters, choice);
    cout << string(30, ' ');
    player.getExp(10);
    cout << endl;
    skillNumber = getSkillNum(inFile, choice);
}

int getSkillNum(ifstream& inFile, string choice) {
    string readFile;

    if ((choice == "Y") || (choice == "y")) {
        // chosen Y
        getline(inFile, readFile, '#'); //ignore consequences of chossing N
        getline(inFile, readFile, '#');
        return stoi(readFile);
    }
    else {
        //chosen N
        getline(inFile, readFile, '#'); // ignore Y choice section
        getline(inFile, readFile, '#');
        return stoi(readFile);
    }
}


void triggerChance(Player& player, bool triggeredChance[], int& skillNumber) {
    srand(time(NULL));
    int i = -1; //note that i will be 1-based for file, but 0-based for array
    bool allTriggered = true;
    do {
        i = rand() % (CHANCE_CNT - 1 + 1) + 1; //i = a random number between 1 and CHANCE_CNT
        for (int j = 0; j < CHANCE_CNT; j++) {
            if (!triggeredChance[j]) {
                allTriggered = false;
                break;
            }
        }
        if(allTriggered) {
            cout << "ALL triggered" << endl;
            break;
        }
    } while (triggeredChance[i - 1]); //re-roll
    
    if (!allTriggered) {
        triggeredChance[i - 1] = true;
        ifstream inFile("../assets/chance/chance" + to_string(i) + ".txt");

        if (inFile.fail()) {
            cout << "File not found\n";
            return;
        }
        
        parseChance(inFile, player, skillNumber);
        inFile.close();
    }
    else {
        cout << "你的大學生活夠精彩啦，休息一下，好好去面對考試吧~";
    }
}

void triggerDestiny(Player& player, bool triggeredDestiny[], int& skillNumber) {
    srand(time(NULL));
    int i = -1; //note that i will be 1-based for file, but 0-based for array
    bool allTriggered = true;
    do {
        i = rand() % (DESTINY_CNT - 1 + 1) + 1; //i = a random number between 1 and DESTINY_CNT
        for (int j = 0; j < DESTINY_CNT; j++) {
            if (!triggeredDestiny[j]) {
                allTriggered = false;
                break;
            }
        }
        if(allTriggered) {
            cout << "ALL triggered" << endl;
            break;
        }
    } while (triggeredDestiny[i - 1]); //re-roll
    
    if (!allTriggered) {
        triggeredDestiny[i - 1] = true;
        ifstream inFile("../assets/destiny/destiny" + to_string(i) + ".txt");

        if (inFile.fail()) {
            cout << "File not found\n";
            return;
        }

        parseDestiny(inFile, player, skillNumber);

        inFile.close();
    }
    else {
        cout << "陽光透過樹梢灑落下來，今天難得放晴。走在涼爽校園裡，深吸一口氣，連空氣都覺得是甜的。";
    }
}
