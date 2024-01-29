#ifndef __HUMANPlAYER_H__
#define __HUMANPLAYER_H__
#include "enumerations.h"
#include "square.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "player.h"
#include <vector>

class HumanPlayer : public Player {
    // public methods
    public:
        // Ctor
        HumanPlayer(Colour colour, Square* kingLocation, ChessBoard* board, std::vector<ChessPiece*>& pieces);

        // Moves the chess piece to the desired square and returns true if the move was successful
        bool move(vector<Square*>& updatedSquares) override; 

        // Returns the player type
        PlayerType getPlayerType() override;


};
#endif
