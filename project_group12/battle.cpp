#include "battle.h"

bool battle(Player& player, Entity &opponent) { // should these be references instead?
    string input;
    int round = 0;
    while (opponent.living() && player.living()) {
        input = "0";
        round ++;
        // player's round
        if (round % 2) {
            cout << "Round " << (round + 1) / 2 << endl;
            player.skillCool();
            if (player.allSkillCooling()){
                cout << "所有技能冷卻中，回合被迫跳過\n";
                continue;
            }
            
            //select a skill!
            while (!(input == "1" || input == "2" || input == "3")) {

                cout << "【現有技能】" << endl << endl;
                player.printSkillNeatly(1);
                cout << endl;
                cout << "選擇技能 ";

                // input choice
                cin >> input;

                // error input
                if (!(input == "1" || input == "2" || input == "3") ) {
                    cout << "輸入錯誤，請再次輸入.\n";
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
        cout << "恭喜你贏啦！" << endl;
        player.getExp(15);
    }
        
    else
        cout << "喔喔，你失敗了 :(" << endl;
    return player.living();
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
    bool result = battle(player, enemy);
    if (result){
        cout << "成功通過期中考！\n";
        player.modifyAcademic(5);
    }
    else{
        cout << "可惜，再接再厲！\n";
    }
        
    cin.ignore();
}

void triggerFinal(Player& player) {
    Entity enemy("finalBoss");
    enemy.adjust(player.getLevel());
    player.fullRecover();
    bool result = battle(player, enemy);
    if (result){
        cout << "趕死線對我不過小菜一碟！\n";
        player.modifyAcademic(5);
    }
    else{
        cout << "下學期還是修少一點學分吧...！\n";
    }
    cin.ignore();
}