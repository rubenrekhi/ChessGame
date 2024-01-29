#include "textdisplay.h"
#include "chessboard.h"
#include "square.h"

TextDisplay::TextDisplay() {
    // Resizes the vector to a size of 8 char vectors that are also of size 8
    theDisplay.resize(8, vector<char>(8));
    
    // Sets the display of the chess board to '_' if a black square and ' ' if a white square for rows (1,3,5,7)
    for (int i = 0; i < 8; i+=2) {
        for (int j = 0; j < 8; ++j) {
            if(j % 2 == 0) {
                theDisplay[i][j] = ' ';
            }
            else {
                theDisplay[i][j] = '_';
            }
        }
    }

    // Sets the display of the chess board to '_' if a black square and ' ' if a white square for rows (2,4,6,8)
    for (int i = 1; i < 8; i+=2) {
        for (int j = 0; j < 8; ++j) {
            if(j % 2 == 0) {
                theDisplay[i][j] = '_';
            }
            else {
                theDisplay[i][j] = ' ';
            }
        }
    }    
}

TextDisplay::~TextDisplay() {
    theDisplay.clear();
}

void TextDisplay::notify(vector<Square*>& updatedSquares, ChessBoard& board) {
    // Goes through the vector of updated squares and updates the display
    for(auto sq : updatedSquares) {
        // Determines the row and col of the dislay that needs to be updated
        int row = 8 - sq->getRow();
        int col = sq->getCol() - 1;

        // If the square that needs to be updated is empty, the display updates to '_' if the square is black and ' ' if the square is white
        if(sq->isEmpty()) {
            if(sq->getColour() == Colour::Black) {
                theDisplay[row][col] = '_';
            }
            else {
                theDisplay[row][col] = ' ';
            }
        }
        // If the square has a piece in it the display is updated with the char of the piece
        else {
            theDisplay[row][col] = sq->getPiece().getDisplayChar();
        }
    }
}

SubscriptionType TextDisplay::getSubType() {
    // Returns that the subscription type is Display
    return SubscriptionType::Display;
}

ostream& operator<<(ostream &out, const TextDisplay &td) {
    // Goes through the entire text display and outputs the character in each spot
    for (int i = 0; i < 8; ++i) {
        
        cout << 8-i << "    ";
        for (int j = 0; j < 8; ++j) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    cout << endl << "     abcdefgh" << endl;
    return out;
}
