// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include "entity.h"
using namespace std;

class Player : public Entity{
    private:
        int x;
        int y;
        
        // initialized for testing
        int academic = 0; 
        int social = 0;
        int emo = 0;
    public:
        Player();

        // below added for testing
        void modifyAcademic(int change);
        void modifySocial(int change);
        void modifyEmo(int change);
		void updateStatus(int academic, int social, int emo);
        void printStat();
        
};

Player::Player() {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
}


void Player::modifyAcademic(int change) {
    academic += change;
}


void Player::modifySocial(int change) {
    social += change;
}


void Player::modifyEmo(int change) {
    emo += change;
}

void Player::updateStatus(int academic, int social, int emo)
{
	socialBuff = (social + emo) / 100;
	studyBuff = (academic + emo) / 100;
	mentalRes = emo / 100;
}

void Player::printStat(){
    cout << "ACA " << academic << "\nSOC " << social << "\nEMO " << emo << endl;
}