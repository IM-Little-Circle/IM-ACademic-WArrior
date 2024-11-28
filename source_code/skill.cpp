#include "skill.h"
#include <fstream>
using namespace std;
/*
先選擇新獲得的skill
再替換現有的skill
好像不會放在skill.cpp而是應該放在Player.cpp
*/

// added skill 4-6 for testing

Skill::Skill(string skillName, string skillType, int restRound, int percent)
{
    this->skillName = skillName;
    this->skillType = skillType;
    this->restRound = restRound;
    this->percent = percent;
    this->coolRound = 0;
}

Skill::Skill()
{
    skillName = "";
    skillType = "";
    percent = 100;
    restRound = 1;
    coolRound = 0;
}

string Skill::getType(){
    return skillType;
}

string Skill::getName(){
    return skillName;
}

void Skill::printSkill() {
    cout << skillName << " " << skillType << " " << restRound << "," << percent << endl;
}

int Skill::getCoolRound(){
    return coolRound;
}

int Skill::getPercent(){
    return percent;
}