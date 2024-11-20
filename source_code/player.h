// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include "entity.h"
using namespace std;

class Player : public Entity {
    private:
        int x;
        int y;
        
        // initialized for testing
        int academic = 0; 
        int social = 0;
        int emo = 0;
    public:
        Player(int hp, int Atk, int Def);
        void modifyAcademic(int change);
        void modifySocial(int change);
        void modifyEmo(int change);
		void updateStatus();

        // below added for testing
        void printStat();
        void setInitialStat(int aca, int soc, int e);
        
};

