::g++ source_code/main.cpp -o build/game.exe -Wall -std=c++17 -Iinclude
if not exist "build" mkdir build
g++ source_code/main.cpp source_code/entity.cpp source_code/event.cpp source_code/player.cpp source_code/battle.cpp source_code/skill.cpp include/conio.c -o build/game.exe -std=c++17 -Iinclude -D__linux__
