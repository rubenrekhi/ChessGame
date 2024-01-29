#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "observer.h"
#include "square.h"
#include "chesspiece.h"
#include "enumerations.h"
#include "chessboard.h"

class Bishop : public ChessPiece {
    // public methods
    public:
        // Ctor for a bishop chess piece
        Bishop(Square* occupiedSquare, Colour colour, char displayChar);

        // Updates the vector of validMoves for the bishop
        void updateValidMoves(ChessBoard& board) override;
};
#endif
