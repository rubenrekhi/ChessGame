#include "square.h"

Square::Square(Colour colour, int row, int col, ChessPiece* piece) : colour(colour), row(row), col(col), piece(piece) {}

int Square::getRow() { return row; }

int Square::getCol() { return col; }

bool Square::isBlackPiece() {
    // If the square doesn't have a piece in it then the square does not have a black piece, returns false
    if(isEmpty() == true) {
        return false;
    }

    // If the colour of the piece in the square is black, then returns true
    if (piece->getColour() == Colour::Black) {
        return true;
    }
    // If the colour of the piece in the square is white, then returns false
    else {
        return false;
    }
}

bool Square::isWhitePiece() {
    // If the square doesn't have a piece in it then the square does not have a white piece, returns false
    if(isEmpty() == true) {
        return false;
    }

    // If the colour of the piece in the square is white, then returns true
    if (piece->getColour() == Colour::White) {
        return true;
    }
    // If the colour of the piece in the square is black, then returns false
    else {
        return false;
    }
}

ChessPiece& Square::getPiece() { return *piece; }

void Square::setPiece(ChessPiece& newPiece) {
    // Sets the piece of the square to the the new piece provided
    piece = &newPiece;
}

bool Square::isEmpty() {
    // If the square has a piece pointer in it then returns false otherwise returns true
    if (piece) {
        return false;
    }
    else {
        return true;
    }
}

void Square::removePiece() {
    // Sets the piece of the square to nullptr representing that there is not piece associated with that square
    piece = nullptr;
}

Colour Square::getColour() { return colour; }
