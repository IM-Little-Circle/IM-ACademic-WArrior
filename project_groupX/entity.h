/*
放一些暫時想到的數值和可能用到的函式
*/
#include <iostream>
using namespace std;
class Entity
{
	private:
		int hpCurr, atk, def, hpMax, level;
		double socialBuff = 0, studyBuff = 0;
		bool alive = true;
		double mentalRes, physicalRes;

	public:	
		void socialAttack(Entity enemy);
        void heal();
		void death();
		void updateStatus(int academic, int social, int emo);
		void levelUp();
		bool living();
};

void Entity::socialAttack(Entity enemy)
{
	int atkCurr = atk * (1 + socialBuff);
	enemy.hpCurr -= atkCurr - enemy.def * (1 + mentalRes);
	if (enemy.hpCurr <= 0)
		enemy.death();
}

void Entity::death()
{
	alive = false;
}

void Entity::updateStatus(int academic, int social ,int emo)
{
	socialBuff = (social + emo) / 100;
	studyBuff = (academic + emo) / 100;
	mentalRes = emo / 100;
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
				break;
			}
		}
		else
		{
			player2.socialAttack(player1);
			if (!player1.living())
			{
				cout << "You lose!" << endl;
				break;
			}
		}
	}
}