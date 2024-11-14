#include <iostream>
#include <fstream>
#include "player.h"
using namespace std;

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
        getline(inFile, readFile, '#'); // ignore Y choice section
        getline(inFile, readFile, '#');
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



int main () {
    int i = 1;
    Player player;
    ifstream inFile("../chance" + to_string(i) + ".txt");

     if (!inFile) {

        cout << "Error reading the file." << endl;

    } else {

        parseEvent(inFile, player);
    
    }

    // divider
    cout << string(15, '#');
    cout << endl;

    // print modified result (org is 0, 0, 0)
    player.printStat();

    // REMEMBER TO CLOSE FILE!
}
