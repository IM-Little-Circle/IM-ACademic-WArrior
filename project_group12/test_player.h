// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Player{
    private:
        int academic = 0; 
    public:
        Player(int hp, int atk, int def);
        int getAcademic();
};

Player::Player(int hp, int atk, int def) {
    academic = 10;
}

int Player::getAcademic() {
    return academic;
}