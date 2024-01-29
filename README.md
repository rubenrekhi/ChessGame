# Chess Game Project
## Description
This Chess Game Project is an interactive, board-based game developed using principles of object-oriented programming. Designed to showcase modularity, reusability, and scalability, the game features a robust architecture encapsulating the functionality into discrete classes. The project demonstrates intricate game mechanics and player interactions, with a focus on the effective application of object-oriented design.

## Table of Contents
Installation
Usage
Credits
License

## Installation
### Prerequisites
* g++-11 compiler with C++20 support
* XQuartz for graphical display (for macOS users)
### Steps
1. Clone the repository from GitHub to your local machine.
2. Ensure you have g++-11 installed and set as the default compiler.
3. Install XQuartz to enable graphical display, following the official installation guide.
### Running on a Remote Server
#### If you're using a university or any remote server:

1. Transfer the project files to your remote server.
2. Follow the installation steps on the server.
3. Use SSH with X11 forwarding enabled to connect to the server and run the game.
## Usage
### To play the chess game:

1. Open a terminal in the project directory.
2. Run the make command to compile the project: make
3. Execute the game: ./chess
4. The game interface should now be up and running. Follow on-screen instructions to play the game.

The game is played in the terminal, and the graphic display is only for visuals; it is not interactive.

### Game Commands:
NOTE: Capital letters (ex. 'K', 'Q') represent white pieces, and underscore letters represent black pieces. All pieces are represented by the first letter in their name, except the Knight which is a 'N' or 'n' depending on the colour. 
* -- game 'white-player'  'black-player' -- starts a new game. The parameters 'white-player' and 'black-player' can be either 'human' or 'computer[1-4]'. Computer levels are of increasing difficulty.
* -- resign -- concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.
* A move consists of the command -- move 'sq1 'sq2' --, with the starting and ending coordinates of the piece to be moved. For example: -- move e2 e4 --. Castling would specified by the two-square move for the king: -- move e1 g1 -- or -- move e1 c1 -- for white.  Pawn promotion would additionally specify the piece type to which the pawn is promoted: -- move e7 e8 Q --. In the case of a computer player, the command -- move -- (without arguments) makes the computer player make amove.
* -- setup -- enters setup mode, within which you can set up your own initial board configurations.  This can only be donewhen a game is not currently running. Within setup mode, the following language is used: 
** -- + K e1 -- places the pieceK (i.e., white king in this case) on the square e1. If a piece is already on that square, it is replaced. 
** -- - e1 -- removes the piece from the square e1. 
** -- = 'colour' -- makes it colour’s turn to go next.
** -- done -- leaves setup mode.
** Upon completion of setup mode, you must verify that the board contains exactly one white king and exactly one blackking; that no pawns are on the first or last row of the board; and that neither king is in check.  The user cannot leavesetup mode until these conditions are satisfied



## Credits
This project was developed by Ruben Rekhi and Tharsihan Ariyanayagam. Special thanks to all those who have provided feedback and suggestions.


