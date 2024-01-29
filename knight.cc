#include "knight.h"

Knight::Knight(Square* occupiedSquare, Colour colour, char displayChar) : ChessPiece(occupiedSquare, colour, displayChar) {}

void Knight::updateValidMoves(ChessBoard& board) {
    // Obtain knights's current row and col
    int currRow = this->getSquare().getRow();
    int currCol = this->getSquare().getCol();

    // All the possible directions the knight can go
    int knightMoveOffsets[8][2] {
        {2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}
    };

    // Empty out the current validMoves vector
    validMoves.resize(0);

    // Checks validty of the potential knight moves
    for (int i = 0; i < 8; ++i) {
        int newRow = currRow + knightMoveOffsets[i][0];
        int newCol = currCol + knightMoveOffsets[i][1];

        if (newRow >= 1 && newRow <= 8 && newCol >= 1 && newCol <= 8) {
            Square& destinationSquare = board.getSquare(newRow, newCol);

            if (destinationSquare.isEmpty() || destinationSquare.getPiece().getColour() != getColour()) {
                validMoves.emplace_back(&destinationSquare);
            }
        }
    }
}
