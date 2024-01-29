#ifndef __ROOK_H__
#define __ROOK_H__
#include <vector>
#include "observer.h"
#include "square.h"
#include "chesspiece.h"
#include "enumerations.h"
#include "chessboard.h"

class Rook : public ChessPiece {
    
    // public methods
    public:
        // Ctor for a rook chess piece
        Rook(Square* occupiedSquare, Colour colour, char displayChar);

        // Updates the array of validMoves for the rook (validMoves in ChessPiece class)
        void updateValidMoves(ChessBoard& board) override;
};
#endif
