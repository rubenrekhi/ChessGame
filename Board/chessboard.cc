#include "chessboard.h"

ChessBoard::ChessBoard() {
    // Create 8 square pointer vectors of size 8
    board.resize(8, std::vector<Square*>(8));

    // Allocating memory for each square on the chessboard
    for(int i = 0; i < 8; i+=2) {
        for(int j = 0; j < 8; ++j) {
            if (j % 2 == 0) {
                board[i][j] = new Square(Colour::Black, i+1, j+1, nullptr);
            }
            else {
                board[i][j] = new Square(Colour::White, i+1, j+1, nullptr);
            }
        }
    }

    for(int i = 1; i < 8; i+=2) {
        for (int j = 0; j < 8; ++j) {
            if (j % 2 == 0) {
                board[i][j] = new Square(Colour::White, i+1, j+1, nullptr);
            }
            else {
                board[i][j] = new Square(Colour::Black, i+1, j+1, nullptr);
            }            
        }
    }
}

ChessBoard::~ChessBoard() {
    // Deallocating every square in the chessboard
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }

    board.clear();
}

Square& ChessBoard::getSquare(int row, int col) {
    // Returns the square at the row and col provided
    return *board[row-1][col-1];
}
