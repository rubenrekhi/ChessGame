#ifndef __PAWN_H__
#define __PAWN_H__
#include <vector>
#include "observer.h"
#include "square.h"
#include "chesspiece.h"
#include "enumerations.h"
#include "chessboard.h"

class Pawn : public ChessPiece {

    // public methods
    public:
        // Ctor for a pawn chess piece
        Pawn(Square* occupiedSquare, Colour colour, char displayChar);

        // Updates the array of validMoves for the pawn (validMoves in ChessPiece class)
        void updateValidMoves(ChessBoard& board) override;
};
#endif
