#include "chesspiece.h"
#include "chessboard.h"
#include "square.h"


ChessPiece::ChessPiece(Square* occupiedSquare, Colour colour, char displayChar) : occupiedSquare(occupiedSquare), colour(colour), displayChar(displayChar) {}

ChessPiece::~ChessPiece() {}

char ChessPiece::getDisplayChar() { return displayChar; }

Colour ChessPiece::getColour() { return colour; }

Square& ChessPiece::getSquare() { return *occupiedSquare; }

bool ChessPiece::isValidMove(Square& location) {
    // Goes through vector of valid moves and if the square provided is in it, returns true or false otherwise
    for(auto n : validMoves) {
        if(n == &location) {
            return true;
        }
    }
    return false;
}

void ChessPiece::setOccupiedSquare(Square& occupiedSquare) {
    // Sets the chess piece's occupied square to the square provided
    this->occupiedSquare = &occupiedSquare;
}

void ChessPiece::notify(std::vector<Square*>& updatedSquares, ChessBoard& board) {
    // Calls updatevalidMoves on the chess piece
    updateValidMoves(board);
}

SubscriptionType ChessPiece::getSubType() { return SubscriptionType::Piece;}

bool ChessPiece::firstMove() { return isFirstMove; }

void ChessPiece::moved() { isFirstMove = false; }

void ChessPiece::reverseMove() { isFirstMove = true;}

vector<Square*> ChessPiece::getValidMoves() {
    return validMoves;
}
