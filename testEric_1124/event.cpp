#include "event.h"
using namespace std;

const int chanceCnt = 2; // number of chances, must >= 1
const int destinyCnt = 2; // number of destinies, must >= 1

Event::Event() {
    // empty constructor
}

// event functions //
void displayEvent(ifstream& inFile) {
    string readFile;
    getline(inFile, readFile, '#');
    cout << readFile;
}

void displayChoice(ifstream& inFile, string choice) {
    string readFile;

    if (choice == "Y") {
        // chosen Y
        getline(inFile, readFile, '#');
        cout << readFile;
    }
    else {
        //chosen N
        std::getline(inFile, readFile, '#'); // ignore Y choice section
        std::getline(inFile, readFile, '#');
        cout << readFile;
    }
}

void modifyParameters(Player& player, int parameters[], string choice) {
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
}

void parseEvent(ifstream& inFile, Player& player) {
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
    displayChoice(inFile, choice);
    modifyParameters(player, parameters, choice);
}

void Event::triggerChance(Player& player) {
    ifstream inFile;
    int i = rand()%(chanceCnt - 1 + 1) + 1; //i = a random number between 1 and chanceCnt
    ifstream inFile("../assets/chance" + to_string(i) + ".txt");
    cout << "Chance " << i << " triggered\n";

    if (inFile.fail()) {
        cout << "File not found\n";
        return;
    }

    parseEvent(inFile, player);
    player.printStat();

    inFile.close();
}