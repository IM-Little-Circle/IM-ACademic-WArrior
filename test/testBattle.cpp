#include <iostream>
#include "player.h"
using namespace std;

void battleLoop(Player player, Entity opponent) { // should these be references instead?
    string input;
    while (opponent.living() && player.living()) {
        input = " ";

        while (!(input == "A" || input == "B" || input == "a" || input == "b")) {
            // choice of attack
            cout << "[A: Study Attack | B: Social Attack]\n";
            cin >> input;

            // error input
            if (!(input == "A" || input == "B" || input == "a" || input == "b")) {
                cout << "Wrong input, try again.\n";
            }
        }

        if (input == "A" || input == "a") {
            // study attack
            player.studyAttack(opponent);
        }

        else {
            // social attack
            player.socialAttack(opponent);

        }

        cout << "Player: ";
        player.printHealth();
        cout << "Opponent: ";
        opponent.printHealth();
    }
}

int main () {
    Player player(10, 10, 10);
    Entity opponent(10, 10, 10);

    player.setInitialStat(10, 10, 10);

    cout << "Battle Time!\n";
    cout << string(15, '#');
    cout << endl;

    battleLoop(player, opponent);


}