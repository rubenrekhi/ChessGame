#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <vector>
#include "observer.h"
#include "square.h"
#include "chesspiece.h"
#include "enumerations.h"
#include "chessboard.h"

class Queen : public ChessPiece {
    // public methods
    public:
        // Ctor for queen chess piece
        Queen(Square* occupiedSquare, Colour colour, char displayChar);

        // Updates the array of validMoves for the queen (validMoves in ChessPiece class)
        void updateValidMoves(ChessBoard& board) override;
};
#endif
