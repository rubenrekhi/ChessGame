#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "enumerations.h"
#include "square.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#include <vector>
#include <iostream>
using namespace std;

// Each instance of player would dictate the player in the specific game they exist inside of 
class Player {
    // protected fields
    protected:
        Colour colour;                   // The colour of the player
        Square* kingLocation;             // The location of the player's king
        ChessBoard* board;               // The chessboard of the current game
        vector<ChessPiece*>& pieces; // A vector of all the pieces on the board

    // public methods
    public:
        // Ctor 
        Player(Colour colour, Square* kingLocation, ChessBoard* board, vector<ChessPiece*>& pieces);
        
        // Dtor
        virtual ~Player();

        // Pure virtual function that will return where the player is a human or computer
        virtual PlayerType getPlayerType() = 0;

        // Pure virtual function that moves the chess piece to the desired square 
        virtual bool move(vector<Square*>& updatedSquares) = 0;

        // Returns true if the player is in checkmate and false otherwise  
        bool isCheckmate();
        
        // Returns true if player is in stalemate by checking if the move function returns false for every piece otherwise returns false
        bool isStalemate();

        // Returns true if the game is a tie (There are only 2 kings left, so a checkmate is impossible)
        bool isTie();

        // Returns true if the king's square is inside any of the validMove arrays in the opposite teams pieces (use the pieces array for this)
        bool isCheck();
    
    // protected methods
    protected:
        // Removes the chess piece that has been captured from the board (does not delete the piece from the pieces vector)
        void removeCapturedPiece(ChessPiece* capturedPiece);

        // Notify all the pieces that a piece has been moved
        void notifyPieces(std::vector<Square*>& updatedSquares);

        // Makes a temporary move then reverses it to check whether a given move will put the player's king under check
        bool isLegalMove(Square* osquare, Square* nsquare);

        // Responsible for executing move given the original square and new square, returns false if the move is not valid, adds squares that need to be redisplayed to updatedSquares vector
        bool executeMove(Square* oSquare, Square* nSquare, vector<Square*>& updatedSquares);

        // Helper function that checks if castling is allowed (specifically if the king is under check or the square its travelling through is under attack)
        bool castling(CastlingSide side);

        // Helper function that promotes a pawn to whatever piece desired (Removes pawn, adds the new promoted piece)
        void pawnPromotion(Square* sq);
};
#endif
