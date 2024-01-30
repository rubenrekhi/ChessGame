#include "graphicdisplay.h"

GraphicDisplay::GraphicDisplay() : xw(800, 800)  {
    
    for (int i = 0; i < 800; i+=200) {
        for (int j = 0; j < 800; j+=100) {
            if (j/100 % 2 == 0) {
                xw.fillRectangle(j,i,100,100,Xwindow::White);
            }
            else {
                xw.fillRectangle(j,i,100,100,Xwindow::Blue);
            }
        }
    }

    for (int i = 100; i < 800; i+=200) {
        for (int j = 0; j < 800; j+=100) {
            if (j/100 % 2 == 0) {
                xw.fillRectangle(j,i,100,100,Xwindow::Blue);
            }
            else {
                xw.fillRectangle(j,i,100,100,Xwindow::White);
            }
        }
    }     
}

void GraphicDisplay::notify(vector<Square*>& updatedSquares, ChessBoard& board) {
    // Goes through the vector of updated squares and updates the display
    for(auto sq : updatedSquares) {
        // Determines the x and y coordinates of the dislay that needs to be updated

        int x = (sq->getCol() - 1) * 100 + 50;
        int y = (8-sq->getRow()) * 100 + 50;

        // If the square that needs to be updated is empty, the display updates to '_' if the square is black and ' ' if the square is white
        if(sq->isEmpty()) {

            if (sq->getColour() == Colour::White) xw.fillRectangle(x-50,y-50,100,100,Xwindow::White);
            else xw.fillRectangle(x-50,y-50,100,100,Xwindow::Blue);
        }
        // If the square has a piece in it the display is updated with the char of the piece
        else {
            xw.drawString(x,y, string(1, sq->getPiece().getDisplayChar()));
        }
    }

}

SubscriptionType GraphicDisplay::getSubType() { return SubscriptionType::Display; }
