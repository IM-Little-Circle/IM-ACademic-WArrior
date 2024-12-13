#include <iostream>
using namespace std;

const int SKILL_CNT = 20; // number of skills

class Skill {
    private:
        int restRound; //戰鬥時會用到的
        int coolRound; // 技能的固定冷卻回合數
        string skillType; // also can use int 
        int percent; // 1 = 100%
        string skillName;
    public:
        Skill();
        Skill(int fileNumber);
        Skill (string skillName, string skillType, int restRound, int percent);
        string getType();
        string getName();
        void printSkill(); 
        void printnewSkill();
        int getCoolRound();
        int getRestRound();
        int getPercent();
        void skillCool();
        void coolReset();
        void cool();

        // for print
        void printName();
        void printType();
        void printCoolRound();
        void printPercent();
        
};