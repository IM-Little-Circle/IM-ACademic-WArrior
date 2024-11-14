// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include "entity.h"
using namespace std;

class Player : public Entity {
    private:
        int x;
        int y;
        
        // initialized for testing
        int academic = 0; 
        int social = 0;
        int emo = 0;
    public:
        Player(int hp, int Atk, int Def);
        void modifyAcademic(int change);
        void modifySocial(int change);
        void modifyEmo(int change);
		void updateStatus();

        // below added for testing
        void printStat();
        void setInitialStat(int aca, int soc, int e);
        
};

Player::Player(int hp, int Atk, int Def) {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
	socialBuff = (social + emo) / 100;
	studyBuff = (academic + emo) / 100;
	mentalRes = emo / 100;
	hpCurr = hp, hpMax = hp, atk = Atk, def = Def;
}


void Player::modifyAcademic(int change) {
    academic += change;
    updateStatus();
}


void Player::modifySocial(int change) {
    social += change;
    updateStatus();
}


void Player::modifyEmo(int change) {
    emo += change;
    updateStatus();
}

void Player::updateStatus()
{
	socialBuff = static_cast<double>(social + emo) / 100;
    studyBuff = static_cast<double>(academic + emo) / 100;
    mentalRes = static_cast<double>(emo) / 100;
    cout << "now socialBuff = " << socialBuff << endl;
    cout << "studyBuff = " << studyBuff << endl;
    cout << "mentalRes = " << mentalRes << endl;
}

void Player::printStat(){
    cout << "ACA " << academic << "\nSOC " << social << "\nEMO " << emo << endl;
}


// to set initial stat
// (so we don't have to come back to player.h to change every time)
// tbh you can just set the initial value at initialization
void Player::setInitialStat(int aca, int soc, int e) {
    academic = aca;
    social = soc;
    emo = e;
    updateStatus();
}