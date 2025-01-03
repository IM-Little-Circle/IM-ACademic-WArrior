#include "player.h"
//#include "skill.h"
//#include "entity.h"
// entity member and related functions

int threshold[6] = {5, 8, 10, 15, 20, 30};

Player::Player(int hp, int atk, int def) : Entity(hp, atk, def) {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
	socialBuff = double(social / 100);
	studyBuff = double(academic / 100);
    healBuff = double((100 - emo) / 500);
	mentalRes = (100 - emo) / 100;
    skill[0] = fetchSkill(1);
    skill[1] = fetchSkill(2);
    skill[2] = fetchSkill(3);
    name = "你";
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

int Player::getEmo() {
    return this->emo;
}

int Player::getLevel() {
    return this->level;
}

void Player::updateStatus() {
	socialBuff = static_cast<double>(social) / 100;
    studyBuff = static_cast<double>(academic) / 100;
    mentalRes = static_cast<double>(100 - emo) / 100;
    healBuff = static_cast<double>((100 - emo) / 500);
    /*cout << "now socialBuff = " << socialBuff << endl;
    cout << "studyBuff = " << studyBuff << endl;
    cout << "mentalRes = " << mentalRes << endl;*/
}

void Player::fullRecover(){
    skillReset();
    hpCurr = hpMax;
    alive = true;
}

void Player::printStatRight() {
    updateStatus();
    cout << "ACA " << academic << "\nSOC " << social << "\nEMO " << emo << endl;
}
void Player::printStatRight(int oriAca, int oriSoc, int oriEmo){
    updateStatus();
    cout << string(30, ' ') << "ACA " << oriAca << " ---> " << academic << "\n" << string(30, ' ')  << "SOC " << oriSoc << " ---> " << social << "\n"  << string(30, ' ')  << "EMO " << oriEmo << " ---> " << emo << endl;
}

// to set initial stat
void Player::setInitialStat(int aca, int soc, int e) {
    academic = aca;
    social = soc;
    emo = e;
    updateStatus();
}

void Player::levelUp() {
	level++;
	atk *= 1.3;
	def *= 1.2;
	hpMax += level * 2 + 1;
	hpCurr = hpMax;
}

void Player::getExp(int experience){
    exp += experience;
    int originalLevel = level;
    if (level >= 6){
        while(exp >= threshold[5]){
            exp -= threshold[5];
            levelUp();
        }
    }
    else{
        while(exp >= threshold[level-1]){
        exp -= threshold[level-1];
        levelUp();
    }
    }
    if (level != originalLevel){
        cout << "Level up!!!  ";
	    cout << originalLevel << "  --->  " << level << endl;
    }
}

Skill* Player::getSkill(int skillIndex) {
    return this->skill[skillIndex];
}

Skill* Player::fetchSkill(int filenumber){
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
   return new Skill(skillName, skillType, restRound, percent);
}



void Player::replaceSkill(int filenumber){
    string changeNumber;
    cin >> changeNumber;

    while (!(changeNumber == "1" || changeNumber == "2" || changeNumber == "3")){
            cout << "Wrong input, please choose your number again" << endl;
            cin >> changeNumber;
    }
    cin.ignore();
    cout << "Replaced " << skill[stoi(changeNumber)-1]->getName();
    skill[stoi(changeNumber)-1] = fetchSkill(filenumber);
    cout << " with " <<  skill[stoi(changeNumber)-1]->getName() << "!\n";

}

void Player::useSkill(Entity& enemy, Skill skill){
    if (skill.getCoolRound() != 0) return; 
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


void Player::useSkill(Entity& enemy, int chooseNumber){
    Skill usedSkill = *skill[chooseNumber];
    if (usedSkill.getType() == "heal"){
        heal(usedSkill.getPercent());
    }
    else if (usedSkill.getType() == "studyAttack"){
        studyAttack(enemy, usedSkill.getPercent());
    }
    else{
        socialAttack(enemy, usedSkill.getPercent());
    }
    skill[chooseNumber]->cool();
}

void Player::printSkill(int skillIndex) {
    if (skillIndex >= 0 && skillIndex < 3) {
        skill[skillIndex]->printSkill();
    }
    else cout << "error index!\n";
}

void Player::printnewSkill(int skillIndex) {
    if (skillIndex >= 0 && skillIndex < 3) {
        skill[skillIndex]->printnewSkill();
    }
    else cout << "error index!\n";
}

void Player::printSkillName(int skillIndex){
    if (skillIndex >= 0 && skillIndex < 3) {
        skill[skillIndex]->printName();
    }
    else cout << "error index!\n";
}

void Player::printSkillType(int skillIndex){
    if (skillIndex >= 0 && skillIndex < 3) {
        skill[skillIndex]->printType();
    }
    else cout << "error index!\n";
}

void Player::printSkillCoolRound(int skillIndex){
    if (skillIndex >= 0 && skillIndex < 3) {
        skill[skillIndex]->printCoolRound();
    }
    else cout << "error index!\n";
}

void Player::printSkillPercent(int skillIndex){
    if (skillIndex >= 0 && skillIndex < 3) {
        skill[skillIndex]->printPercent();
    }
    else cout << "error index!\n";
}

void Player::printSkillNeatly(int coolOrRest) {
    for (int i = 0; i < 3; i++) {
        cout << ">" << i+1;
        cout << string(23, ' ');
        }
        cout << endl;

        // print current skills
        for(int i=0; i<3; i++) {
            printSkillName(i);
            cout << string(25 - (getSkill(i)->getName().length())/3*2, ' ');
        }
        cout << endl;
        
        for(int i = 0; i < 3; i++) {
            cout << "技能類型：";
            printSkillType(i);
            cout << string(15 - getSkill(i)->getType().length(), ' ');
        }
        cout << endl;
        
        if (coolOrRest == 1){
            for(int i = 0; i < 3; i++) {
                cout << "剩餘冷卻回合：" << getSkill(i)->getRestRound();
                cout << string(11 - to_string(getSkill(i)->getRestRound()).length(), ' ');
            }
            cout << endl;
        }
        else{
            for(int i = 0; i < 3; i++) {
                cout << "技能冷卻回合：" << getSkill(i)->getCoolRound();
                cout << string(11 - to_string(getSkill(i)->getCoolRound()).length(), ' ');
            }
            cout << endl;
        }
           
        for(int i = 0; i < 3; i++) {
            cout << "倍率：";
            cout << getSkill(i)->getPercent() << "%";
            cout << string(19 - to_string(getSkill(i)->getPercent()).length() - 1, ' ');
        }
        cout << endl;
}

void Player::skillCool(){
    for (int i = 0; i < 3; i++){
        skill[i]->skillCool();
    }
}

bool Player::isCool(int skillNumber){
    if (skill[skillNumber-1]->getRestRound() > 0) 
        return true;
    else 
        return false;
    
}

void Player::skillReset(){
    for (int i = 0; i < 3; i++){
        skill[i]->coolReset();
    }
}

bool Player::allSkillCooling(){
    bool is = 1;
    for (int i = 0; i < 3; i++){
        if (skill[i]->getRestRound() <= 0)
            return false;
    }
    return true;
}

