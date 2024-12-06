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
        int getLevel();
        Skill* getSkill(int skillNumber);

		void updateStatus();
        void fullRecover();
        void setInitialStat(int aca, int soc, int e);

        void levelUp();
        void getExp(int experience);
        // below added for testing
        void printStatRight();
        void printStatRight(int oriAca, int oriSoc, int oriEmo);
        void printSkill(int skillnumber);
        void printnewSkill(int skillnumber);

        //skill print
        void printSkillName(int skillIndex);
        void printSkillType(int skillIndex);
        void printSkillCoolRound(int skillIndex);
        void printSkillPercent(int skillIndex);

        //skill
        Skill* fetchSkill(int filenumber); // read file for skill
        void replaceSkill(int filenumber);
        void useSkill(Entity& enemy, Skill skill);
        void useSkill(Entity& enemy, int chooseNumber);
        void skillCool();
        bool isCool(int skillNumber);
        void skillReset();
        

        
};

