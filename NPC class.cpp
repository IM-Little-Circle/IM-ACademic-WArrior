/*
放一些暫時想到的數值和可能用到的函式
*/
#include <bits/stdc++.h> //by eric, 這東西在只有裝vscode的電腦會跑不了 而且理論上把用到的函式庫列出來會比姣好
using namespace std;
class NPC
{
	private:
		int HP, ATK, DEF;
		double magic_buff, physical_buff;
		double magic_RES, physical_RES;
		// a bag for skill
		//vector<skill> Skill;
	public:	
		void attack(NPC);
        void heal(NPC);
		void use_skill();		
}