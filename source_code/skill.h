#include <iostream>
#include "Entity.h"
using namespace std;

/*
要添加buff嗎?
但不知道buff的到期怎麼處理...
*/

class skill : public Entity{
    private:
        int restRound;
        int coolRound;
        string attackType; // also can use int 
        int percent; // 1 = 100%
    public:
        void useSkill(Entity enemy);
        void getSkill(string filename); // 讀檔?
}