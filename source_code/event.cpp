#include <iostream>
#include <fstream>
#include <string>
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
    if (choice == "Y") {
        player.modifyAcademic(parameters[0]);
        player.modifySocial(parameters[1]);
        player.modifyEmo(parameters[2]);
    }
    else {
        player.modifyAcademic(parameters[3]);
        player.modifySocial(parameters[4]);
        player.modifyEmo(parameters[5]);
    }
    player.printStat(oriAca, oriSoc, oriEmo);
}

void parseChance(ifstream& inFile, Player& player) {
    string choice = "";

    int parameters[6] = {0}; // acaTrue, socTrue, emoTrue, acaFalse, socFalse, emoFalse
    for (int i = 0; i < 6; i++) {
        inFile >> parameters[i];
    }

    // print the event
    displayEvent(inFile);

    // choose [Y | N]
    while (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) {
        cin >> choice;
        if (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) cout << "Wrong input. Please try again.\n";
    }

    // print result based on choice
    displayChoiceChance(inFile, choice);
    modifyParameters(player, parameters, choice);
    player.getExp(10);
}

void parseDestiny(ifstream& inFile, Player& player) {
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
    player.getExp(10);
}

int getSkillNum(ifstream& inFile, string choice) {
    string readFile;

    if ((choice == "Y") || (choice == "y")) {
        // chosen Y
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


void triggerChance(Player& player, bool triggeredChance[]) {
    int i = -1; //note that i will be 1-based for file, but 0-based for array
    do {
        i = rand() % (CHANCE_CNT - 1 + 1) + 1; //i = a random number between 1 and CHANCE_CNT
        bool allTriggered = false;
        for (int j = 0; j < CHANCE_CNT; j++) {
            if (!triggeredChance[j]) {
                allTriggered = false;
                break;
            }
            allTriggered = true;
        }
        if(allTriggered) {
            cout << "ALL triggered" << endl;
            break;
        }
    } while (triggeredChance[i - 1]); //re-roll
    

    triggeredChance[i - 1] = true;
    ifstream inFile("../assets/chance/chance" + to_string(i) + ".txt");
    cout << "Chance " << i << " triggered\n"; //shall be deleted as game development finishes

    if (inFile.fail()) {
        cout << "File not found\n";
        return;
    }
    
    parseChance(inFile, player);
    //player.printStat();

    inFile.close();
}

void triggerDestiny(Player& player, bool triggeredDestiny[]) {
    int i = -1; //note that i will be 1-based for file, but 0-based for array
    do {
        i = rand() % (DESTINY_CNT - 1 + 1) + 1; //i = a random number between 1 and DESTINY_CNT
        bool allTriggered = false;
        for (int j = 0; j < DESTINY_CNT; j++) {
            if (!triggeredDestiny[j]) {
                allTriggered = false;
                break;
            }
            allTriggered = true;
        }
        if(allTriggered) {
            cout << "ALL triggered" << endl;
            break;
        }
    } while (triggeredDestiny[i - 1]); //re-roll
    

    triggeredDestiny[i - 1] = true;
    ifstream inFile("../assets/destiny/destiny" + to_string(i) + ".txt");
    cout << "Destiny " << i << " triggered\n"; //shall be deleted as game development finishes

    if (inFile.fail()) {
        cout << "File not found\n";
        return;
    }

    parseDestiny(inFile, player);
    //player.printStat();

    inFile.close();
}
