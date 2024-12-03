#include "entity.h"
using namespace std;

// entity member and related functions

Entity::Entity(int hp, int Atk, int Def) {
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
    cout << "player created!!!!!\n"; // temp, delete later
}
Entity::Entity(int hp, int Atk, int Def, double mentalRes, double physicalRes, string weakness){
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
	this->mentalRes = mentalRes, this->physicalRes = physicalRes;
	this->weakness = weakness;
}
void Entity::socialAttack(Entity& enemy, int percent) {
	int atkCurr = double(atk * (1 + socialBuff)) * percent / 100;
	int defCurr = enemy.def * (1 + mentalRes);
	if (enemy.weakness == "social")
		atkCurr *= 1.3;

	cout << "atkCurr = " << atkCurr << endl;
	cout << "Enemy's def = " << defCurr << endl;

	int damage = atkCurr - defCurr;
	damage = max(damage, 0);
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
		atkCurr *= 1.3;
/*
	cout << "atkCurr = " << atkCurr << endl;
	cout << "defCurr = " << defCurr << endl;
*/
	int damage = atkCurr - defCurr;
	damage = max(damage, 0);
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
	int recover = hpMax * healBuff;
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
