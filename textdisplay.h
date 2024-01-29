#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "observer.h"
#include <iostream>
#include <vector>
#include "enumerations.h"
using namespace std;

class ChessBoard;
class Square;

class TextDisplay: public Observer {
  vector<vector<char>> theDisplay;
 
  public:
    // Ctor
    TextDisplay();

    // theDisplay is updated based on what squares were updated on the board
    void notify(vector<Square*>& updatedSquares, ChessBoard& board) override;

    // Returns the subscription type
    SubscriptionType getSubType() override;

    // Dtor
    ~TextDisplay();

    // Outputs theDisplay to the out stream provided
    friend ostream &operator<<(ostream &out, const TextDisplay &td);
};
#endif
