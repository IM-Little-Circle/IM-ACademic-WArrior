#include "entity.h"
using namespace std;

// entity member and related functions

Entity::Entity(int hp, int Atk, int Def) {
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
    cout << "player created!!!!!\n"; // temp, delete later
}

void Entity::socialAttack(Entity& enemy) {
	int atkCurr = atk * (1 + socialBuff);
	int defCurr = enemy.def * (1 + mentalRes);
/*
	cout << "atkCurr = " << atkCurr << endl;
	cout << "Enemy's def = " << defCurr << endl;
*/
	int damage = atkCurr - defCurr;
	cout << "Cause damage: " << damage << endl;
	enemy.hpCurr -= damage;
	if (enemy.hpCurr <= 0) {
		enemy.death();
		enemy.hpCurr = 0;
	}
}

void Entity::studyAttack(Entity& enemy) {
	int atkCurr = double(atk * (1 + studyBuff));
	int defCurr = enemy.def * (1 + physicalRes);
/*
	cout << "atkCurr = " << atkCurr << endl;
	cout << "defCurr = " << defCurr << endl;
*/
	int damage = atkCurr - defCurr;
	cout << "Cause damage: " << damage << endl;
	enemy.hpCurr -= damage;
	if (enemy.hpCurr <= 0) {
		enemy.death();
		enemy.hpCurr = 0;
	}	
}

void Entity::death() {
	alive = false;
}

void Entity::levelUp() {
	level++;
	atk += level * 1.2;
	def += level;
	hpMax += level * 2;
	hpCurr = hpMax;
}


bool Entity::living() {
	return alive;
}

void Entity::printHealth() {
	cout << hpCurr << "/" << hpMax << endl;
}

void Battle(Entity& player1, Entity& player2) {
	int round = 0;
	bool stop = 0;
	while (true) {
		round++;
		if (round % 2) {
			// may be you can choose socialATK or studyATK; but now there is only socialATK for you :D
			player1.socialAttack(player2);
			if (!player2.living())
			{
				cout << "Congratulation! You win!" << endl;
				stop = 1;
			}
		}
		else {
			player2.socialAttack(player1);
			if (!player1.living()) {
				cout << "You lose!" << endl;
				stop = 1;
			}
		}
		if (stop)
			break;
	}
}