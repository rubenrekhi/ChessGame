#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "enumerations.h"
#include "square.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "player.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class Computer : public Player {
    // private fields
    int level; // The computer's level of difficulty

    // public methods
    public:
        // Ctor
        Computer(Colour colour, Square* kingLocation, ChessBoard* board, vector<ChessPiece*>& pieces, int level);
        
        // Moves the computer's chess piece based on what level the computer is
        bool move(vector<Square*>& updatedSquares) override;

        // Returns the player type
        PlayerType getPlayerType() override;
    
    // private methods
    private:
        // Algorithm that determines the move computer will make at level 1
        void moveAlg1(vector<Square*>& updatedSquares);

        // Algorithm that determines the move computer will make at level 2
        void moveAlg2(vector<Square*>& updatedSquares);

        // Algorithm that determines the move computer will make at level 3
        void moveAlg3(vector<Square*>& updatedSquares);

        // Algorithm that determines the move computer will make at level 4
        void moveAlg4(vector<Square*>& updatedSquares);
};
#endif
