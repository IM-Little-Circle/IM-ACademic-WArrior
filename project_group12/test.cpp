#include <iostream>
#include <fstream>
#include <string>
#include "test_player.h"

using namespace std;

int main() {
    #ifdef _WIN32
    system("chcp 65001");
    system("cls");
    #endif

    Player player(100, 10, 5);
    cout << player.getAcademic() << endl;

    ifstream inFile;
    inFile.open("./sources/ending/ending1.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
    return 0;
}