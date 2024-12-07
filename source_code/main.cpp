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

// here are some global variables for now, wrap them up later
vector<string> map;
// pos mainly to control camera movement, put in player class
int x = 7;
int y = 7; //btw the pos is temp too
int chanceEncounteredCnt = 0;
bool midterms = false, finals = false;
extern const int CHANCE_CNT; //number of chances, must >= 1
extern const int DESTINY_CNT; //number of destinies, must >= 1
const int SKILL_CNT = 3; // number of skills, note that skill 1-3 are starters, not included here

//// declare functions ////
void buffer(); // press enter to continue
void setCodePage();
void clearScreen(); // system cls/clear
<<<<<<< Updated upstream
void gameStartScreen();
void animateString(string str);
=======

void printTitle();
void printPreface();
void printSummary();
void printInstruction();
void printGameStart();

void gameMechanicScreen();
void animateString(string str, int ms); 
void animateStringForEnding(ifstream& inFile);
void timeBar();
>>>>>>> Stashed changes
void readMap();
void printMaze(bool visited[][MAP_W]);
void moveCamera(int ch);
void detectEvent(Player& player, bool visited[][MAP_W], bool triggeredChance[], bool triggeredDestiny[]);
void detectChanceCnt(Player& player);
void replaceSkillScreen(Player& player);
void printLine(int length);
void printSpace(int length);
void printStat(Player& player, int index);
//void battle(Player& player, Entity oppoment);
// add things here later


//// functions (for game loop) ////
void readMap() {
    string line;
    ifstream file("../assets/map/testEventMap.txt"); 
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

<<<<<<< Updated upstream
void gameStartScreen() {
    cout << "GAME START\n";
    buffer();
=======
void printTitle() {
    
    printSpace(30);
    printLine(65);
    this_thread::sleep_for(200ms);
    cout << endl;
    this_thread::sleep_for(200ms);
    cout << endl;
    this_thread::sleep_for(200ms);
    
    printSpace(30);
    cout << "   ___ __  __      _    ____          _                _      " << endl;
    printSpace(30);
    cout << "  |_ _|  \\/  |    / \\  / ___|__ _  __| | ___ _ __ ___ (_) ___" << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "   | || |\\/| |   / _ \\| |   / _` |/ _` |/ _ \\ '_ ` _ \\| |/ __|" << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "   | || |  | |  / ___ \\ |__| (_| | (_| |  __/ | | | | | | (__ " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "  |___|_|  |_|_/_/   \\_\\____\\__,_|\\__,_|\\___|_| |_| |_|_|\\___|" << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "  \\ \\      / / \\   _ __ _ __(_) ___  _ __                     " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "   \\ \\ /\\ / / _ \\ | '__| '__| |/ _ \\| '__|                    " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "    \\ V  V / ___ \\| |  | |  | | (_) | |                       " << endl;
    this_thread::sleep_for(300ms);
    
    printSpace(30);
    cout << "     \\_/\\_/_/   \\_\\_|  |_|  |_|\\___/|_|                     " << endl;
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
    printSpace(30);
    cout << "內容取材自我們的生活經驗" << endl;
    printSpace(30);
    cout << "如與你有任何雷同，純屬巧合" << endl;
    printSpace(30);
    cout << "希望大家玩得愉快！" << endl;
    cout << endl;
    printSpace(30);
    cout << "2024.12" << endl;
    cout<<endl<<endl<<endl;
    
    printSpace(30);
    printLine(20+14+25);

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
    animateString("----- 前情提要 -----",20);
    cout << endl << endl;
    
    printSpace(30);
    animateString("你是臺大資管的大一菜鳥，帶著滿腔熱血與一絲忐忑",20);
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    printSpace(30);
    animateString("踏入這座名為「大學」的迷宮",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    animateString("這裡充滿了未知的挑戰與無窮的可能性——",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    animateString("從初次見面的同學到眼花繚亂的選課系統",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    printSpace(30);
    animateString("從期待已久的社團活動到令人頭痛的GPA壓力",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl;

    cout<<endl;
    printSpace(30);
    animateString("然而，大學生活並非如想像般地一帆風順……",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    printSpace(30);
    animateString("「命運」猶如一道無形的力量，冷不防地將你推向天堂或是深淵",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    printSpace(30);
    animateString("而「機會」的天秤兩端總是令人難以取捨",20);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout<<endl;

    cout<<endl;
    printSpace(30);
    animateString("作為一名新手冒險者，你準備好踏上這段喜淚交織的大學旅程了嗎？",20);
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

void printInstruction() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;
    
    printSpace(50);
    cout << "----- 操作說明 -----"<<endl;
    cout << endl;

    printSpace(30);
    cout << "◆ 在迷宮裡，請以【WASD】控制角色移動以探索地圖" << endl;
    cout<<endl;
    printSpace(30);
    cout << "◆ 遇上選擇時，請按【Y/N】以進行互動" << endl;
    cout<<endl;
    printSpace(30);
    cout << "◆ 攻擊時，請按【1、2、3】以選擇技能" << endl;
    cout<<endl<<endl;
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
>>>>>>> Stashed changes
    clearScreen();
}

void printGameStart() {
    cout<<endl<<endl<<endl<<endl;
    printSpace(50);
    string s = "那麼，讓我們開始吧！";
    cout << "\033[34m"; 
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
// question: how should we print the guide (press i for smtn smtn), at the right or bottom?
// to do here: figure out/design the guide!
void printMaze (bool visited[][MAP_W]) {

    printSpace(25);
    printLine(25+14+25);
    cout<<endl;
    cout<<endl;

    for (int j = y-SCRN_HW; j <= y+SCRN_HW; j++) {
    
        printSpace(50);
        for (int i = x-SCRN_HW; i <= x+SCRN_HW; i++) {

            if (i < 0 || i >= MAP_W || j < 0 || j >= MAP_H) {
                cout << "  "; // screen edge padding
            }

            else if (i == x && j == y) {
                cout << "@ "; // player marker
            }

            else if (visited[j][i]) cout << ". ";

            else if (i == 18 && j == 18) cout << "E"; // temp, for ending game

            else { // events and battles (and nothing)
                if (map[j][i] == 'c' || map[j][i] == 'd') cout << ". "; // accidents
                else cout << map[j][i] << " "; // others
                //cout << map[j][i] << " ";
                //cout << ". ";
            }
            printStat(player, 0);
        }
        
        cout << "\n";
    }
    // for debugging: cout pos
    cout << string(50, ' ') << x << " " << y << string (20, ' ') << "Chance encountered: " << chanceEncountered << endl;
    
    printSpace(25);
    printLine(25+14+25);
    cout<<endl;
}


void animateString(string str) {
    for(int i=0; i<str.length(); i++) {
        cout << str[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
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
        visited[y][x] = 1;
        char c = map[y][x];
        // replace cout below with functions to call
        if (c != '.') {
            //detectedEvent = true;
            if (c == 'c' || c == 'C') {
                cout << string(50, ' ') << "Chance!\n";
                triggerChance(player, triggeredChance);
                chanceEncounteredCnt++;
                cin.ignore();
            }
            else if (c == 'd') {        //original: || c == 'D'
                cout << string(50, ' ') << "Destiny!\n";
                triggerDestiny(player, triggeredDestiny);
            }
            else if (c == 'B') {
                cout << string(50, ' ') << "Battle!\n";
                triggerBattle(player);
                cin.ignore();
            }

            buffer();

            // BELOW IS FOR TESTING REPLACESKILL (TEMP)
            replaceSkillScreen(player);
            buffer();
            
            clearScreen();
            printMaze(visited);
        }
    }
}

void printStat(Player& player, int index) {
    if(index == 0) cout << "Stat: \n";
    if(index == 1) cout << "Academic: " << player.getAcademic();
    if(index == 2) cout << "Social:  " << player.getSocial();
}

void printSpace(int length) {
    cout << string(length, ' ');
}

void printLine(int length) {
    for(int i=0;i<length;i++) cout << "═";

void detectChanceCnt(bool visited[][MAP_W]) {
        if (chanceEncounteredCnt == 2 && !midterms) {
            // midterms
            cout << string(20, ' ');
            animateString("NOTE: Two months have passed. Entering midterms :(");
            this_thread::sleep_for(500ms);
            clearScreen();
            buffer();
            clearScreen();
            printMaze(visited);
            midterms = true;

        }

        else if (chanceEncounteredCnt == 4 && !finals) {
            // finals
            cout << string(20, ' ');
            animateString("NOTE: Two months have passed. Entering finals :(");
            this_thread::sleep_for(500ms);
            clearScreen();
            buffer();
            clearScreen();
            finals = true;
        }
}

bool detectEnding(Player& player) {
    if (finals) {
        player.printStat();
        // FIX CONDITIONS
        if (player.getAcademic() > 25) {
            cout << "ACADEMIC ENDING\n";
        }
        else if (player.getSocial() > 20) {
            cout << "SOCIAL ENDING\n";
        }
        else {
            cout << "MCDONALDS ENDING\n";
        }
        return 1;
    }
    return 0;
}

void buffer() {
    this_thread::sleep_for(100ms);
    cout << "Press Enter to Continue\n";
    cin.ignore();
}

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}


//// functions (for events handling) ////

void replaceSkillScreen(Player& player) {
    // get random skill
    int skillNumber = rand() % (SKILL_CNT) + 4;
    string choice = "";
    Skill newSkill = Skill(skillNumber);
    clearScreen();
    cout << "You get new skill! \n";
    newSkill.printSkill();

    
    cout << "Your current skills: \n";
    cout << "1. ";
    player.printSkill(0);
    cout << "2. ";
    player.printSkill(1);
    cout << "3. ";
    player.printSkill(2);
    cout << endl;

    // print the name of the gotten skill somehow
    cout << "You have gotten new skill!\nDo you want to switch one of your skills for this? "; 
    while (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) {
        cin >> choice;
        if (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) cout << "Wrong input. Please try again.\n";
    }
    if (choice == "Y" || choice == "y") {
        cout << "Which one do you want to change?\n";
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
    Player player(10, 10, 10);

    setCodePage(); // for WIN32

    //gameStartScreen();

    readMap();

<<<<<<< Updated upstream
    printMaze(visited);
=======
    printTitle();
    printPreface();
    printSummary();
    printInstruction();
    printGameStart();

    printMaze(visited, player);
>>>>>>> Stashed changes

    while (!end) {
        ch = 0;

        // arrow key mode
        if (c_kbhit()) {
            ch = c_getch(); // for modifications, see testMaze.cpp for ref
            if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
                
                moveCamera(ch);
                clearScreen();

                printMaze(visited);

                if (x == 18 && y == 18) end = 1; // temp, for ending game

                detectEvent(player, visited, triggeredChance, triggeredDestiny);
                detectChanceCnt(visited); // for special events (like midterms)
                end = detectEnding(player);
            }
        }
        this_thread::sleep_for(25ms);
    }

}