/*
放一些暫時想到的數值和可能用到的函式
*/
#include <iostream>
using namespace std;
class Entity
{
	protected:
		int hpCurr, atk, def, hpMax;
		int level = 1;
		double socialBuff = 0, studyBuff = 0;
		bool alive = true;
		double mentalRes = 0, physicalRes = 0;

		// wanna add name

	public:	
		Entity(int hp, int Atk, int Def);
		void socialAttack(Entity& enemy);
		void studyAttack(Entity& enemy);
        void heal();
		void death();
		void levelUp();
		bool living();

		void printHealth();
};