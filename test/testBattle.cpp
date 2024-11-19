#include <iostream>
#include "player.h"
using namespace std;

void battleLoop(Player player, Entity opponent) { // should these be references instead?
    string input;
    int round = 0;
    while (opponent.living() && player.living()) {
        input = " ";
        round ++;
        // show round?
        cout << "Round " << round << endl;
        if (round % 2) // player's round
        {
            while (!(input == "A" || input == "B" || input == "a" || input == "b")) {
                // choice of attack
                cout << "[A: Study Attack | B: Social Attack]\n";
                cin >> input;
            }
                // error input
                if (!(input == "A" || input == "B" || input == "a" || input == "b")) {
                    cout << "Wrong input, try again.\n";
            }

            // study attack
            if (input == "A" || input == "a") {
                player.studyAttack(opponent);
                cout << "Oppoenent got studyattack!\n"; // maybe can show how demage the player caused or show at the studyAttack function
            }
                
            // social attack
            else  {
                player.socialAttack(opponent);
            }
        }
        else{
            opponent.studyAttack(player);
        }

        cout << "Player: ";
        player.printHealth();
        cout << "Opponent: ";
        opponent.printHealth();
        input = " ";
        cout << endl;
    }
}

int main () {
    Player player(60, 50, 50);
    Entity opponent(60, 60, 40);

    player.setInitialStat(10, 10, 10);
    cout << "Battle Time!\n";
    cout << string(15, '#');
    cout << endl;

    battleLoop(player, opponent);

}