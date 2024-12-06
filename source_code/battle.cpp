#include "battle.h"

void battle(Player player, Entity opponent) { // should these be references instead?
    string input;
    int round = 0;
    while (opponent.living() && player.living()) {
        input = "0";
        round ++;
        
        if (round % 2) // player's round
        {
            cout << "Round " << (round + 1) / 2 << endl;
            player.skillCool();

            //select a skill!
            while (!(input == "1" || input == "2" || input == "3")) {
                // choice of attack
                cout << "Select a skill\n";
                player.printSkill(0);
                player.printSkill(1);
                player.printSkill(2);
                cin >> input;
                // error input
                if (!(input == "1" || input == "2" || input == "3") ) {
                    cout << "Wrong input, try again.\n";
                }
                if (player.isCool( stoi(input))){
                    cout << "the skill is cooling, please try again.\n";
                    input = -1;
                }
            }
                
                


            player.useSkill(opponent, stoi(input) - 1);
        }
        else{
            opponent.studyAttack(player, 100);
        }

        cout << "Player: ";
        player.printHealth();
        cout << "Opponent: ";
        opponent.printHealth();
        input = "0";
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

void triggerBattle(Player& player){
    Entity enemy(1); // 要怎麼找敵人?
    enemy.adjust(player.getLevel());
    player.fullRecover();
    battle(player, enemy);
}
