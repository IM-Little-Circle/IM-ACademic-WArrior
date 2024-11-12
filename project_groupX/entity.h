/*
放一些暫時想到的數值和可能用到的函式
*/
#include <iostream>
using namespace std;
class Entity
{
	private:
		int hpCurr, atk, def, hpMax;
		double socialBuff = 0, studyBuff = 0;
		bool alive = true;
		double mentalRes, physicalRes;

	public:	
		void socialAttack(Entity enemy);
        void heal();
		void death();
		void updateStatus(int academic, int social, int emo);
};

void socialAttack(Entity enemy)
{
	int atkCurr = atk * (1 + magicBuff);
	enemy.hpCurr -= atkCurr - enemy.def * (1 + mentalRes);
	if (enemy.hpCurr <= 0)
		enemy.death();
}

void death()
{
	alive = false;
}

void updateStatus(int academic, int social ,int emo)
{
	socialBuff = (social + emo) / 100;
	studyBuff = (academic + emo) / 100;
	mentalRes = emo / 100;
}

