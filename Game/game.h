#ifndef __GAME_H__
#define __GAME_H__

#include "enumerations.h"

#include "chessboard.h"
#include "square.h"

#include "chesspiece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include "textdisplay.h"
#include "graphicdisplay.h"

#include "player.h"
#include "computer.h"
#include "humanplayer.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Each instance of the game class represents one singular game, and is created and destroyed
//  when games start or end. 
class Game {
    // private fields
    ChessBoard* board;                  // Pointer to the dynamically allocated Board
    Colour currTurn = Colour::White;    // Colour of the player who's turn it is
    vector<ChessPiece*> pieces;         // Vector of pointers to all the ChessPieces currently in the game
    TextDisplay* td;                    // Pointer to the TextDisplay for the current game
    GraphicDisplay* xw;                 // Pointer to the GraphicDisplay for the current game
    Player* blackPlayer;                // Pointer to the black Player
    Player* whitePlayer;                // Pointer to the white Player
    GameState state;                    // Current state of the game

    // Ctor + Dtor
    public :
        // ctor that gets called during setup mode since the players are not defined yet
        Game();

        // ctor that gets called during a normal game creation
        Game(PlayerType whitePlayer, PlayerType blackPlayer, int level1, int level2);

        // dtor
        ~Game();

    // Since a game is never going to get coppied or moved, only deleted or created, move/copy ctor/operators are not needed

    // public methods
    public: 
        // Puts the game into setup mode to initialize the board
        void enterSetupMode();

        // Resigns the game and returns the colour of the winner to update the scoreboard
        Colour resign();

        // Handles moving pieces during the game, and returns false if the move is invalid for any reason, true otherwise
        bool move(); 

        // Returns the state of the game when it is called
        GameState getGameState();

        // Initializes the players for the case when the game is created before it starts (during setup mode), also sets gameState to inGame
        void resetPlayers(PlayerType whitePlayer, PlayerType blackPlayer, int level1, int level2);

        void changeTurn();

    // private methods
    private:
        // Updates the state variable
        void updateGameState();

        // Helper function to check if setup is valid
        bool exitSetupCheck();

        // Calls notify for all the pieces in the game
        void notifyPieces(vector<Square*>& updatedSquares);

        // Calls notify on the displays
        void notifyDisplays(vector<Square*>& updatedSquares);
    
    
    // declaring << operator as a friend
    friend ostream& operator<<(ostream& out, Game& g);
};
#endif
