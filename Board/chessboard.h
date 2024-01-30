#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include "square.h"
#include <vector>

// Class that creates an instance of a chess board with a double vector of squares
class ChessBoard {
    // private fields
    std::vector<std::vector<Square*>> board;

    // public methods
    public:
        // Ctor
        ChessBoard(); 

        // Dtor
        ~ChessBoard();

        // Returns the square at (row, col) in the board
        Square& getSquare(int row, int col);
};
#endif
