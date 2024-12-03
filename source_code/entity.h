/*
放一些暫時想到的數值和可能用到的函式
*/
#include <iostream>
using namespace std;
class Entity {
	protected:
		int hpCurr, atk, def, hpMax;
		int level = 1;
		double socialBuff = 0, studyBuff = 0, healBuff = 0;
		bool alive = true;
		double mentalRes = 0, physicalRes = 0;
		string weakness = "";
		// wanna add name

	public:	
		Entity(int hp, int atk, int def);
		void socialAttack(Entity& enemy, int percent);
		void studyAttack(Entity& enemy, int percent);
        void heal(int percent);
		void death();
		
		bool living();
		
		void printHealth();
};