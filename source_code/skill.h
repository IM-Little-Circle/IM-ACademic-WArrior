#include <iostream>
using namespace std;

/*
要添加buff嗎?
但不知道buff的到期怎麼處理...
*/

class Skill {
    private:
        int restRound;
        int coolRound;
        string skillType; // also can use int 
        int percent; // 1 = 100%
        string skillName;
    public:
         // 讀檔?
        Skill (string skillName, string skillType, int restRound, int percent);
        string getType();
        int getCoolRound();
        int getPercent();
};