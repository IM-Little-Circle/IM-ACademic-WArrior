/*
放一些暫時想到的數值和可能用到的函式
*/
#include <iostream>
using namespace std;
class Entity
{
	protected:
		int hpCurr, atk, def, hpMax, level;
		double socialBuff = 0, studyBuff = 0;
		bool alive = true;
		double mentalRes, physicalRes;

	public:	
		Entity(int hp, int Atk, int Def);
		void socialAttack(Entity enemy);
		void studyAttack(Entity enemy);
        void heal();
		void death();
		void levelUp();
		bool living();
};
Entity::Entity(int hp, int Atk, int Def)
{
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
}

void Entity::socialAttack(Entity enemy)
{
	int atkCurr = atk * (1 + socialBuff);
	enemy.hpCurr -= atkCurr - enemy.def * (1 + mentalRes);
	if (enemy.hpCurr <= 0)
		enemy.death();
}

void Entity::studyAttack(Entity enemy)
{
	int atkCurr = atk * (1 + studyBuff);
	enemy.hpCurr -= atkCurr - enemy.def * (1 + physicalRes);
	if (enemy.hpCurr <= 0)
		enemy.death();
}

void Entity::death()
{
	alive = false;
}

void Entity::levelUp()
{
	level++;
	atk += level * 1.2;
	def += level;
	hpMax += level * 2;
	hpCurr = hpMax;
}
bool Entity::living()
{
	return alive;
}
void Battle(Entity player1, Entity player2)
{
	int round = 0;
	bool stop = 0;
	while (true)
	{
		round++;
		if (round % 2)
		{
			// may be you can choose socialATK or studyATK; but now there is only socialATK for you :D
			player1.socialAttack(player2);
			if (!player2.living())
			{
				cout << "Congratulation! You win!" << endl;
				stop = 1;
			}
		}
		else
		{
			player2.socialAttack(player1);
			if (!player1.living())
			{
				cout << "You lose!" << endl;
				stop = 1;
			}
		}
		if (stop)
			break;
	}
}