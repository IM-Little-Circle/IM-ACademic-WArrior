#include <iostream>
using namespace std;

const int SKILL_CNT = 20; // number of skills, note that skill 1-3 are starters, not included here

/*
要添加buff嗎?
但不知道buff的到期怎麼處理...
*/

class Skill {
    private:
        int restRound; //戰鬥時會用到的
        int coolRound; // 技能的固定冷卻回合數
        string skillType; // also can use int 
        int percent; // 1 = 100%
        string skillName;
    public:
         // 讀檔?
        Skill();
        Skill(int fileNumber);
        Skill (string skillName, string skillType, int restRound, int percent);
        string getType();
        string getName();
        void printSkill(); // added by liz, for  debugging
        void printnewSkill();
        int getCoolRound();
        int getRestRound();
        int getPercent();
        void skillCool();
        void coolReset();
        void cool();

        void printName(); // added by Mia
        void printType();
        void printCoolRound();
        void printPercent();
        
};