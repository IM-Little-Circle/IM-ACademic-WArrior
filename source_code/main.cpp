#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <thread>

// below are user-made header files
#include "myconio.h"
//#include "player.h"
#include "event.h"

using namespace std;
/* ###bug notes###
found new bug: if arrow key pressed for too long (more than 25ms i think)
console will keep running the input 
fix, maybe with this_thread sleep or something
new issue found @2024/11/24: if right arrow key pressed for a while and then ran into a chance, 
                             as cin >> choice is waiting for input, 
**the issue has been fixed** the right arrow key will result in a 'y' input.
                             note that 'y' could be the last input before the cin
*/

//// conio.h keys ////
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define KEY_ENTER 13

//// game settings ////
#define MAP_W 32
#define MAP_H 32
#define SCRN_HW 4 // half width of 9, for printing camera screen
#define TERM_CHANCE_CNT 8

// here are some global variables for now, wrap them up later
vector<string> map;
// pos mainly to control camera movement, put in player class
int x = 7;
int y = 7; //btw the pos is temp too
int chanceEncounteredCnt = 0;
bool midterms = false, finals = false;
extern const int CHANCE_CNT; //number of chances, must >= 1
extern const int DESTINY_CNT; //number of destinies, must >= 1
extern const int SKILL_CNT; // number of skills, note that skill 1-3 are starters, not included here
string mapFilePath = "../assets/map/testEventMap5.txt";

//// declare functions ////
void buffer(); // press enter to continue
void setCodePage();
void clearScreen(); // system cls/clear

void printTitle();
void printPreface();
void printSummary();
void printInstruction();
void printGameStart();

void gameStartScreen();
void gameMechanicScreen();
void animateString(string str, int ms); 
void animateStringForEnding(ifstream& inFile);
void timeBar();
void readMap();
void printMaze(bool visited[][MAP_W], Player& player);
void moveCamera(int ch);
void detectEvent(Player& player, bool visited[][MAP_W], bool triggeredChance[], bool triggeredDestiny[]);
void detectChanceCnt(bool visited[][MAP_W], Player& player);
void replaceSkillScreen(Player& player, int skillNumber);
void printLine(int length);
void printSpace(int length);
void printStatRight(Player& player, int index);
void printStatLeft(Player& player, int index);
//void battle(Player& player, Entity oppoment);
// add things here later


//// functions (for game loop) ////
void readMap() {
    string line;
    ifstream file(mapFilePath); 
    // note to self: the current path setting will not run from VSCode execution
    // you will have to rely on batch compiling and exe for now

    while (getline(file, line)) {
        map.push_back(line);
    }
}

void setCodePage() {
    #ifdef _WIN32
    system("chcp 65001");
    system("cls");
    #endif
}

void gameStartScreen() {
    
    printSpace(30);
    printLine(65);
    this_thread::sleep_for(200ms);
    cout << endl;
    this_thread::sleep_for(200ms);
    cout << endl;
    this_thread::sleep_for(200ms);
    
    printSpace(30);
    cout << "   ___ __  __      \033[1;32m_    ____\033[0m          _                _      " << endl;
    printSpace(30);
    cout << "  |_ _|  \\/  |    \033[1;32m/ \\  / ___|\033[0m__ _  __| | ___ _ __ ___ (_) ___" << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "   | || |\\/| |   \033[1;32m/ _ \\| |\033[0m   / _` |/ _` |/ _ \\ '_ ` _ \\| |/ __|" << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "   | || |  | |  \033[1;32m/ ___ \\ |__\033[0m| (_| | (_| |  __/ | | | | | | (__ " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "  |___|_|  |_|_\033[1;32m/_/   \\_\\____\033[0m\\__,_|\\__,_|\\___|_| |_| |_|_|\\___|" << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "\033[31m  \\ \\      / / \\\033[0m   _ __ _ __(_) ___  _ __                     " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "\033[31m   \\ \\ /\\ / / _ \\\033[0m | '__| '__| |/ _ \\| '__|                    " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "\033[31m    \\ V  V / ___ \\\033[0m| |  | |  | | (_) | |                       " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "\033[31m     \\_/\\_/_/   \\_\\\033[0m_|  |_|  |_|\\___/|_|                     " << endl;
    this_thread::sleep_for(300ms);
    
    cout << endl;
    this_thread::sleep_for(300ms);

    cout << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(52);
    cout << "按 “ENTER” 進入下一頁" << endl;
    this_thread::sleep_for(300ms);

    cout << endl;
    this_thread::sleep_for(300ms);

    printSpace(30);
    printLine(65);
    cout << endl;
    this_thread::sleep_for(500ms);
    
    cin.ignore();

    clearScreen();
}

void printPreface() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;

    printSpace(50);
    cout << "----- 前言 -----"<< endl;
    cout << endl;
    printSpace(30);
    cout << "本遊戲由資管一的喻慈恩、黃靖媛、林妤娟、邱浚祐製作" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(30);
    cout << "內容取材自我們的生活經驗" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(30);
    cout << "如與你有任何雷同，純屬巧合" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(30);
    cout << "希望大家玩得愉快！" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    cout << endl;
    printSpace(30);
    cout << "2024.12" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    cout<<endl<<endl<<endl;
    
    printSpace(30);
    printLine(20+14+25);
    this_thread::sleep_for(chrono::milliseconds(300));

    cout<<endl;
    printSpace(30+20+18);
    cout << "按 “ENTER” 進入下一頁" <<endl;

    cout<<endl;

    cin.ignore();
    clearScreen();
}

void printSummary() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;
    
    printSpace(50);
    animateString("----- 前情提要 -----",18);
    cout << endl << endl;
    
    printSpace(30);
    animateString("你是臺大資管的大一菜鳥，帶著滿腔熱血與一絲忐忑",18);
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(30);
    animateString("踏入這座名為「大學」的迷宮",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    animateString("這裡充滿了未知的挑戰與無窮的可能性——",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    animateString("從初次見面的同學到眼花繚亂的選課系統",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    animateString("從期待已久的社團活動到令人頭痛的GPA壓力",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    cout<<endl;
    printSpace(30);
    animateString("然而，大學生活並非如想像般地一帆風順……",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    printSpace(30);
    animateString("「命運」猶如一道無形的力量，冷不防地將你推向天堂或是深淵",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    printSpace(30);
    animateString("而「機會」的天秤兩端總是令人難以取捨",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    cout<<endl;
    printSpace(30);
    animateString("作為一名新手冒險者，你準備好踏上這段喜淚交織的大學旅程了嗎？",18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl << endl;

    printSpace(30);
    printLine(20+14+25);

    cout<<endl;
    printSpace(30+20+18);
    cout << "按 “ENTER” 進入下一頁" <<endl;

    cin.ignore();
    clearScreen();
}

void gameMechanicScreen() {
    printSpace(30);
    printLine(65);

    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(58);
    cout << "----- 玩法說明 -----" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(35);
    cout << "WASD探索地圖          Y/N決定選項          ENTER進入下一頁" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(30);
    printLine(65);

    cin.ignore();
    clearScreen();
}

void printInstruction() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;
    
    printSpace(50);
    cout << "----- 操作說明 -----"<<endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    cout << "◆ 在迷宮裡，請以【WASD】控制角色移動以探索地圖" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    printSpace(30);
    cout << "◆ 遇上選擇時，請按【Y/N】以進行互動" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    printSpace(30);
    cout << "◆ 攻擊時，請按【1、2、3】以選擇技能" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl<<endl;

    printSpace(30);
    printLine(20+14+25);
    
    cout<<endl;
    printSpace(30+20+18);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "按 “ENTER” 進入下一頁" <<endl;
        
    cin.ignore();
    clearScreen();
}

void printGameStart() {
    cout<<endl<<endl<<endl<<endl;
    printSpace(50);
    string s = "“那麼，讓我們開始吧！”";
    cout << "\033[32m"; 
    for(int i=0; i<s.length(); i++) {
        cout << s[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << "\033[0m";
    this_thread::sleep_for(chrono::milliseconds(500));
    clearScreen();
}

// for updating camera screen
// to do here: figure out/design the guide!
void printMaze (bool visited[][MAP_W], Player& player) {

    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;

    for (int j = y-SCRN_HW; j <= y+SCRN_HW; j++) {
       
        if(j==y-SCRN_HW || j==y-SCRN_HW+1 || j==y-SCRN_HW+5 || j==y-SCRN_HW+7) {
            printStatLeft(player, j-(y-SCRN_HW));
        }
        else printSpace(50);

        for (int i = x-SCRN_HW; i <= x+SCRN_HW; i++) {

            if (i < 0 || i >= MAP_W || j < 0 || j >= MAP_H) {
                cout << "  "; // screen edge padding
            }

            else if (i == x && j == y) {
                cout << "@ "; // player marker
            }

            else if (visited[j][i]) cout << "\033[30;1m. \033[0m";

            else { // events and battles (and nothing)
                if (map[j][i] == 'c' || map[j][i] == 'd') cout << "\033[30;2m. \033[0m"; // accidents
                else if (map[j][i] == '.') cout << "\033[30;1m. \033[0m";
                else cout << map[j][i] << " "; // others
            }
            
        }
        printStatRight(player, j-(y-SCRN_HW));
        cout << "\n";
    }
    //cout << "Chance encountered: " << chanceEncounteredCnt << endl;
    
    cout << endl;
    printSpace(30);
    printLine(20+14+25);
    cout<<endl;
}


void animateString(string str, int ms) {
    for(int i=0; i<str.length(); i++) {
        cout << str[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
}

void animateStringForEnding(ifstream& inFile) {
    string str;
    while(getline(inFile, str)) {
        for(int i=0; i<str.length(); i++) {
            cout << str[i];
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(15));
        }
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }   
}

void timeBar() {
    for (int i = 0; i < chanceEncounteredCnt; i++) {
      cout << "█";
    }
    for (int i = 0; i < TERM_CHANCE_CNT - chanceEncounteredCnt; i++) {
        cout << "░";
    }
}


void moveCamera(int ch) {
switch(ch) {
    case KEY_UP:
        if (y-1 >= 0 && map[y-1][x] != '#') {
            y-=1;
        }
        break;
    case KEY_DOWN:
        if (y+1 < MAP_H && map[y+1][x] != '#') {
            y+=1;
        }
        break;
    case KEY_LEFT:
        if (x-1 >= 0 && map[y][x-1] != '#') {
            x-=1;
        }
        break;
    case KEY_RIGHT:
        if (x+1 < MAP_W && map[y][x+1] != '#') {
            x+=1;
        }
        break;
    }
}

void detectEvent (Player& player, bool visited[][MAP_W], bool triggeredChance[], bool triggeredDestiny[]) {
    if (!visited[y][x]) {
        visited[y][x] = true;
        char c = map[y][x];
        // replace cout below with functions to call
        if (c != '.') {
            //detectedEvent = true;
            int skillNumber = -1;
            if (c == 'c' || c == 'C') {
                cout << string(30, ' ') << "機會！\n";
                triggerChance(player, triggeredChance, skillNumber); //pass skillNumber by reference
                chanceEncounteredCnt++;
                cin.ignore();
            }
            else if (c == 'd' || c== 'D') {        //original: || c == 'D'
                cout << string(30, ' ') << "命運！\n";
                triggerDestiny(player, triggeredDestiny, skillNumber); //pass skillNumber by reference
            }
            else if (c == 'B') {
                clearScreen();
                cout << string(30, ' ') << "戰鬥！\n";
                triggerBattle(player);
            }

            buffer();

            // BELOW IS FOR TESTING REPLACESKILL (TEMP)
            cout << endl << skillNumber << endl;
            replaceSkillScreen(player, skillNumber);
            if(skillNumber >= 1 && skillNumber <= SKILL_CNT) {
               buffer();
            }
            
            
            clearScreen();
            printMaze(visited, player);
        }
    }
}

void printStatLeft(Player& player, int index) {
    if(index == 0){
        printSpace(35);
        cout << "【玩家座標】";
        printSpace(3);
    }
    if(index == 1) {
        printSpace(36);
        cout << "X: " << x << " Y: " << y;
        printSpace(3+(x<10)+(y<10));
    }
    if(index == 5){
        printSpace(35);
        cout << "【經過時間】";
        printSpace(3);
    }
    if(index == 7){
        printSpace(36);
        timeBar();
        printSpace(6);
    }  
}
void printStatRight(Player& player, int index) {
    if(index == 0) cout << "  【玩家 LV." << player.getLevel() << "】"; 
    if(index == 1) cout << "   ◆ ACA: " << player.getAcademic();
    if(index == 2) cout << "   ◆ SOC: " << player.getSocial();
    if(index == 3) cout << "   ◆ EMO: " << player.getEmo();
    if(index == 5) cout << "  【技能欄位】";
    if(index == 6) cout << "   ◆ "<< player.getSkill(0)->getName();
    if(index == 7) cout << "   ◆ "<< player.getSkill(1)->getName();
    if(index == 8) cout << "   ◆ "<< player.getSkill(2)->getName();
}

void printSpace(int length) {
    cout << string(length, ' ');
}

void printLine(int length) {
    for(int i=0;i<length;i++) cout << "═";
}

void detectChanceCnt(bool visited[][MAP_W], Player& player) {
        if (chanceEncounteredCnt == TERM_CHANCE_CNT / 2 && !midterms) {
            // midterms
            cout << string(30, ' ');
            animateString("\033[31m警告: 兩個月不知不覺地過去了，期中考來臨 :(\033[0m", 50);
            this_thread::sleep_for(500ms);
            clearScreen();

            //midterms boss battle
            triggerMidterms(player);

            buffer();
            clearScreen();
            printMaze(visited, player);
            midterms = true;

        }

        else if (chanceEncounteredCnt == TERM_CHANCE_CNT && !finals) {
            // finals
            cout << string(30, ' ');
            animateString("\033[31m警告: 兩個月不知不覺地過去了，期末專案來臨 :(\033[0m", 50);
            this_thread::sleep_for(500ms);
            clearScreen();

            //final boss battle
            triggerFinal(player);

            buffer();
            clearScreen();
            finals = true;
        }
}

bool detectEnding(Player& player) {
    if (finals) {
        player.printStatRight();
        cout << endl;
        // FIX CONDITIONS
        if (player.getEmo() >= 12) {
            ifstream inFile("../assets/ending/ending3.txt");
            animateStringForEnding(inFile);
            inFile.close();
        }
        else if (player.getAcademic() + player.getSocial() >= 30) {
            ifstream inFile("../assets/ending/ending2.txt");
            animateStringForEnding(inFile);
            inFile.close();
        }
        else if (player.getAcademic() >= 10) {
            ifstream inFile("../assets/ending/ending1.txt");
            animateStringForEnding(inFile);
            inFile.close();
        }
        else {
            ifstream inFile("../assets/ending/ending3.txt");
            animateStringForEnding(inFile);
            inFile.close();
        }
        cout << endl;
        return 1;
    }
    return 0;
}

void buffer() {
    this_thread::sleep_for(100ms);
    cout << "\033[4m按 “ENTER” 進入下一頁\033[0m ";
    cin.ignore();
}

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}


void replaceSkillScreen(Player& player, int skillNumber) {
    if(skillNumber < 1 || skillNumber > SKILL_CNT) 
        return;
    string choice = "";
    Skill newSkill = Skill(skillNumber);
    clearScreen();
    
    /*
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;
    */

    cout << "你獲得了新技能! \n";
    newSkill.printnewSkill();
    cout << endl;
    cout << "【現有技能】" << endl << endl;
    player.printSkillNeatly(0);
    cout << endl;

    // print the name of the gotten skill somehow
    cout << "你想用它取代現有技能嗎? [Press Y/N] "; 
    while (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) {
        cin >> choice;
        if (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) cout << "Wrong input. Please try again.\n";
    }
    if (choice == "Y" || choice == "y") {
        cout << "你想取代哪個現有技能? [Press 1~3] ";
        player.replaceSkill(skillNumber);
    }
    else cin.ignore();
}

//// main function //// 
int main () {
    int ch; // for reading arrow key
    bool end = 0; // for game loop
    bool visited[MAP_H][MAP_W] = {0};
    bool triggeredChance[CHANCE_CNT] = {0};
    bool triggeredDestiny[DESTINY_CNT] = {0};
    string input;

    // initialize player (test)
    Player player(20, 12, 8);

    setCodePage(); // for WIN32

    readMap();

    clearScreen();
    //gameStartScreen();
    //printPreface();
    //printSummary();
    //printInstruction();
    //printGameStart();

    printMaze(visited, player);

    while (!end) {
        ch = 0;

        // arrow key mode
        if (c_kbhit()) {
            ch = c_getch(); // for modifications, see testMaze.cpp for ref
            if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
                //cerr << "";

                moveCamera(ch);
                clearScreen();

                printMaze(visited, player);

                detectEvent(player, visited, triggeredChance, triggeredDestiny);
                detectChanceCnt(visited, player); // for special events (like midterms)
                end = detectEnding(player);
            }
        }
        this_thread::sleep_for(25ms);
    }

}