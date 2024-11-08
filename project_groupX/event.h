// note: keep trivial function definitions in header file
// define non-trivial (important) functions in main
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::cin;
using std::cout;


class Event {
    private:
        int x;
        int y;
        
    public:
        Event();
        char* readPlot();
};

Event::Event() {
    // temp, set random pos upon initialization
    x = 5;
    y = 5;
}

char* Event::readPlot()
{
    char* str = NULL;
    ifstream in("../chance1.txt");

    //for(int i = 0; i < 9; i++)
    //    in.ignore();
    
    in >> str;

    if(in.fail())
        return "Event file NOT FOUND"; // fix this part
    else
        return str;
}

