// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main

class Player {
    private:
        int x;
        int y;
        int academic;
        int social;
        int emo;
    public:
        Player();

        
};

Player::Player() {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
}