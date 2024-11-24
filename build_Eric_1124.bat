::g++ source_code/main.cpp -o build/game.exe -Wall -std=c++17 -Iinclude
if not exist "build" mkdir build
g++ testEric_1124/main.cpp testEric_1124/entity.cpp testEric_1124/player.cpp include/conio.c -o build/game.exe -std=c++17 -Iinclude -D__linux__
