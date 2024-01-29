#include "pawn.h"

Pawn::Pawn(Square* occupiedSquare, Colour colour, char displayChar) : ChessPiece(occupiedSquare, colour, displayChar) {}

void Pawn::updateValidMoves(ChessBoard& board) {
    // Obtain pawn's current row and col
    int currRow = this->getSquare().getRow();
    int currCol = this->getSquare().getCol();
    
    // Empty the validMoves vectors
    validMoves.resize(0);

    // VALID MOVES FOR WHITE PAWNS
    if (getColour() == Colour::White) {
        // if the pawn is at the last row (before promotion) it does not have any valid moves
        if (getSquare().getRow() == 8) return;

        // Checks if the square infront of the pawn is a valid move
        
        if(board.getSquare(currRow+1, currCol).isEmpty() == true) {
            validMoves.emplace_back(&board.getSquare(currRow+1, currCol));
        }

        // Checks if the right side diagonal is a valid move 
        if(currCol != 8 && board.getSquare(currRow+1, currCol+1).isBlackPiece() == true) {
            validMoves.emplace_back(&board.getSquare(currRow+1, currCol+1));
        }

        // Checks if the left side diagonal is a valid move
        if(currCol != 1 && board.getSquare(currRow+1, currCol-1).isBlackPiece() == true) {
            validMoves.emplace_back(&board.getSquare(currRow+1, currCol-1));
        }
        // if the pawn is setup at the 7th row, firstmove is true but it doesn't check for double moves
        if (getSquare().getRow() == 7) return;

        // Checks if the second square infront of the pawn is a valid move if the pawn hasn't made their first move
        if(isFirstMove == true && board.getSquare(currRow+2, currCol).isEmpty() == true) {
            validMoves.emplace_back(&board.getSquare(currRow+2, currCol));
        }
    }
    // VALID MOVES FOR BLACK PAWNS
    else {

        // if the pawn is at the last row (before promotion) it does not have any valid moves
        if (getSquare().getRow() == 1) return;

        // Check if the square infront of the pawn is a valid move
        if(board.getSquare(currRow-1, currCol).isEmpty() == true) {
            validMoves.emplace_back(&board.getSquare(currRow-1, currCol));
        }

        // Checks if the right side diagonal is a valid move
        if(currCol != 8 && board.getSquare(currRow-1, currCol+1).isWhitePiece() == true) {
            validMoves.emplace_back(&board.getSquare(currRow-1, currCol+1));
        }

        // Checks if the left side diagonal is a valid move
        if(currCol != 1 && board.getSquare(currRow-1, currCol-1).isWhitePiece() == true) {
            validMoves.emplace_back(&board.getSquare(currRow-1, currCol-1));
        }
        // if the pawn is setup at the 7th row, firstmove is true but it doesn't check for double moves
        if (getSquare().getRow() == 2) return;

        // Check if the second square infront of the pawn is a valid move if the pawn hasn't made their first move
        if(isFirstMove == true && board.getSquare(currRow-2, currCol).isEmpty() == true) {
            validMoves.emplace_back(&board.getSquare(currRow-2, currCol));
        }    
    }
}
