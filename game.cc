#include "game.h"


Game::Game(PlayerType whitePlayer, PlayerType blackPlayer, int level1, int level2) : board(new ChessBoard()), currTurn(Colour::White), td(new TextDisplay), xw(new GraphicDisplay), state(GameState::InGame) {


    // initiaize all the pieces that are going to be in the game
    ChessPiece* whiteKing = new King(&board->getSquare(1,5),Colour::White, 'K');
    board->getSquare(1,5).setPiece(*whiteKing);
    pieces.push_back(whiteKing);
    ChessPiece* blackKing = new King(&board->getSquare(8,5),Colour::Black, 'k');
    board->getSquare(8,5).setPiece(*blackKing);
    pieces.push_back(blackKing);

    ChessPiece* whiteQueen = new Queen(&board->getSquare(1,4),Colour::White, 'Q');
    board->getSquare(1,4).setPiece(*whiteQueen);
    pieces.push_back(whiteQueen);    

    ChessPiece* blackQueen = new Queen(&board->getSquare(8,4),Colour::Black, 'q');
    board->getSquare(8,4).setPiece(*blackQueen);
    pieces.push_back(blackQueen); 

    for (int i = 1; i <= 8; i += 7) {
        ChessPiece* whiteRook = new Rook(&board->getSquare(1, i), Colour::White, 'R');
        board->getSquare(1,i).setPiece(*whiteRook);
        pieces.push_back(whiteRook);
    }

    for (int i = 2; i <= 7; i += 5) {
        ChessPiece* whiteKnight = new Knight(&board->getSquare(1, i), Colour::White, 'N');
        board->getSquare(1, i).setPiece(*whiteKnight);
        pieces.push_back(whiteKnight);
    }

    for (int i = 3; i <= 6; i += 3) {
        ChessPiece* whiteBishop = new Bishop(&board->getSquare(1, i), Colour::White, 'B');
        board->getSquare(1, i).setPiece(*whiteBishop);
        pieces.push_back(whiteBishop);
    }

    for (int i = 1; i <= 8; i++) {
        ChessPiece* whitePawn = new Pawn(&board->getSquare(2, i), Colour::White, 'P');
        board->getSquare(2, i).setPiece(*whitePawn);
        pieces.push_back(whitePawn);
    }
    
    for (int i = 1; i <= 8; i += 7) {
        ChessPiece* blackRook = new Rook(&board->getSquare(8, i), Colour::Black, 'r');
        board->getSquare(8, i).setPiece(*blackRook);
        pieces.push_back(blackRook);
    }

    for (int i = 2; i <= 7; i += 5) {
        ChessPiece* blackKnight = new Knight(&board->getSquare(8, i), Colour::Black, 'n');
        board->getSquare(8, i).setPiece(*blackKnight);
        pieces.push_back(blackKnight);
    }

    for (int i = 3; i <= 6; i += 3) {
        ChessPiece* blackBishop = new Bishop(&board->getSquare(8, i), Colour::Black, 'b');
        board->getSquare(8, i).setPiece(*blackBishop);
        pieces.push_back(blackBishop);
    }

    for (int i = 1; i <= 8; i++) {
        ChessPiece* blackPawn = new Pawn(&board->getSquare(7, i), Colour::Black, 'p');  // Pawns are placed on the 7th row for black
        board->getSquare(7, i).setPiece(*blackPawn);
        pieces.push_back(blackPawn);
    }

    // initialize the players in the game
    if (whitePlayer == PlayerType::Human) {
        this->whitePlayer = new HumanPlayer(Colour::White, &board->getSquare(1, 5), board, pieces);
    }   
    else {
        this->whitePlayer = new Computer(Colour::White, &board->getSquare(1, 5), board, pieces, level1);
    } 

    if (blackPlayer == PlayerType::Human) {
        this->blackPlayer = new HumanPlayer(Colour::Black, &board->getSquare(8, 5), board, pieces);
    }   
    else {
        this->blackPlayer = new Computer(Colour::Black, &board->getSquare(8, 5), board, pieces, level2);
    } 

    // notify all the displays and pieces
    vector<Square*> updatedSquares;
    for (int i = 1; i <= 2; i++) {
        for (int k = 1; k <= 8; k++) {
            updatedSquares.push_back(&board->getSquare(i, k));
        }
    }

    for (int i = 7; i <= 8; i++) {
        for (int k = 1; k <= 8; k++) {
            updatedSquares.push_back(&board->getSquare(i, k));
        }
    }

    notifyDisplays(updatedSquares);
    notifyPieces(updatedSquares);
    // Prints out the board
    cout << *this;
}

Game::Game() : board(new ChessBoard()), currTurn(Colour::White), td(new TextDisplay()), xw(new GraphicDisplay()), state(GameState::Undefined) {}

Game::~Game() {
    // Deallocates the memory of the text display, the Xwindow, both players, the board and all the pieces
    delete td;
    delete xw;
    delete blackPlayer;
    delete whitePlayer;
    delete board;
    for (auto piece : pieces) {
        delete piece;
    }
    pieces.clear();
}


Colour Game::resign() {
    // If black resigned then return the white player's colour to update the scoreboard
    if(currTurn == Colour::Black) {
        return Colour::White;
    }
    // If white resigned then return the black player's colour to update the scoreboard
    else {
        return Colour::Black;
    }
}

bool Game::move() {
    bool retval;
    vector<Square*>updatedSquares;
    // call the move function associated with the player who's turn it is
    if (currTurn == Colour::White) {
        retval = whitePlayer->move(updatedSquares);
    }

    else {
        retval = blackPlayer->move(updatedSquares);
    }
    if (retval) {
        changeTurn();
        // update the state and notify the display of any changes made
        updateGameState();
        notifyDisplays(updatedSquares);
    }

    return retval;
}

GameState Game::getGameState() {return state;}

void Game::resetPlayers(PlayerType whitePlayer, PlayerType blackPlayer, int level1, int level2) {
    
    // find the location of the kings after setup mode
    Square* whiteKingLocation = nullptr;
    Square* blackKingLocation = nullptr;
    for (auto piece : pieces) {
        if (piece->getDisplayChar() == 'K') {
            whiteKingLocation = &(piece->getSquare());
        }
        if (piece->getDisplayChar() == 'k') {
            blackKingLocation = &(piece->getSquare());
        }
    }

    // initialize the players
    if (whitePlayer == PlayerType::Human) {
        this->whitePlayer = new HumanPlayer(Colour::White, whiteKingLocation, board, pieces);
    }   
    else {
        this->whitePlayer = new Computer(Colour::White, whiteKingLocation, board, pieces, level1);
    } 

    if (blackPlayer == PlayerType::Human) {
        this->blackPlayer = new HumanPlayer(Colour::Black, blackKingLocation, board, pieces);
    }   
    else {
        this->blackPlayer = new Computer(Colour::Black, blackKingLocation, board, pieces, level2);
    }

    // change the state to InGame
    state = GameState::InGame; 

    cout << *this;
}

void Game::updateGameState() {
    if (whitePlayer->isCheckmate()) {
        state = GameState::CheckmateBlack;
    }

    else if (blackPlayer->isCheckmate()) {
        state = GameState::CheckmateWhite;
    }

    else if (currTurn == Colour::White && whitePlayer->isStalemate()) {
        state = GameState::Tie;
    }

    else if (currTurn == Colour::Black && blackPlayer->isStalemate()) {
        state = GameState::Tie;
    }

    else if (whitePlayer->isTie()) {
        state = GameState::Tie;
    }

    else {
        state = GameState::InGame;
    }
}

void Game::notifyPieces(vector<Square*>& updatedSquares) {
    // Goes through the vector of all the pieces and notifies each one
    for (auto piece : pieces) {
        piece->notify(updatedSquares, *board);
    }
}

void Game::notifyDisplays(vector<Square*>& updatedSquares) {
    // Notifies the text display to update with a vector of squares that need to be updated
    td->notify(updatedSquares, *board);
    xw->notify(updatedSquares, *board);
}

ostream& operator<<(ostream& out, Game& g) {
    // print the TextDisplay 
    return out << *(g.td);
}

void Game::enterSetupMode() {
    string command;
    while (cin >> command) {
        if (command == "+") {
            // get the type of piece to add
            char pieceType;
            if (!(cin >> pieceType)) {
                cout << "Invalid input, try again" << endl;
                continue;
            }
            // get the position to add the piece to 
            char colChar;
            int row;
            int col;
            if (!(cin >> colChar >> row)) {
                cout << "Invalid input, try again" << endl;
                cin.clear();
                cin.ignore();
                continue;
            }
            col = colChar - 'a' + 1;

            // validate that the position is inside the board
            if (row > 8 || row < 1 || col > 8 || row < 1) {
                cout << "Invalid input, try again" << endl;
                continue;
            }


            ChessPiece* addPiece = nullptr;
            Square* addSquare = &board->getSquare(row, col);

            // create the piece and add it to the board
            if (pieceType == 'K') {
                addPiece = new King(addSquare, Colour::White, 'K');
            }
            else if (pieceType == 'P') {
                addPiece = new Pawn(addSquare, Colour::White, 'P');
            }
            else if (pieceType == 'Q') {
                addPiece = new Queen(addSquare, Colour::White, 'Q');
            }
            else if (pieceType == 'N') {
                addPiece = new Knight(addSquare, Colour::White, 'N');
            }
            else if (pieceType == 'R') {
                addPiece = new Rook(addSquare, Colour::White, 'R');
            }
            else if (pieceType == 'B') {
                addPiece = new Bishop(addSquare, Colour::White, 'B');
            }
            else if (pieceType == 'k') {
                addPiece = new King(addSquare, Colour::Black, 'k');
            }
            else if (pieceType == 'p') {
                addPiece = new Pawn(addSquare, Colour::Black, 'p');
            }
            else if (pieceType == 'q') {
                addPiece = new Queen(addSquare, Colour::Black, 'q');
            }
            else if (pieceType == 'n') {
                addPiece = new Knight(addSquare, Colour::Black, 'n');
            }
            else if (pieceType == 'r') {
                addPiece = new Rook(addSquare, Colour::Black, 'r');
            }
            else if (pieceType == 'b') {
                addPiece = new Bishop(addSquare, Colour::Black, 'b');
            }
            else {
                cout << "Invalid input, try again" << endl;
                continue;
            }

            // if the square is occupied remove the piece in it currently
            if (!addSquare->isEmpty()) {
                for (auto it = pieces.begin(); it != pieces.end(); ++it) {
                    if (*it == &addSquare->getPiece()) {
                        delete *it;
                        pieces.erase(it);
                        break; 
                    }
                }
            }
            // add the new piece to the square and to the pieces vector
            addSquare->setPiece(*addPiece);
            pieces.push_back(addPiece);
            // update the display
            vector<Square*>updatedSquares;
            updatedSquares.push_back(addSquare);
            notifyDisplays(updatedSquares);

            cout << *this;
        }

        else if (command == "-") {
            char colChar;
            int row;
            int col;
            if (!(cin >> colChar >> row)) {
                cout << "Invalid input, try again" << endl;
                cin.clear();
                cin.ignore();
                continue;
            }
            col = colChar - 'a' + 1;
            if (row > 8 || row < 1 || col > 8 || row < 1) {
                cout << "Invalid input, try again" << endl;
                continue;
            }
            // if the square is not empty, remove the piece at the square
            if (!board->getSquare(row, col).isEmpty()) {
                ChessPiece* removePiece = &board->getSquare(row, col).getPiece();
                board->getSquare(row, col).removePiece();
                for (auto it = pieces.begin(); it != pieces.end(); ++it) {
                    if (*it == removePiece) {
                        delete *it;
                        pieces.erase(it);
                        break; 
                    }
                }
                vector<Square*>updatedSquares;
                updatedSquares.push_back(&board->getSquare(row,col));
                notifyDisplays(updatedSquares);
                cout << *this;
            }
            else {
                cout << *this;
            }
        }

        else if (command == "=") {
            string colour;
            if (!(cin >> colour)) {
                cout << "Invalid input, try again" << endl;
            }
            if (colour == "White" || colour == "white") {
                currTurn = Colour::White;
            }
            else if (colour == "Black" || colour == "black") {
                currTurn = Colour::Black;
            }
            else {
                cout << "Invalid input, try again" << endl;
                continue;
            }
        }

        else if (command == "done") {
            vector<Square*>updatedSquares;
            notifyPieces(updatedSquares);

            // Checks if the board created in setup mode is valid
            if (!exitSetupCheck()) {
                cout << "Your board is invalid, please continue editing and try again" << endl;
                cout << *this;
                continue;
            }
            else {
                cout << "Setup successful, please start a game" << endl;
                return;
            }
        }

        else {
            cout << "Invalid input, try again" << endl;
            continue;
        }
    }
}

bool Game::exitSetupCheck() {
    Square* whiteKingLocation = nullptr;
    Square* blackKingLocation = nullptr;

    // find the location of the kings
    for (auto piece : pieces) {
        if (piece->getDisplayChar() == 'K') {
            if(whiteKingLocation) return false; // if a whiteking has already been found and there is a second one, return false
            whiteKingLocation = &piece->getSquare();
        }
        else if (piece->getDisplayChar() == 'k') {
            if(blackKingLocation) return false; // if a blackking has already been found and there is a second one, return false
            blackKingLocation = &piece->getSquare();
        }
        else if ((piece->getDisplayChar() == 'P' || piece->getDisplayChar() == 'p') && (piece->getSquare().getRow() == 8 || piece->getSquare().getRow() == 1)) {
            return false;   // if there are any pawns on the first or last row, return false
        }
    }

    if (!(whiteKingLocation && blackKingLocation)) return false; // if either a black of white king was not found, return false

    // setup temporary players to check if either of the kings are under check
    whitePlayer = new HumanPlayer(Colour::White, whiteKingLocation, board, pieces);
    blackPlayer = new HumanPlayer(Colour::Black, blackKingLocation, board, pieces);

    // delete the players and then return true or false based on whether the kings were under check
    if (whitePlayer->isCheck() || blackPlayer->isCheck()) {
        delete whitePlayer;
        whitePlayer = nullptr;
        delete blackPlayer;
        blackPlayer = nullptr;
        return false;
    }
    
    delete whitePlayer;
    whitePlayer = nullptr;
    delete blackPlayer;
    blackPlayer = nullptr;
    return true;
}

void Game::changeTurn() {
    // If the current turn is white, change it to black and if the current turn is black, change it to white
    if (currTurn == Colour::White) {
        currTurn = Colour::Black;
    }
    else {
        currTurn = Colour::White;
    }
}
