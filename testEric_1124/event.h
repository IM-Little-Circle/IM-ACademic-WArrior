// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
//we will decalre a chance and a destiny which both have the type of Event
//we wlll call functions in Event.h to manifist the consequences of encountering chances or destinies
//e.g. acaedmic, social, and emotional changes
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
        void triggerChance(Player& player);
        void displayEvent(ifstream& inFile);
        void displayChoice(ifstream& inFile, string choice);
        void modifyParameters(Player& player, int parameters[], string choice);
        void parseEvent(ifstream& inFile, Player& player);
};



