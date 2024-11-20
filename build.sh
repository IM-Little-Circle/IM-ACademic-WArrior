#g++ source_code/main.cpp -o build/game.exe -Wall -std=c++17 -Iinclude
#still not able to run since apple clang has an error with "features.h not found" while including <iostream>
g++ source_code/main.cpp source_code/entity.cpp include/conio.c -o build/game.exe -std=c++17 -Iinclude -D__linux__