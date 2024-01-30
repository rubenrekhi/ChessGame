#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include <vector>
#include "observer.h"
#include "enumerations.h"

using namespace std;

class ChessBoard;
class Square;

class ChessPiece : public Observer {
    // private fields
    Square* occupiedSquare; // Pointer to the square that the chess piece is on
    Colour colour;          // The colour of the chess piece
    char displayChar;       // The character of the chess piece (To indicate what piece it is)

    // protected field
    protected:
        std::vector<Square*> validMoves; // Vector of Square pointers of all the valid moves for a chess piece
        bool isFirstMove = true; // For pawn, king, rook
    
    // public methods
    public:
        // Ctor for a chess piece (Don't have to include validMoves. It will be intialized by default when the subclass piece is created. vector has a default constructor that initalizes it to an empty vector with no elements)
        ChessPiece(Square* occupiedSquare, Colour colour, char displayChar); 

        // Dtor
        virtual ~ChessPiece();

        // Returns the value of displayChar
        char getDisplayChar(); 

        // Returns the value of colour
        Colour getColour();

        // Returns the square that the chesspiece currently occupies
        Square& getSquare();

        // Returns true if the chess piece can move to the provided square and false otherwise
        bool isValidMove(Square& location); 
        
        // Sets the occupiedSquare of the chess piece to the Square provided
        void setOccupiedSquare(Square& occupiedSquare);

        // Pure virtual function that updates the array of validMoves for the chess piece
        virtual void updateValidMoves(ChessBoard& board) = 0;

        // Notifies the ChessPiece to call updateValidMoves since a ChessPiece has been moved on the board        
        void notify(std::vector<Square*>& updatedSquares, ChessBoard& board) override;

        // Returns the subscription type of a chess piece
        SubscriptionType getSubType() override;

        // returns if its the piece's first move, only functional for pawn, king, and rook, dummy values for rest of the pieces
        //  not implemented as exclusive function for the derived classes for polymorphsim 
        bool firstMove();

        // Sets isFirstMove to false
        void moved();

        // sets isFirstMove back to true after a temporary move is reversed
        void reverseMove();

        // Returns the validMoves vector (as a shallow copy so that the iterator is not invalidated)
        vector<Square*> getValidMoves();
};
#endif
