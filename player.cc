#include "player.h"

Player::Player(Colour colour, Square* kingLocation, ChessBoard* board, std::vector<ChessPiece*>& pieces) : 
    colour(colour), kingLocation(kingLocation), board(board), pieces(pieces) {}

Player::~Player() {}

bool Player::isTie() {
    if (pieces.size() == 2) {
        return true;
    }
    return false;
}

bool Player::isStalemate() {
    // Checks if the player is in check. If it is in check cannot be in stalemate
    if (isCheck()) return false;
    
    // Checks if any of their pieces have any valid moves. If yes then cannot be in stalemate
    for (auto piece : pieces) {
        if (piece->getColour() != colour) continue;
        for (auto move : piece->getValidMoves()) {
            // Stalemate does not need to check for castling, as for castling to be legal the king moving one square to the left or right has to be legal which would return false since the game is not in stalemate
            if ((piece->getDisplayChar() == 'k' || piece->getDisplayChar() == 'K') && (move->getCol() == piece->getSquare().getCol() + 2 || move->getCol() == piece->getSquare().getCol() - 2)) continue;
            if (isLegalMove(&piece->getSquare(), move)) {
                return false;
            }
        }
    }
    // Otherwise in stalemate
    return true;
}

bool Player::isLegalMove(Square* osquare, Square* nsquare) {
    ChessPiece* tempCap = nullptr;              // set a temporary piece to be captured
    if (!nsquare->isEmpty()) {
        tempCap = &nsquare->getPiece();         // if the new square has a piece in it set the tempCap too that
        removeCapturedPiece(tempCap);               // and remove the piece from the pieces vector to get an accurate updateValidMoves()
    }
    ChessPiece* piece = &osquare->getPiece();   // get a pointer to the piece being moved
    // move the piece over to the new square and remove the piece from the old square
    piece->setOccupiedSquare(*nsquare);
    nsquare->setPiece(*piece);
    osquare->removePiece();
    piece->moved();

    // if the piece moved was the player's king, updates the kingLocation pointer (temporarily)
    if (piece->getDisplayChar() == 'k' || piece->getDisplayChar() == 'K') {
        kingLocation = nsquare;
    }

    vector<Square*>updatedSquares;

    // notify the pieces to update their valid moves array so that the program can accurately check for check
    notifyPieces(updatedSquares);
    bool underCheck = isCheck();    // check if the potential move would place the player under check

    // reverse the move and put the board back to its original state
    piece->setOccupiedSquare(*osquare);
    osquare->setPiece(*piece);
    nsquare->removePiece();
    piece->reverseMove();

    // If the piece was the king, reverse the king location's back to the original square
    if (piece->getDisplayChar() == 'k' || piece->getDisplayChar() == 'K') {
        kingLocation = osquare;
    }

    // add the captured piece back if it exists
    if (tempCap) {
        pieces.push_back(tempCap);
        nsquare->setPiece(*tempCap);
    }
    notifyPieces(updatedSquares); // notify the pieces again to set validMoves for all pieces to its original state


    if (underCheck) {
        return false; // return false since the move is not valid
    }
    else {
        return true;  // returns true since the move is legal
    }

}

bool Player::isCheck() {
    // Checks if any of the opposing pieces has the king's location as a valid. If it does then in check
    for (auto piece : pieces) {
        if (piece->getColour() != colour && piece->isValidMove(*kingLocation)) return true;
    }
    return false;
}

bool Player::isCheckmate() {
    // Checks if the king is in check
    if(!isCheck()) return false;

    // Checks if the player has any legal moves at all and can therefore avoid check after a move meaning the player is not in checkmate
    for (auto piece : pieces) {
        if (piece->getColour() != colour) continue;
        for (auto move : piece->getValidMoves()) {
            if ((piece->getDisplayChar() == 'k' || piece->getDisplayChar() == 'K') && (move->getCol() == piece->getSquare().getCol() + 2 || move->getCol() == piece->getSquare().getCol() - 2)) continue;
            if (isLegalMove(&piece->getSquare(), move)) {
                return false;
            }
        }
    }
    // If the player has no legal moves and the player is in check then they are in checkmate
    return true;
}

void Player::removeCapturedPiece(ChessPiece* capturedPiece) {
    // Removes the captured piece from the pieces vector but does not deallocate the memory associated with the piece
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if (*it == capturedPiece) {
            pieces.erase(it);
            break; 
        }
    }
}

void Player::notifyPieces(std::vector<Square*>& updatedSquares) {
    // Notifies the pieces when a move has been made so that they can update their valid moves
    for (auto piece : pieces) {
        piece->notify(updatedSquares, *board);
    }
}

bool Player::executeMove(Square* oSquare, Square* nSquare, vector<Square*>& updatedSquares) {
    int ncol = nSquare->getCol();
    int ocol = oSquare->getCol();

    bool isCastling = false;
    CastlingSide side;

    // Checks if when the king passes through the square when right side castling, that square isn't in danger
    if(oSquare == kingLocation && ncol == ocol+2) {
        isCastling = true;
        side = CastlingSide::KingSide;
        if(!castling(CastlingSide::KingSide)) {
            return false;
        }
    }

    // Checks if when the king passes through the square when left side castling, that square isn't in danger
    if(oSquare == kingLocation && ncol == ocol-2) {
        isCastling = true;
        side = CastlingSide::QueensSide;
        if(!castling(CastlingSide::QueensSide)) {
            return false;
        }
    }    

    // Checks if the move is legal and appends the new oSquare and new nSquare to updated squares
    // Is legal move will also actually do the moving of the piece if the move is valid
    if(isLegalMove(oSquare, nSquare)) {
        if (!nSquare->isEmpty()) {
            ChessPiece* removedPiece = &nSquare->getPiece();
            removeCapturedPiece(removedPiece);
            delete removedPiece;
        }

        // moves the piece 
        nSquare->setPiece(oSquare->getPiece());
        nSquare->getPiece().setOccupiedSquare(*nSquare);
        oSquare->removePiece();
        nSquare->getPiece().moved();

        updatedSquares.emplace_back(oSquare);
        updatedSquares.emplace_back(nSquare);


        // if the piece moved was the player's king, updates the kingLocation pointer
        if (nSquare->getPiece().getDisplayChar() == 'k' || nSquare->getPiece().getDisplayChar() == 'K') {
            kingLocation = nSquare;
        }
        notifyPieces(updatedSquares);

        if (isCastling) {           // if castling is being done
            Square* rookSquare = nullptr;     // have to move the rook as well after the king has been moved through isLegalMove
            Square* newRookSquare = nullptr;
            // Get pointers to the squares of the rook and the square it has to move to 
            if (side == CastlingSide::KingSide) {
                rookSquare = &board->getSquare(kingLocation->getRow(), 8);
                newRookSquare = &board->getSquare(kingLocation->getRow(), 6);
            }
            else {
                rookSquare = &board->getSquare(kingLocation->getRow(), 1);
                newRookSquare = &board->getSquare(kingLocation->getRow(), 4);
            }
            // move the rook to the new square and remove it from the original square
            rookSquare->getPiece().setOccupiedSquare(*newRookSquare);
            newRookSquare->setPiece(rookSquare->getPiece());
            rookSquare->removePiece();

            // append the old and new squares for the rook to the list of squares that have to be updated in the display
            updatedSquares.emplace_back(rookSquare);
            updatedSquares.emplace_back(newRookSquare);
            // call moved() on the rook
            newRookSquare->getPiece().moved();
            // notify pieces again since the rook has been moved
            notifyPieces(updatedSquares);
        }

        if ((nSquare->getRow() == 1 || nSquare->getRow() == 8) && (nSquare->getPiece().getDisplayChar() == 'p' || nSquare->getPiece().getDisplayChar() == 'P')) {
            pawnPromotion(nSquare); // call pawn promotion function if a pawn promotion is happening
            nSquare->getPiece().notify(updatedSquares, *board); // update the validMoves vector for the new piece
        }

        return true; // return true to let the game know that a valid move has been performed
    }

    else {
        return false; // move was not legal
    }    
}

bool Player::castling(CastlingSide side) {
    Square* checkSquare = nullptr;
    if (side == CastlingSide::KingSide) {
        checkSquare = &board->getSquare(kingLocation->getRow(), kingLocation->getCol()+1);
    }

    else {
        checkSquare = &board->getSquare(kingLocation->getRow(), kingLocation->getCol()-1);
    }

    for (auto piece : pieces) {
        if (piece->getColour() != colour && piece->isValidMove(*checkSquare)) return false; // check if the square the king passes through is under attack by any opposing pieces
    }
    if (isCheck()) return false; // cannot perform castling if the king is under check
    return true;
}

void Player::pawnPromotion(Square* sq) {
    char newPiece; // set a char for the new piece
    ChessPiece* promotedPiece = nullptr;
    while (true) {
        if(!(cin >> newPiece)) { // if input type is invalid, get input again
            cout << "Invalid promotion piece, try again" << endl;
            continue;
        }
        // if the case of the piece does not match the colour of the player ask for the piece again
        if (!((colour == Colour::White && newPiece >= 'A' && newPiece <= 'Z') || (colour == Colour::Black && newPiece >= 'a' && newPiece <= 'z'))) {
            cout << "Invalid promotion piece, try again" << endl;
            continue;
        }

        // create the new piece 
        if(newPiece == 'Q' || newPiece == 'q') {
            promotedPiece = new Queen(sq, colour, newPiece);
            break;
        }
        else if (newPiece == 'B' || newPiece == 'b') {
            promotedPiece = new Bishop(sq, colour, newPiece);
            break;
        }
        else if (newPiece == 'R' || newPiece == 'r') {
            promotedPiece = new Rook(sq, colour, newPiece); 
            break;            
        }
        else if (newPiece == 'N' || newPiece == 'n') {
            promotedPiece = new Knight(sq, colour, newPiece); 
            break;           
        }
        else {
            cout << "Invalid promotion piece, try again" << endl; // if the char for the piece type did not match any valid piece chars ask for input again
            continue;           
        }
    }

    // delete the pawn from the pieces vector
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if (*it == &sq->getPiece()) {
            delete *it;
            pieces.erase(it);
            break; 
        }
    }
    
    // set the square to hold the new promoted piece
    sq->setPiece(*promotedPiece);
    // add the new promoted piece to the pieces vector
    pieces.emplace_back(promotedPiece);
}
