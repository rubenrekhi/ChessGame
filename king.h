#ifndef __KING_H__
#define __KING_H__
#include <vector>
#include "observer.h"
#include "square.h"
#include "chesspiece.h"
#include "enumerations.h"
#include "chessboard.h"
#include "rook.h"

class King : public ChessPiece {

    // public methods
    public:
        // Ctor for a king chess piece
        King(Square* occupiedSquare, Colour colour, char displayChar);

        // Updates the array of validMoves for the King (validMoves in ChessPiece class)
        void updateValidMoves(ChessBoard& board) override;
};
#endif
