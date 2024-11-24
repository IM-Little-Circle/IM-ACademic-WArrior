#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

class playSprite {
public:
    playSprite(int a, int b);
    bool checkAt(int a, int b);
    void move(int a, int b);
    int x;
    int y;
};

class Sprite {
public:
    Sprite(int a, int b);
    bool checkAt(int a, int b);
    int x;
    int y;
};

void playSprite::move(int a, int b) {
    if (a == -1) {
        if (x > 0) x -= 1;
    }
    if (a == 1) {
        if (x < 9) x += 1;
    }
    if (b == -1) {
        if (y > 0) y -= 1;
    }
    if (b == 1) {
        if (y < 9) y += 1;
    }

}

playSprite::playSprite(int a, int b) {
    x = a;
    y = b;
};

bool playSprite::checkAt(int a, int b) {
    if (a == x && b == y) return true;
    return false;
}

bool Sprite::checkAt(int a, int b) {
    if (a == x && b == y) return true;
    return false;
}

Sprite::Sprite(int a, int b) {
    x = a;
    y = b;
};


playSprite player(0, 0);
Sprite a(4, 5);
Sprite b(2, 8);
Sprite c(7, 2);
Sprite finish(6, 4);

void printMaze (bool visited[][10]) {
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (player.checkAt(i, j)) {
                cout << "@ ";
                visited[j][i] = 1;
            }
            else if (visited[j][i]) {
                cout << ", ";
            }
            else if (a.checkAt(i, j)) {
                cout << "A ";
            }
            else if (b.checkAt(i, j)) {
                cout << "B ";
            }
            else if (c.checkAt(i, j)) {
                cout << "C ";
            }
            else if (finish.checkAt(i, j)) {
                cout << "T ";
            }
            else cout << ". ";
        }
        cout << "\n";
    }
}

void printCreature(int s) {
    cout << "\n";
    switch(s) {
        case 1:
            cout << "  /\\_/\\  \n ( o.o ) \n > ^ ^ < \n";
            break;
        case 2:
            cout << "  >_<  \n /o o\\ \n \\_-_/ \n";
            break;
        case 3:
            cout << " / \\__\n(    @\\___\n /         O\n/   (_____/\n/_____/   U\n";
            break;
    }
}

int main () {
    int ch;
    bool visited[10][10] = {0};
    bool end = 0;
    int mode = 0;
    printMaze(visited);
    while (!end) {
        ch = 0;
        if (!mode) {
            if (kbhit()) {
                ch = getch();
                if (ch == KEY_ENTER) {
                    mode = abs(mode-1);
                    //cout << mode;
                    continue;
                }
                else {
                    if (ch == KEY_UP||ch == KEY_DOWN ||ch == KEY_LEFT||ch == KEY_RIGHT) {
                        switch(ch) {
                            case KEY_UP:
                                player.move(0, -1);
                                break;
                            case KEY_DOWN:
                                player.move(0, 1);
                                break;
                            case KEY_LEFT:
                                player.move(-1, 0);
                                break;
                            case KEY_RIGHT:
                                player.move(1, 0);
                                break;
                        }
                    }
                }

                    system("cls");
                    printMaze(visited);
                    if (player.checkAt(finish.x, finish.y)) end = 1;
                    else if (player.checkAt(a.x, a.y)) {
                        printCreature(1);
                    }
                    else if (player.checkAt(b.x, b.y)) {
                        printCreature(2);
                    }
                    else if (player.checkAt(c.x, c.y)) {
                        printCreature(3);
                    }
            }
        } else {
                //if (cin.peek() != '\n') {  // Check for cin input
                    cout << "#Input Mode#\n";
                    string input;
                    getline(cin, input);
                    if (input == "inv") {
                        cout << "You have: Nothing!\n";
                    }
                    else if (input == "save") {
                        cout << "You haven't designed a save system yet, idiot D:\n";
                    }
                    else if (input == "exit") {
                        end = 1;
                    }
                    else cout << "Not a valid comment!\n";
                //}
                mode = 0;
            }
        this_thread::sleep_for(50ms);
    }
}
