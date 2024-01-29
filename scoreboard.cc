#include "scoreboard.h"

Scoreboard::Scoreboard() : whiteScore(0), blackScore(0)  {}

void Scoreboard::addResult(Colour colour, float points) {
    // If black player won, add points to the black player's score
    if (colour == Colour::Black) {
        blackScore+= points;
    }
    // If white player won, add points to the white player's score
    else {
        whiteScore += points;
    }
}

ostream& operator<<(ostream& out, Scoreboard& s) {
    // Outputs the scoreboard
    out << "Final Score:" << endl;
    out << "White: " << s.whiteScore << endl;
    out << "Black: " << s.blackScore << endl;
    return out;
}
