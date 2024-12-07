#include "entity.h"
#include <fstream>
using namespace std;

// entity member and related functions

// constructors
Entity::Entity(int hp, int Atk, int Def) {
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
}

Entity::Entity(int hp, int Atk, int Def, double mentalRes, double physicalRes, string weakness){
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
	this->mentalRes = mentalRes, this->physicalRes = physicalRes;
	this->weakness = weakness;
}

Entity::Entity(int fileNumber) {
    string enemyName, enemyWeakness;
    int attack, defence, health;
	double menR, phyR;
    ifstream inFile("../assets/enemy/enemy" + to_string(fileNumber) + ".txt");
    if (inFile.fail()) {
        cout << "File not found\n";
    }
    else {
        getline(inFile, enemyName);
        getline(inFile, enemyWeakness);
        inFile >> attack >> defence >> health >> menR >> phyR;
    }

    this->name = enemyName;
    this->weakness = enemyWeakness;
    this->atk = attack;
    this->def = defence;
    this->hpMax = health;
    this->hpCurr = health;
    this->mentalRes = menR;
    this->physicalRes = phyR;
}

Entity::Entity(string fileName) {
    string enemyName, enemyWeakness;
    int attack, defence, health;
	double menR, phyR;
    ifstream inFile("../assets/enemy/" + fileName + ".txt");
    if (inFile.fail()) {
        cout << "File not found\n";
    }
    else {
        getline(inFile, enemyName);
        getline(inFile, enemyWeakness);
        inFile >> attack >> defence >> health >> menR >> phyR;
    }

    this->name = enemyName;
    this->weakness = enemyWeakness;
    this->atk = attack;
    this->def = defence;
    this->hpMax = health;
    this->hpCurr = health;
    this->mentalRes = menR;
    this->physicalRes = phyR;
}


void Entity::socialAttack(Entity& enemy, int percent) {
	int atkCurr = double(atk * (1 + socialBuff)) * percent / 100;
	/*cout << "def = " << enemy.def << endl;
	cout << "now enemy's mentalRes = " << mentalRes << endl;*/
	int defCurr = enemy.def;
	if (enemy.weakness == "social")
		atkCurr *= 1.2;
/*
	cout << "atkCurr = " << atkCurr << endl;
	cout << "Enemy's def = " << defCurr << endl;
*/
	int damage = atkCurr - defCurr;
	damage = max(damage, 1);
	cout << "「" << this->getName() << "」對「"  << enemy.getName() << "」造成了" << damage <<  "點的傷害！" << endl;
	enemy.hpCurr -= damage;
	if (enemy.hpCurr <= 0) {
		enemy.death();
		enemy.hpCurr = 0;
	}
}

void Entity::studyAttack(Entity& enemy, int percent) {
	int atkCurr = double(atk * (1 + studyBuff)) * percent /100;
	int defCurr = enemy.def;
	if (enemy.weakness == "study")
		atkCurr *= 1.;
/*
	cout << "atkCurr = " << atkCurr << endl;
	cout << "defCurr = " << defCurr << endl;
*/
	int damage = atkCurr - defCurr;
	damage = max(damage, 1);
	cout << "「" << this->getName() << "」對「"  << enemy.getName() << "」造成了" << damage <<  "點的傷害！" << endl;
	enemy.hpCurr -= damage;
	if (enemy.hpCurr <= 0) {
		enemy.death();
		enemy.hpCurr = 0;
	}	
	//cout << "enemy's hp" << enemy.hpCurr << endl;
}

void Entity::heal(int percent){
	//cout << "atk = " << atk << " healBuff = " << healBuff << endl;
	int recover = double(atk * (1 + healBuff) / 1.5) * percent / 100;
	cout << "回復了" << recover << "的血量！" << endl;
	hpCurr = min(hpCurr + recover, hpMax);
}

void Entity::death() {
	alive = false;
}

bool Entity::living() {
	return alive;
}

void Entity::printHealth() {
	cout << hpCurr << "/" << hpMax << endl;
}

void Entity::adjust(int level){
	//cout << "now enemy's mentalRes = " << mentalRes << endl;
	/*cout << "before adjust\n";
	cout << "hp = " << hpMax << "\natk = " << atk << "\ndef = " << def << endl;*/
	hpMax += 5 * level;
	hpCurr = hpMax;
	atk += 2 * level;
	def += 1.2 * level;
	if (level >= 10)
		def += 10;
	while(level > 2){
		level -= 2;
		atk += 2.2 * level;
		def += 2 * level;
		hpMax += 4 * level;
	}
	/*cout << "after adjust\n";
	cout << "hp = " << hpMax << "\natk = " << atk << "\ndef = " << def << endl;*/
}

string Entity::getName() {
	return name;
}