// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include "entity.h"
#include "skill.h"
using namespace std;

class Player : public Entity {
    private:
        int x;
        int y;
        int exp = 0;
        // initialized for testing
        int academic = 0; 
        int social = 0;
        int emo = 0;
        Skill** skill = new Skill*[3];
    public:
        Player(int hp, int atk, int def);
        void modifyAcademic(int change);
        void modifySocial(int change);
        void modifyEmo(int change);

        int getAcademic();
        int getSocial();
        int getEmo();

		void updateStatus();
        void fullRecover();
        void setInitialStat(int aca, int soc, int e);

        void levelUp();
        void getExp(int experience);
        // below added for testing
        void printStat();
        void printSkill(int skillnumber);

        //skill
        Skill* getSkill(int filenumber);
        void replaceSkill(int filenumber);
        void useSkill(Entity enemy, Skill skill);
        //void useSkill(Entity enemy, int chooseNumber);
        void skillCool();
};

