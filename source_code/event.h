#include <iostream>
#include <fstream>
#include <cstdlib>
#include "battle.h"
using namespace std;

const int CHANCE_CNT = 2; //number of chances, must >= 1
const int DESTINY_CNT = 17; //number of destinies, must >= 1

void displayEvent(ifstream& inFile);
void displayChoiceChance(ifstream& inFile, string choice);
void displayChoiceDestiny(ifstream& inFile, string choice);
void modifyParameters(Player& player, int parameters[], string choice);
void parseChance(ifstream& inFile, Player& player);
void parseDestiny(ifstream& inFile, Player& player);
int getSkillNum(ifstream& inFile, string choice);
void triggerChance(Player& player, bool triggeredChance[]);
void triggerDestiny(Player& player, bool triggeredDestiny[]);
void triggerBattle(Player& player);