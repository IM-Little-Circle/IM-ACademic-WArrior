::g++ main.cpp -o build/game.exe -Wall -std=c++17 -Iinclude
if not exist "build" mkdir build
g++ main.cpp entity.cpp event.cpp player.cpp battle.cpp skill.cpp include/conio.c -o build/game.exe -std=c++17 -Iinclude -D__linux__
