#include "game.h"
#include "scoreboard.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    string command;
    PlayerType playerType1;
    PlayerType playerType2;
    int level1 = 0;
    int level2 = 0;
    Scoreboard sb;
    Game* g = nullptr;
    srand(static_cast<unsigned int>(time(0)));

    while (cin >> command) {
        if (command == "Game" || command == "game") {
            // Figure out what type the white player is
            cin >> command;
            if(command == "human" || command == "Human") {
                playerType1 = PlayerType::Human;
            }
            else if (command == "computer" || command == "Computer") {
                playerType1 = PlayerType::Computer;
                if (!(cin >> level1)) { // confirm that the level is an int
                    cout << "Invalid command, try again" << endl;
                    cout << "Error code: computer level not inputted" << endl;
                    cin.clear();
                    cin.ignore();
                    continue;
                }
                if (level1 < 1 || level1 > 4) { // Invalid level
                    cout << "Invalid command, try again" << endl;
                    cout << "Error code: computer level outside valid range" << endl;
                    continue;
                }
            }
            else {
                cout << "Invalid command, try again" << endl;
                cout << "Error: player types not valid" << endl;
                continue;
            }
            // Figure out what type the black player is
            cin >> command;
            if(command == "human" || command == "Human") {
                playerType2 = PlayerType::Human;
            }
            else if (command == "computer" || command == "Computer") {
                playerType2 = PlayerType::Computer;
                if (!(cin >> level2)) { 
                    cout << "Invalid command, try again" << endl;
                    cout << "Error code: computer level not inputted" << endl;
                    cin.clear();
                    cin.ignore();
                    continue;
                }
                if (level2 < 1 || level2 > 4) {
                    cout << "Invalid command, try again" << endl;
                    cout << "Error code: computer level outside valid range" << endl;

                    continue;
                }
            }
            else {
                cout << "Invalid command, try again" << endl;
                cout << "Error: player types not valid" << endl;
                continue;
            }
            // set up the game

            // reset the players if the game has been initialized 
            if(g) {
                g->resetPlayers(playerType1, playerType2, level1, level2);
            }
            // create a new game with the players
            else {
                g = new Game{playerType1, playerType2, level1, level2};
            }

        } 
        
        else if (command == "resign" || command == "Resign") {
            if (!g || g->getGameState() != GameState::InGame) { // If there is no game in progress
                cout << "Invalid command, try again" << endl;
                cout << "Error code: no game in progress" << endl;
                continue;
            }
            Colour winner = g->resign(); // resign the game and get the winner
            sb.addResult(winner, 1); // update scoreboard
            if (winner == Colour::White) {
                cout << "Black resigns, White wins!" << endl;
            }
            else {
                cout << "White resigns, Black wins!" << endl;
            }
            delete g; // delete the game since it is over
            g = nullptr;
        }

        else if (command == "move" || command == "Move") {
            if (!g || g->getGameState() != GameState::InGame) {
                cout << "Invalid Command, try again" << endl;
                cout << "Error code: no game in progress" << endl;
                continue;
            }

            if (!g->move()) { // if Game::move() returns false, the move was invalid
                cout << "Invalid Command, try again" << endl;
                cout << "Error code: move was invalid" << endl;
                continue;
            }
            cout << *g; // print out the game board

            // check the status of the game (if a valid move was performed)
            if (g->getGameState() == GameState::InGame) {
                continue;
            }
            else if (g->getGameState() == GameState::CheckmateWhite) {
                cout << "White wins by checkmate!" << endl;
                sb.addResult(Colour::White, 1);
                delete g;
                g = nullptr;
            }
            else if (g->getGameState() == GameState::CheckmateBlack) {
                cout << "Black wins by checkmate!" << endl;
                sb.addResult(Colour::Black, 1);
                delete g;
                g = nullptr;
            }
            else {
                cout << "Stalemate!" << endl;
                sb.addResult(Colour::Black, 0.5);
                sb.addResult(Colour::White, 0.5);
                delete g;
                g = nullptr;
            }

        }

        else if (command == "setup" || command == "Setup") {
            if (g && g->getGameState() != GameState::Undefined) { // If a game is already in progress
                cout << "Invalid command, try again" << endl;
                cout << "Error code: game is already in progress" << endl;
                continue;
            }
            if (!g) g = new Game(); // create Game object
            g->enterSetupMode(); // call Game::enterSetupMode()
            cout << *g; // print out the game board
        }
        else {
            cout << "Invalid command, try again" << endl;
            cout << "Error code: '" << command << "' is not a valid command" << endl;
            continue; 
        }
    }

    cout << sb; // print the scoreboard once EOF is reached (or there is no more input)
}
