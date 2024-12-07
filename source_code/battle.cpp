#include "battle.h"

void battle(Player& player, Entity opponent) { // should these be references instead?
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

                cout << "【現有技能】" << endl << endl;
                // print current skills
                player.printSkillNeatly(1);
                cout << endl;
    
                cout << "選擇技能 ";

                // input choice
                cin >> input;

                // error input
                if (!(input == "1" || input == "2" || input == "3") ) {
                    cout << "Wrong input, try again.\n";
                }
                else if (player.isCool(stoi(input))){
                    cout << "技能正在冷卻，請重新選擇\n";
                    input = -1;
                }
            }
            // clear screen
            #ifdef _WIN32
            system("cls");
            #elif __linux__
            system("clear");
            #endif
            player.useSkill(opponent, stoi(input) - 1);
        }
        else{
            opponent.studyAttack(player, 100);
        }
        

        cout << player.getName() << ": ";
        player.printHealth();
        cout <<  opponent.getName() << ": ";
        opponent.printHealth();
        input = "0";
        cout << endl;
    }

    if (player.living()){
        cout << "Congratulation! you win!" << endl;
        player.getExp(10);
    }
        
    else
        cout << "oops! you fail :(" << endl;
}

void triggerBattle(Player& player){
    srand(time(NULL));
    Entity enemy(rand() % ENEMY_CNT + 1);
    enemy.adjust(player.getLevel());
    player.fullRecover();
    cout << "觸發戰鬥：【" << enemy.getName() << "】\n";
    battle(player, enemy);
    cin.ignore();
    

}

void triggerMidterms(Player& player) {
    Entity enemy("midtermBoss");
    enemy.adjust(player.getLevel());
    player.fullRecover();
    battle(player, enemy);
    cin.ignore();
}

void triggerFinal(Player& player) {
    Entity enemy("finalBoss");
    enemy.adjust(player.getLevel());
    player.fullRecover();
    battle(player, enemy);
    cin.ignore();
}