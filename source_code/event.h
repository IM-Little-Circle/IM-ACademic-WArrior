#include <iostream>
#include <fstream>
#include <cstdlib>
#include "battle.h"
using namespace std;

const int CHANCE_CNT = 16; //number of chances, must >= 1       
const int DESTINY_CNT = 12; //number of destinies, must >= 1    //17 // for testing: 12

void displayEvent(ifstream& inFile);
void displayChoiceChance(ifstream& inFile, string choice);
void displayChoiceDestiny(ifstream& inFile, string choice);
void modifyParameters(Player& player, int parameters[], string choice);
void parseChance(ifstream& inFile, Player& player, int& skillNumber);
void parseDestiny(ifstream& inFile, Player& player, int& skillNumber);
int getSkillNum(ifstream& inFile, string choice);
void triggerChance(Player& player, bool triggeredChance[], int& skillNumber);
void triggerDestiny(Player& player, bool triggeredDestiny[], int& skillNumber);