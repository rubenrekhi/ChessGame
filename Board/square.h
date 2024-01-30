#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "chesspiece.h"
#include "enumerations.h"

// Class that creates instances of squares for each position on a chess board
class Square {
    // private fields
    Colour colour;
    int row;
    int col;
    ChessPiece* piece;

    // public methods
    public:
        // Ctor to create a square
        Square(Colour colour, int row, int col, ChessPiece* piece = nullptr);

        // Returns the row of the square
        int getRow();

        // Returns the column of the square
        int getCol();

        // Returns true if colour = Black and false otherwise
        bool isBlackPiece();

        // Returns true if colour = White and false otherwise
        bool isWhitePiece();

        // Returns the chess piece on the square
        ChessPiece& getPiece();

        // Sets a chess piece to the square
        void setPiece(ChessPiece& newPiece);

        // Returns true if there is no piece in the square and false otherwise
        bool isEmpty();

        // Sets the ChessPiece pointer to null pointer
        void removePiece();

        // Returns the colour of the square
        Colour getColour();
};
#endif
