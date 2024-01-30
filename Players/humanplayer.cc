#include "humanplayer.h"
#include <iostream>
using namespace std;

HumanPlayer::HumanPlayer(Colour colour, Square* kingLocation, ChessBoard* board, std::vector<ChessPiece*>& pieces) 
                : Player(colour, kingLocation, board, pieces) {}

PlayerType HumanPlayer::getPlayerType() {
    return PlayerType::Human;
}

bool HumanPlayer::move(vector<Square*>& updatedSquares) {
    char ocolChar;
    char ncolChar;
    
    int orow;
    int ocol;

    int nrow;
    int ncol;

    // Reads in the row and col (col is a letter)
    if(!(cin >> ocolChar >> orow >> ncolChar >> nrow)) {
        cin.clear();
        cin.ignore();
        return false;
    }

    // Converts the column letter into a number
    ocol = ocolChar - 'a' + 1;
    ncol = ncolChar - 'a' + 1;

    // Checks if the column and rows are within the board range
    if(orow > 8 || orow < 1 || nrow > 8 || nrow < 1 || ocol > 8 || ocol < 1 || ncol > 8 || ncol < 1) {
        return false;
    }

    // Finds the square on the board and creates a pointer to it
    Square* oSquare = &board->getSquare(orow, ocol);
    Square* nSquare = &board->getSquare(nrow, ncol);

    // checks if the square is empty and returns false if it is
    if (oSquare->isEmpty()) {
        return false;
    }

    // Checks if the piece colour is the same as the player colour
    if(oSquare->getPiece().getColour() != colour) {
        return false;
    }

    // Checks if the nSquare is a valid move for the piece in oSquare
    if(!oSquare->getPiece().isValidMove(*nSquare)) {
        return false;
    }

    // Executes the move and returns true, if the move was not legal returns false and the move is not executed
    return executeMove(oSquare, nSquare, updatedSquares);
}




