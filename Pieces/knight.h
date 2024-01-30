#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <vector>
#include "observer.h"
#include "square.h"
#include "chesspiece.h"
#include "enumerations.h"
#include "chessboard.h"

class Knight : public ChessPiece {
    // public methods
    public:
        // Ctor for knight chess piece
        Knight(Square* occupiedSquare, Colour colour, char displayChar);

        // Updates the array of validMoves for the knight(validMoves in ChessPiece class)
        void updateValidMoves(ChessBoard& board) override;
};
#endif
