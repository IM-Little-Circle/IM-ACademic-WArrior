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
	int defCurr = enemy.def * (1 + mentalRes);
	if (enemy.weakness == "social")
		atkCurr *= 1.1;

	cout << "atkCurr = " << atkCurr << endl;
	cout << "Enemy's def = " << defCurr << endl;

	int damage = atkCurr - defCurr;
	damage = max(damage, 1);
	cout << "Cause damage: " << damage << endl;
	enemy.hpCurr -= damage;
	if (enemy.hpCurr <= 0) {
		enemy.death();
		enemy.hpCurr = 0;
	}
}

void Entity::studyAttack(Entity& enemy, int percent) {
	int atkCurr = double(atk * (1 + studyBuff)) * percent /100;
	int defCurr = enemy.def * (1 + physicalRes);
	if (enemy.weakness == "study")
		atkCurr *= 1.1;
/*
	cout << "atkCurr = " << atkCurr << endl;
	cout << "defCurr = " << defCurr << endl;
*/
	int damage = atkCurr - defCurr;
	damage = max(damage, 1);
	cout << atkCurr << "-" << defCurr << endl; // for debugging
	cout << "Cause damage: " << damage << endl;
	enemy.hpCurr -= damage;
	if (enemy.hpCurr <= 0) {
		enemy.death();
		enemy.hpCurr = 0;
	}	
	//cout << "enemy's hp" << enemy.hpCurr << endl;
}

void Entity::heal(int percent){
	//cout << "atk = " << atk << " healBuff = " << healBuff << endl;
	int recover = double(atk * (1 + healBuff) / 3) * percent / 100;
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
	/*cout << "before adjust\n";
	cout << "hp = " << hpMax << "\natk = " << atk << "\ndef = " << def << endl;*/
	hpMax += 5 * level;
	hpCurr = hpMax;
	atk += 2 * level;
	def += 1.2 * level;
	while(level > 3){
		level -= 5;
		atk += 2 * level;
		def += 1.7 * level;
		hpMax += 3 * level;
	}
	/*cout << "after adjust\n";
	cout << "hp = " << hpMax << "\natk = " << atk << "\ndef = " << def << endl;*/
}

string Entity::getName() {
	return name;
}