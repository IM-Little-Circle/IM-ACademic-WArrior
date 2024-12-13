#include "skill.h"
#include <fstream>
using namespace std;

Skill::Skill(string skillName, string skillType, int coolRound, int percent){
    this->skillName = skillName;
    this->skillType = skillType;
    this->restRound = 0;
    this->percent = percent;
    this->coolRound = coolRound;
}

Skill::Skill(int filenumber){
    string skillName, skillType;
    int restRound, percent;
    ifstream inFile("../sources/skill/skill" + to_string(filenumber) + ".txt");
    if (inFile.fail()) {
        cout << "File not found\n";
    }
    else {
        getline(inFile, skillName);
        getline(inFile, skillType);
        inFile >> coolRound >> percent;
    }
    this->skillName = skillName;
    this->skillType = skillType;
    this->restRound = 0;
    this->percent = percent;
    this->coolRound = coolRound;
}

Skill::Skill(){
    skillName = "";
    skillType = "";
    percent = 100;
    restRound = 0;
    coolRound = 1;
}

string Skill::getType(){
    return skillType;
}

string Skill::getName(){
    return skillName;
}

void Skill::printnewSkill() {
    cout << "⋆｡° " << skillName << " °｡⋆" << endl;
    cout << "◆  技能類型: " << skillType << endl;
    cout << "◆  技能冷卻回合: " << coolRound << endl;
    cout << "◆  倍率: " << percent << endl;
    cout << endl;
}

void Skill::printSkill() {
    cout << skillName << "\n" << "技能類型: " << skillType << "\n剩餘冷卻回合: " << restRound << "\n倍率: " << percent << endl;
    cout << endl;
}

int Skill::getCoolRound(){
    return coolRound;
}

int Skill::getRestRound(){
    return restRound;
}

int Skill::getPercent(){
    return percent;
}

void Skill::skillCool(){
    restRound = max(restRound - 1, 0);
}

void Skill::coolReset(){
    restRound = 0;
}

void Skill::cool(){
    restRound = coolRound + 1;
}

void Skill::printName(){
    cout << skillName;
}

void Skill::printType(){
    cout << skillType;
}

void Skill::printCoolRound(){
    cout << coolRound;
}

void Skill::printPercent(){
    cout << percent;
}