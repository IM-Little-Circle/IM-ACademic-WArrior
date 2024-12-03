#include "battle.h"
void battle(Player player, Entity opponent) { // should these be references instead?
    string input;
    int round = 0;
    while (opponent.living() && player.living()) {
        input = " ";
        round ++;
        // show round?
        
        if (round % 2) // player's round
        {
            cout << "Round " << (round + 1) / 2 << endl;
            player.skillCool();

            //select a skill!

            while (!(input == "A" || input == "B" || input == "a" || input == "b")) {
                // choice of attack
                cout << "[A: Study Attack | B: Social Attack]\n";
                cin >> input;
            }
                // error input
                if (!(input == "A" || input == "B" || input == "a" || input == "b")) {
                    cout << "Wrong input, try again.\n";
            }
            /*
            skill version battle
            useskill(player, stoi(input));
            */


            // study attack
            if (input == "A" || input == "a") {
                player.studyAttack(opponent, 100);
                cout << "Oppoenent got studyattack!\n"; // maybe can show how demage the player caused or show at the studyAttack function
            }
                
            // social attack
            else  {
                player.socialAttack(opponent, 100);
            }
        }
        else{
            opponent.studyAttack(player, 100);
        }

        cout << "Player: ";
        player.printHealth();
        cout << "Opponent: ";
        opponent.printHealth();
        input = " ";
        cout << endl;
    }
    if (player.living()){
        cout << "Congradulation! you win!" << endl;
        player.getExp(10);
    }
        
    else
        cout << "oops! you fail :(" << endl;
    player.fullRecover();
}