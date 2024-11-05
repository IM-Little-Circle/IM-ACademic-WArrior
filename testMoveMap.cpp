#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;
vector<string> map;


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13


void printMaze (bool visited[][20], int x, int y) {
    for (int j = y-4; j <= y+4; j++) {
        for (int i = x-4; i <= x+4; i++) {
            if (i == x && j == y) {
                cout << "@ ";
                visited[j][i] = 1;
            }
            else if (i == 18 && j == 18) cout << "E";
            else if (i < 0 || i > 19 || j < 0 || j > 19) {
                cout << "  ";
            }
            else cout << map[j][i] << " ";
        }
        cout << "\n";
    }
}

int main () {
    int ch;
    bool end;
    bool visited[20][20] = {0};
    int x = 7, y = 7;
    string line;
    ifstream file("c:/Programming/NTUIM/test/testmap.txt");
 
    while (getline(file, line)) {
        map.push_back(line);
    }

    printMaze(visited, x, y);
    while (!end) {
        ch = 0;
        if (kbhit()) {
                ch = getch();
            if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
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
                
                system("cls");
                printMaze(visited, x, y);
                if (x == 18 && y == 18) end = 1;
            }
        }
        this_thread::sleep_for(25ms);
    }

}