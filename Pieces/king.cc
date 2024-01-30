#include "king.h"

King::King(Square* occupiedSquare, Colour colour, char displayChar) : ChessPiece(occupiedSquare, colour, displayChar) {}

void King::updateValidMoves(ChessBoard& board) {
    // Obtain king's current row and col
    int currRow = this->getSquare().getRow();
    int currCol = this->getSquare().getCol();

    // All the possible directions the king can go
    int kingMoveOffsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},{0, -1},{0, 1},{1, -1},{1, 0},{1, 1}
    };

    // Empty out the current validMoves vector
    validMoves.resize(0);

    // Checks validty of the potential king moves
    for (int i = 0; i < 8; ++i) {
        int newRow = currRow + kingMoveOffsets[i][0];
        int newCol = currCol + kingMoveOffsets[i][1];

        if (newRow >= 1 && newRow <= 8 && newCol >= 1 && newCol <= 8) {
            Square* destinationSquare = &board.getSquare(newRow, newCol);

            if (destinationSquare->isEmpty() || destinationSquare->getPiece().getColour() != getColour()) {
                validMoves.emplace_back(destinationSquare);
            }
        }
    }
    // if the king is not in its original position or it has been moved, don't check for castling
    if (getSquare().getCol() != 5) return;
    if (getSquare().getRow() != 1 && getColour() == Colour::White) return;
    if (getSquare().getRow() != 8 && getColour() == Colour::Black) return;
    if (!isFirstMove) return;

    // Right side castling

    // Checks if the square 3 pieces to the right of the king is empty
    if(board.getSquare(currRow,currCol+3).isEmpty() == false) {

        char rightRookChar = board.getSquare(currRow,currCol+3).getPiece().getDisplayChar();

        // Checks if the displayCharacter for that square is a rook
        if (rightRookChar == 'r' || rightRookChar == 'R') {
            // Pointer to the rook on that square
            ChessPiece* rightRook = &board.getSquare(currRow,currCol+3).getPiece();
            
            // Checks if king and rook have moved and whether the 2 spaces to the right of the king is empty
            if(isFirstMove == true && rightRook->firstMove() == true && board.getSquare(currRow,currCol+1).isEmpty() == true && board.getSquare(currRow,currCol+2).isEmpty() == true) {
                // Appends the square that is 2 squares to the right of the king into the king's valid moves
                validMoves.emplace_back(&board.getSquare(currRow,currCol+2));
            }
        }
    }

    // Left side castling

    // Checks if the square 4 pieces to the left of the king is empty
    if(board.getSquare(currRow,currCol-4).isEmpty() == false) {
        char leftRookChar = board.getSquare(currRow,currCol-4).getPiece().getDisplayChar();

        // Checks if the displayCharacter for that square is a rook
        if(leftRookChar == 'r' || leftRookChar == 'R') {
            // Pointer to the rook on that square
            ChessPiece* leftRook = &board.getSquare(currRow,currCol-4).getPiece();

            // Checks if king and rook have moved and whether the 3 spaces to the left of the king is empty
            if(isFirstMove == true && leftRook->firstMove() == true && board.getSquare(currRow,currCol-1).isEmpty() == true && board.getSquare(currRow,currCol-2).isEmpty() == true && board.getSquare(currRow,currCol-3).isEmpty() == true) {
                // Appends the square that is 2 squares to the left of the king into the king's valid moves
                validMoves.emplace_back(&board.getSquare(currRow,currCol-2));
            }
        }
    }
}
