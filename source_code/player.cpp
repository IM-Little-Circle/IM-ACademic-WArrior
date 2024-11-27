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
    skill[0] = getSkill(1);
    skill[1] = getSkill(2);
    skill[2] = getSkill(3);
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

Skill Player::getSkill(int filename){
    int i = 1;
    ifstream inFile("../assets/skill/skill" + to_string(i) + ".txt");
    if (inFile.fail()) {
        cout << "File not found\n";
        return;
    }
    /*
    放skill
    skillName;
    skillType;
    restRound;
    */
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