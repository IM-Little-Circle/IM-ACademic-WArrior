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
#include "battle.h"

using namespace std;
/* ###bug notes###
found new bug: if arrow key pressed for too long (more than 25ms i think)
console will keep running the input 
fix, maybe with this_thread sleep or something
new issue found @2024/11/24: if right arrow key pressed for a while and then ran into a chance, 
                             as cin >> choice is waiting for input, 
                             the right arrow key will result in a 'y' input.
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
const int chanceCnt = 2; //number of chances, must >= 1
const int destinyCnt = 2; //number of destinies, must >= 1


//// declare functions ////
void readMap();
void printMaze(bool visited[][MAP_W]);
void moveCamera(int ch);
void detectEvent(Player& player);
void displayEvent(ifstream& inFile);
void displayChoiceChance(ifstream& inFile, string choice);
void displayChoiceDestiny(ifstream& inFile, string choice);
void modifyParameters(Player& player, int parameters[], string choice);
void parseChance(ifstream& inFile, Player& player);
void parseDestiny(ifstream& inFile, Player& player);
void triggerChance(Player& player);
void triggerDestiny(Player& player);
void triggerBattle(Player& player);
//void battle(Player& player, Entity oppoment);
// add things here later


//// functions (for game loop) ////
void readMap() {
    string line;
    ifstream file("../assets/testEventMap.txt"); 
    // note to self: the current path setting will not run from VSCode execution
    // you will have to rely on batch compiling and exe for now

    while (getline(file, line)) {
        map.push_back(line);
    }
}

// for updating camera screen
// question: how should we print the guide (press i for smtn smtn), at the right or bottom?
// to do here: figure out/design the guide!
void printMaze (bool visited[][MAP_W]) {
    for (int j = y-SCRN_HW; j <= y+SCRN_HW; j++) {

        cout << string(50, ' '); //padding

        for (int i = x-SCRN_HW; i <= x+SCRN_HW; i++) {

            if (i < 0 || i >= MAP_W || j < 0 || j >= MAP_H) {
                cout << "  "; // screen edge padding
            }

            else if (i == x && j == y) {
                cout << "@ "; // player marker
                visited[j][i] = 1;
            }

            else if (visited[j][i]) cout << ". ";

            else if (i == 18 && j == 18) cout << "E"; // temp, for ending game

            else { // events and battles (and nothing)
                if (map[j][i] == 'c' || map[j][i] == 'd') cout << ". "; // accidents
                else cout << map[j][i] << " "; // others
                //cout << map[j][i] << " ";
                //cout << ". ";
            }

        }
        
        cout << "\n";
    }
    // for debugging: cout pos
    cout << string(50, ' ') << x << " " << y << endl;
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

void detectEvent (Player& player){
    char c = map[y][x];
    // replace cout below with functions to call
    if (c != '.') {
        //detectedEvent = true;
        if (c == 'c' || c == 'C') {
            cout << string(50, ' ') << "Chance!";
            triggerChance(player);
        }
        else if (c == 'd' || c == 'D') {
            cout << string(50, ' ') << "Destiny!";
            triggerDestiny(player);
        }
        else if (c == 'B') {
            cout << string(50, ' ') << "Battle!";
            triggerBattle(player);
        }
    }
    cout << endl;

}


//// functions (for events handling) ////
void displayEvent(ifstream& inFile) {
    string readFile;
    getline(inFile, readFile, '#');
    cout << readFile;
}

void displayChoiceChance(ifstream& inFile, string choice) {
    string readFile;

    if ((choice == "Y") || (choice == 'y')) {
        // chosen Y
        getline(inFile, readFile, '#');
        cout << readFile;
    }
    else {
        //chosen N
        std::getline(inFile, readFile, '#'); // ignore Y choice section
        std::getline(inFile, readFile, '#');
        cout << readFile;
    }
}

void displayChoiceDestiny(ifstream& inFile, string choice) {
    string readFile;

    //forced to choose Y
    getline(inFile, readFile, '#');
    cout << readFile;
}

void modifyParameters(Player& player, int parameters[], string choice) {
    if (choice == "Y") {
        player.modifyAcademic(parameters[0]);
        player.modifySocial(parameters[1]);
        player.modifyEmo(parameters[2]);
    }
    else {
        player.modifyAcademic(parameters[3]);
        player.modifySocial(parameters[4]);
        player.modifyEmo(parameters[5]);
    }
}

void parseChance(ifstream& inFile, Player& player) {
    string choice = "";

    int parameters[6] = {0}; // acaTrue, socTrue, emoTrue, acaFalse, socFalse, emoFalse
    for (int i = 0; i < 6; i++) {
        inFile >> parameters[i];
    }

    // print the event
    displayEvent(inFile);

    // choose [Y | N]
    while (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) {
        cin >> choice;
        if (!(choice == "Y" || choice == "N"|| choice == "y"|| choice == "n")) cout << "Wrong input. Please try again.\n";
    }

    // print result based on choice
    displayChoiceChance(inFile, choice);
    modifyParameters(player, parameters, choice);
}

void parseDestiny(ifstream& inFile, Player& player) {
    const string choice = "Y"; //forced to choose Y

    int parameters[3] = {0}; // acaTrue, socTrue, emoTrue
    for (int i = 0; i < 3; i++) {
        inFile >> parameters[i];
    }

    // print the event
    displayEvent(inFile);

    // print result based on choice
    displayChoiceChance(inFile, choice);
    modifyParameters(player, parameters, choice);
}

void triggerChance(Player& player) {
    int i = rand() % (chanceCnt - 1 + 1) + 1; //i = a random number between 1 and chanceCnt
    ifstream inFile("../assets/chance" + to_string(i) + ".txt");
    cout << "Chance " << i << " triggered\n"; //shall be deleted as game development finishes

    if (inFile.fail()) {
        cout << "File not found\n";
        return;
    }

    parseChance(inFile, player);
    player.printStat();

    inFile.close();
    player.levelUp();
}

void triggerDestiny(Player& player) {
    int i = rand() % (destinyCnt - 1 + 1) + 1; //i = a random number between 1 and chanceCnt
    ifstream inFile("../assets/destiny" + to_string(i) + ".txt");
    cout << "Destiny " << i << " triggered\n"; //shall be deleted as game development finishes

    if (inFile.fail()) {
        cout << "File not found\n";
        return;
    }

    parseDestiny(inFile, player);
    player.printStat();

    inFile.close();
    player.levelUp();
}

void triggerBattle(Player& player){
    Entity oppoment(30, 30, 30); // 要怎麼找敵人?
    battle(player, oppoment);
}

//// main function //// 
int main () {
    int ch; // for reading arrow key
    bool end = 0; // for game loop
    bool visited[MAP_H][MAP_W] = {0};
    string input;

    // initialize player (test)
    Player player(10, 10, 10);


    readMap();

    printMaze(visited);

    while (!end) {
        ch = 0;

        // arrow key mode
        if (c_kbhit()) {
            ch = c_getch(); // for modifications, see testMaze.cpp for ref
            if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
                
                moveCamera(ch);

                #ifdef _WIN32
                system("cls");
                #elif __linux__
                system("clear");
                #endif

                printMaze(visited);
                detectEvent(player);
                if (x == 18 && y == 18) end = 1; // temp, for ending game
            }
        }
        this_thread::sleep_for(25ms);
    }

}