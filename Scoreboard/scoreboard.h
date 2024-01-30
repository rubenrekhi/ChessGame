#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__
#include <vector>
#include <iostream>
#include "enumerations.h"
using namespace std;

class Scoreboard {
    float whiteScore; // Score of the white Player
    float blackScore; // Score of the black Player

    public:
        // Ctor
        Scoreboard();    

        // Adds the result of the previous game onto the scoreboard    
        void addResult(Colour colour, float points);

        // declaring << operator as a friend
        friend ostream& operator<<(ostream& out, Scoreboard& s);
    
};
#endif
