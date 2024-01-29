#include "queen.h"

Queen::Queen(Square* occupiedSquare, Colour colour, char displayChar) : ChessPiece(occupiedSquare, colour, displayChar) {}

void Queen::updateValidMoves(ChessBoard& board) {
    // Obtain Queen's current row and col
    int currRow = this->getSquare().getRow();
    int currCol = this->getSquare().getCol();

    // All the possible directions the queen can go
    int queenMoveOffsets[8][2] {
        {1,1},{-1,1},{1,-1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}
    };

    // Empty the validMoves vectors
    validMoves.resize(0);

    for(int i = 0; i < 8; ++i) {
        int newRow = currRow;
        int newCol = currCol;
        
        while(true) {
            newRow += queenMoveOffsets[i][0];
            newCol += queenMoveOffsets[i][1];

            // Checks if the square positions is actually on the board
            if (newRow >= 1 && newRow <= 8 && newCol >= 1 && newCol <= 8) {
                Square& destinationSquare = board.getSquare(newRow, newCol);
                // Checks if the destination square is empty or occupied by the opposing colour
                if (destinationSquare.isEmpty() || destinationSquare.getPiece().getColour() != getColour()) {
                    validMoves.emplace_back(&destinationSquare);
                    if(!destinationSquare.isEmpty()) break; // if the square has an opposing piece, add it but stop there
                }
                else {
                    break; // Breaks if the position is blocked off with a same colour piece
                }
            }
            else {
                break; // Breaks if the position of the square is outside of the board
            }
        }
    }
}
