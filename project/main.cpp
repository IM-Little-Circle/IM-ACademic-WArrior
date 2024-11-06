#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iomanip>

// below are user-made header files
#include "event.h"

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


// BIG QUESTION: how do we read the generated pos/info for each event? 
// -> how do we read all the current existing events
// store them in a vector, then once it's triggered, delete the element? list? some other data structure?

// info can be generated beforehand, or when event is triggered ig



//// functions (for game loop) ////
void readMap() {
    string line;
    ifstream file("../map.txt");

    while (getline(file, line)) {
        map.push_back(line);
    }
}

// for updating camera screen
// question: how should we print the guide (press i for smtn smtn), at the right or bottom?
// to do here: figure out/design the guide!
void printMaze (bool visited[][MAP_W], int x, int y) {
    for (int j = y-SCRN_HW; j <= y+SCRN_HW; j++) {

        cout << setw(50); // for setting screen to center

        for (int i = x-SCRN_HW; i <= x+SCRN_HW; i++) {

            if (i == x && j == y) {
                cout << "@ "; // player marker
                visited[j][i] = 1; // necessary? (see below at declaration)
            }

            else if (i == 18 && j == 18) cout << "E"; // temp, for ending game

            else if (i < 0 || i > 19 || j < 0 || j > 19) {
                cout << "  "; // screen edge padding
            }

            else cout << map[j][i] << " ";

        }
        
        cout << "\n";
    }
}


void moveCamera(int ch) {
switch(ch) {
        case KEY_UP:
            if (y-1 >= 0 && map[y-1][x] == '.') {
                y-=1;
            }
            break;
        case KEY_DOWN:
            if (y+1 < 20 && map[y+1][x] == '.') {
                y+=1;
            }
            break;
        case KEY_LEFT:
            cout << left << endl;
            if (x-1 >= 0 && map[y][x-1] == '.') {
                x-=1;
            }
            break;
        case KEY_RIGHT:
            if (x+1 < 20 && map[y][x+1] == '.') {
                x+=1;
            }
            break;
    }
}


//// main function //// 
int main () {
    int ch; // for reading arrow key
    bool end; // for game loop
    bool visited[MAP_H][MAP_W] = {0}; // is this necessary? (recording trodden paths with ',')

    // test event
    Event testevent;

    readMap();

    printMaze(visited, x, y);

    while (!end) {
        ch = 0;
        if (kbhit()) {
                ch = getch(); // for modifications, see testMaze.cpp for ref
            if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
                
                moveCamera(ch);

                system("cls");
                printMaze(visited, x, y);
                if (x == 18 && y == 18) end = 1; // temp, for ending game
            }
        }
        this_thread::sleep_for(chrono::milliseconds(25));
    }

}