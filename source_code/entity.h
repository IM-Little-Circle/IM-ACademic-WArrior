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
		string name = "";

	public:	
		Entity(int filenumber);
		Entity(int hp, int atk, int def);
		Entity(int hp, int atk, int def, double mentalRes, double physicalRes, string weakness);
		void socialAttack(Entity& enemy, int percent);
		void studyAttack(Entity& enemy, int percent);
        void heal(int percent);
		void death();
		
		bool living();
		
		void printHealth();
};