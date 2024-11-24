#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "myconio.h"
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <thread>
#include "player.h"
#include "event.h"

// below are user-made header files
//#include "event.h"
//#include "../Windows_Only_Header_Files/windows.h" //still working on this...

using namespace std;

// found new bug: if arrow key pressed for too long (more than 25ms i think)
// console will keep running the input 
// fix, maybe with this_thread sleep or something

//// conio.h keys ////
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
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


//// header file member functions ////

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

void detectEvent(Player& player) {
    Event funcCaller;
    char c = map[y][x];
    // replace cout below with functions to call
    if (c == 'c' || c == 'C') {
        cout << string(50, ' ') << "Chance!";
        funcCaller.triggerChance(player);
    }
    else if (c == 'd' || c == 'D') {
        cout << string(50, ' ') << "Destiny!";
    }
    else if (c == 'B') {
        cout << string(50, ' ') << "Battle!";
    }
    cout << endl;
}


//// main function //// 
int main () {
    int ch; // for reading arrow key
    bool end = 0; // for game loop
    bool visited[MAP_H][MAP_W] = {0};

    // initialize player (test)
    Player player(10, 10, 10);


    readMap();

    printMaze(visited);

    while (!end) {
        ch = 0;
        if (c_kbhit()) {
                ch = c_getch(); // for modifications, see testMaze.cpp for ref
            if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
                
                moveCamera(ch);

                system("cls");
                printMaze(visited);
                detectEvent(player);
                if (x == 18 && y == 18) end = 1; // temp, for ending game
            }
        }
        this_thread::sleep_for(25ms);
    }

}