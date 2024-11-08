// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main

class Event {
    private:
        int x;
        int y;
        
    public:
        Event();
        
};

Event::Event() {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
}

