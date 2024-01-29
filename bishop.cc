#include "bishop.h"

Bishop::Bishop(Square* occupiedSquare, Colour colour, char displayChar) : ChessPiece(occupiedSquare, colour, displayChar) {}

void Bishop::updateValidMoves(ChessBoard& board) {
    // Obtain Bishop's current row and col
    int currRow = this->getSquare().getRow();
    int currCol = this->getSquare().getCol();

    // All the possible directions the bishop can go
    int bishopMoveOffsets[4][2] {
        {1,1},{-1,1},{1,-1},{-1,-1}
    };

    // Clear validMoves vector
    validMoves.resize(0);

    // Checks validty of the potential bishop moves
    for(int i = 0; i < 4; ++i) {
        int newRow = currRow;
        int newCol = currCol;

        // while loop that checks validity of each move in one direction of the bishop
        while(true) {
            newRow += bishopMoveOffsets[i][0];
            newCol += bishopMoveOffsets[i][1];
            
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
