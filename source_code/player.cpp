#include "player.h"
//#include "skill.h"
//#include "entity.h"
#include <fstream>
// entity member and related functions


Player::Player(int hp, int atk, int def) : Entity(hp, atk, def) {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
	socialBuff = social / 100;
	studyBuff = academic / 100;
    healBuff = (100 - emo) / 100;
	mentalRes = (100 - emo) / 100;
    skill[0] = getSkill(1);
    skill[1] = getSkill(2);
    skill[2] = getSkill(3);
}


void Player::modifyAcademic(int change) {
    academic += change;
}


void Player::modifySocial(int change) {
    social += change;
}


void Player::modifyEmo(int change) {
    emo += change;
    if (emo < 0) emo = 0;
    if (emo >= 100) emo = 100;
}

int Player::getAcademic() {
    return this->academic;
}

int Player::getSocial() {
    return this->social;
}

int Player::getEmo(){
    return this->emo;
}

void Player::updateStatus() {
	socialBuff = static_cast<double>(social + emo) / 100;
    studyBuff = static_cast<double>(academic + emo) / 100;
    mentalRes = static_cast<double>(emo) / 100;
    cout << "now socialBuff = " << socialBuff << endl;
    cout << "studyBuff = " << studyBuff << endl;
    cout << "mentalRes = " << mentalRes << endl;
}

void Player::fullRecover(){
    hpCurr = hpMax;
}

void Player::printStat() {
    cout << "ACA " << academic << "\nSOC " << social << "\nEMO " << emo << endl;
}


// to set initial stat
// (so we don't have to come back to player.h to change every time)
// tbh you can just set the initial value at initialization
void Player::setInitialStat(int aca, int soc, int e) {
    academic = aca;
    social = soc;
    emo = e;
    updateStatus();
}

void Player::levelUp() {
	level++;
	atk += level * 1.2;
	def += level;
	hpMax += level * 2;
	hpCurr = hpMax;
	cout << "Level up! " << endl;
	cout << level-1 << "  --->  " << level << endl;
}

void Player::getExp(int experience){
    exp += experience;
}

/*
最難的是getskill這邊理論上要有介面的切換
*/
Skill* Player::getSkill(int filenumber){
    string skillName, skillType;
    int restRound, percent;
    ifstream inFile("../assets/skill/skill" + to_string(filenumber) + ".txt");
    if (inFile.fail()) {
        cout << "File not found\n";
    }
    else {
        getline(inFile, skillName);
        getline(inFile, skillType);
        inFile >> restRound >> percent;
    }
    /*
    放skill
    skillName;
    skillType;
    restRound;
    */
   return new Skill(skillName, skillType, restRound, percent);
}

void Player::replaceSkill(int filenumber){
    
    /*cout << "you get a new skill!" << endl;
    輸出得到的skill

    列出現在有的skill，讓他輸入1、2、3決定要換掉哪一個
    */
    string changeNumber;
    cin >> changeNumber;

    // 以下的偵測條件有點白癡，看需不需要改？
    while (!(changeNumber == "1" || changeNumber == "2" || changeNumber == "3")){
            cout << "Wrong input, please choose your number again" << endl;
            cin >> changeNumber;
    }
    cin.ignore();
    cout << "Replaced " << skill[stoi(changeNumber)-1]->getName();
    skill[stoi(changeNumber)-1] = getSkill(filenumber);
    cout << "with " <<  skill[stoi(changeNumber)-1]->getName() << "!\n";

}

void Player::useSkill(Entity enemy, Skill skill){
    if (skill.getCoolRound() != 0) return; //輸錯要給甚麼回饋?
    if (skill.getType() == "heal"){
        heal(skill.getPercent());
    }
    else if (skill.getType() == "studyAttack"){
        studyAttack(enemy, skill.getPercent());
    }
    else{
        socialAttack(enemy, skill.getPercent());
    }
}

/*
void Player::useSkill(Entity enemy, int chooseNumber){
    Skill usedSkill = player.skill[chooseNumber];
    if (usedSkill.getCoolRound() != 0) return; //輸錯要給甚麼回饋?
    if (usedSskill.getType() == "heal"){
        heal(usedSkill.getPercent());
    }
    else if (usedSkill.getType() == "studyAttack"){
        studyAttack(enemy, usedSkill.getPercent());
    }
    else{
        socialAttack(enemy, usedSkill.getPercent());
    }
}*/

// added for testing

void Player::printSkill(int skillnumber) {
    if (skillnumber >= 0 && skillnumber < 3) {
        skill[skillnumber]->printSkill();
    }
    else cout << "error index!\n";
}

void Player::skillCool(){
    for (int i = 0; i < 3; i++){
        skill[i]->skillCool();
    }
}