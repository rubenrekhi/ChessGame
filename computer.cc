#include "computer.h"

Computer::Computer(Colour colour, Square* kingLocation, ChessBoard* board, std::vector<ChessPiece*>& pieces, int level) : 
    Player(colour, kingLocation, board, pieces), level(level) {}


PlayerType Computer::getPlayerType() { return PlayerType::Computer;}

bool Computer::move(vector<Square*>& updatedSquares) {
    // call the move algorithm for the level of the computer
    if (level == 1) moveAlg1(updatedSquares);
    else if (level == 2) moveAlg2(updatedSquares);
    else if (level == 3) moveAlg3(updatedSquares);
    else moveAlg4(updatedSquares);
    return true;
}


void Computer::moveAlg1(vector<Square*>& updatedSquares) {
    while(true) {

        int randomNumber = rand() % pieces.size();
        auto piece = pieces[randomNumber];
        if (piece->getColour() != colour) continue;
        for (auto sq : piece->getValidMoves()) {
            if (executeMove(&piece->getSquare(), sq, updatedSquares)) {
                return; // return after the first legal + valid move is found and executed
            }
        }
    }
}

void Computer::moveAlg2(vector<Square*>& updatedSquares) {
    for (auto piece : pieces) {
        if (piece->getColour() != colour) continue;
        for (auto sq : piece->getValidMoves()) {
            if (sq->isEmpty()) continue;    // only check valid move squares that are not empty, which means they have an enemy piece inside them
            if (executeMove(&piece->getSquare(), sq, updatedSquares)) {     // execute moves that prefer capuring pieces
                return;
            }
        }
    }

    // if no move is found, try to find a way to check the opponent
    // get a pointer to the opponent's king's location

    Square* oppKingLocation;
    for (auto piece : pieces) {
        if (piece->getColour() != colour && (piece->getDisplayChar() == 'k' || piece->getDisplayChar() == 'K')) {
            oppKingLocation = &piece->getSquare();
            break;
        }
    }

    for (auto piece : pieces) {
        if (piece->getColour() != colour) continue;
        for (auto sq : piece->getValidMoves()) {
            if (!sq->isEmpty()) continue;   // Don't check squares with enemy pieces as those have already been checked
           
            Square* osquare = &piece->getSquare(); // store a pointer to the original square of the piece
            piece->setOccupiedSquare(*sq);         // change the piece's occupied square to the potential move to check if it can check the king
            osquare->removePiece();
            vector<Square*>tempEmpty; 
            piece->notify(tempEmpty, *board);      // update the piece's valid moves based on if it were at the new square
            
            bool potentialCheck = false;

            for (auto findSq : piece->getValidMoves()) { // checks what the valid moves WOULD be if you moved the piece 
                if (findSq == oppKingLocation) {    // check if the king would be part of that, so there is a potential check
                    potentialCheck = true;
                    break;
                }
            }
            // set the piece and squares to their original state (reverse the temporary move)
            piece->setOccupiedSquare(*osquare);
            osquare->setPiece(*piece);
            sq->removePiece();
            piece->notify(tempEmpty, *board); // set the valid moves for that piece to its original state as well

            // if we have a potential check (for moving piece to sq) and the move is legal, it is executed and the function returns
            if (potentialCheck && executeMove(osquare, sq, updatedSquares))  {
                return;
            }
        }
    }

    // if there are no valid prefferred moves, simply revert to alg 1 (random valid moves)
    moveAlg1(updatedSquares);
}

void Computer::moveAlg3(vector<Square*>& updatedSquares) {
    bool canCapture = false;
    ChessPiece* captureRisk = nullptr; // the piece at risk of being captured
    for (auto piece : pieces) {
        if (piece->getColour() != colour) continue;
        for (auto oppPiece : pieces) {
            if (oppPiece->getColour() == colour) continue;
            if (oppPiece->isValidMove(piece->getSquare())) {    // if an opponent piece is threatning the computer's piece
                canCapture = true;
                captureRisk = piece;
                break;
            }
        }
    }

    // if no piece is under danger, revert to movealg2 (try to check or take a piece)
    if (!canCapture) moveAlg2(updatedSquares);
    if (!captureRisk) moveAlg2(updatedSquares);
    // make a copy of the valid moves of the piece at risk
    vector<Square*>potentialEscapes = captureRisk->getValidMoves();

    // finds all the potential escapes that take the piece out of danger
    for (auto potentialEscape = potentialEscapes.begin(); potentialEscape != potentialEscapes.end();) {
        bool erased = false;
        for (auto oppPiece : pieces) {
            if (oppPiece->getColour() == colour) continue;

            // to check if a potential move is safe, get rid of enemy pieces at that square so that they include it in 
            //  their valid moves, and make the piece at risk transparent so enemy pieces can updateValidMoves through it
            ChessPiece* temp = &(*potentialEscape)->getPiece();
            Square* captureRiskSq = &captureRisk->getSquare();
            captureRiskSq->removePiece();
            (*potentialEscape)->setPiece(*captureRisk);
            oppPiece->notify(potentialEscapes, *board);

            if (oppPiece->isValidMove(*(*potentialEscape))) {   // if the potential move is threatened, remove it from the vector
                // reverse the temporary changes
                if (temp) (*potentialEscape)->setPiece(*temp);
                else (*potentialEscape)->removePiece();
                captureRiskSq->setPiece(*captureRisk);
                oppPiece->notify(potentialEscapes, *board);
                
                // remove the pointer through erasing the iterator
                potentialEscape = potentialEscapes.erase(potentialEscape);
                erased = true;
                break;
            }

            // reverse the move if the if statement does not execute
            if (temp) (*potentialEscape)->setPiece(*temp);
            else (*potentialEscape)->removePiece();
            captureRiskSq->setPiece(*captureRisk);
            oppPiece->notify(potentialEscapes, *board); 
        }
        if (!erased) ++potentialEscape;
    }

    // if any of the potential escapes can take another piece, give that priority
    for (auto potentialEscape = potentialEscapes.begin(); potentialEscape != potentialEscapes.end();) {
        if((*potentialEscape)->isEmpty()) {
            ++potentialEscape;
            continue;
        }
        if (executeMove(&captureRisk->getSquare(), *potentialEscape, updatedSquares)) return;
        // if the move is not legal erase it from the vector
        potentialEscape = potentialEscapes.erase(potentialEscape);
    }

    // go through the rest of the potential escapes to see if any of them are legal
    for (auto potentialEscape : potentialEscapes) {
        if (executeMove(&captureRisk->getSquare(), potentialEscape, updatedSquares)) return;
    }

    // if the funtion gets to this point, the piece is unsavable, so we try to take another piece to get some value
    for (auto tradePiece : captureRisk->getValidMoves()) {
        if (tradePiece->isEmpty()) continue;
        if (executeMove(&captureRisk->getSquare(), tradePiece, updatedSquares)) return;
    }

    // if we cannot save the piece, and we cannot get any value out of it, we simply try to move another piece
    //  that tries to take a piece or check the opponent, and makes a random move if that is not possible
    moveAlg2(updatedSquares);
}


void Computer::moveAlg4(vector<Square*>& updatedSquares) {
    moveAlg3(updatedSquares);
}
