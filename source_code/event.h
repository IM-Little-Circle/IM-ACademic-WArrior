// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"

using namespace std;

/*
using std::string;
using std::ifstream;
using std::cin;
using std::cout;
*/


class Event {
    private:
        int x;
        int y;
        
    public:
        Event();
        char* readPlot();
};

Event::Event() {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
}

char* Event::readPlot()
{
    char* str = NULL;
    ifstream in("../chance1.txt");

    //for(int i = 0; i < 9; i++)
    //    in.ignore();
    
    in >> str;

    if(in.fail())
        return "Event file NOT FOUND"; // fix this part
    else
        return str;
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
