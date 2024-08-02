#include "chess.h"

/*
What I've learned so far:
Can use .at(#) or [#] on strings to figure out what's at #
When using .at(#) or [#] on a string and I am expecting an integer (int var = string.at(#))
it will return the ASCII value of that integer (interesting)
Plan things out, split up functions


To run in console: g++ .\chess.cpp .\chessMoves.cpp .\chessFunctions.cpp
Then .\a.exe
*/

/*
I declare most variables in the first game loop, since if a new game is started
many of the variables need to be reset and resetting them this way is easier than doing them 
all individually.
*/
int main(){
    int gameStart = 0;

    cout << "The pieces are abbreviated as the following: " << endl << "Pawn: p" << endl << 
    "Rook: r" << endl << "Knight/Horse: h" << endl << "Bishop: b" << endl << "Queen: q" << endl <<
    "King: k" << endl << "The white pieces are capital letters and the black pieces are lower case." << endl;
    cout << "To castle enter your King's location as the starting square and your Rook's location as the ending square." << endl;
    cout << "To begin type 1." << endl;

    cin >> gameStart;

    do {
        /*
        could also do a multidimensional array [8][8]
        it would mainly just change the way the board is created (double loop)
        and in checking if valid would check row and column
        */
        char board[64], pieceMoved;
        int initialPlacement = 0, endPlacement = 0, kingPosition = 0, inCheck = 0;
        int userLastMove = 0; //this is straight up only for en passant 
        bool validMove = true, gameOngoing = true, turn = true, gotInitial = false;
        //variable turn: true = white, false = black for which color's turn it is.
        int hasMoved[6] = {0, 0, 0, 0, 0, 0};
        /*
        This is to check if a piece necessary for castling has moved yet (as castling has to be a pieces' first move if done)
        They stand for the pieces as follows:
        White left rook, white king, white right rook (uppercase pieces)
        Black left rook, black king, black right rook (undercase pieces)
        */
        //board initalization, this is the loop for replayability 
        boardInitalization (board);
        do {
            //board creation
            boardCreation(board);
            gotInitial = false;

            if (turn){
                cout << "White's turn." << endl;
            } else {
                cout << "Black's turn." << endl; 
            }

            do {
                if (!validMove){
                    cout << "That move was not valid, please try again." << endl;
                    validMove = true;
                    if (inCheck == 1){
                        cout << "You are currently in check or moving into check, please save your king." << endl;
                        inCheck = 0;
                    }
                }
                cout << "Enter the location of the piece you want to move." << endl;
                cout << "For example, A2 would move the pawn in the first column, second row." << endl;

                initialPlacement = getUserInputAndConvert(turn, board, gotInitial);
                gotInitial = true; 
                pieceMoved = board[initialPlacement];
                cout << "Where would you like to move this piece to?" << endl;
                cout << "Enter as A2, E6, F8, etc." << endl;
                endPlacement = getUserInputAndConvert(turn, board, gotInitial);
                validMove = checkIfPossible(initialPlacement, endPlacement, pieceMoved, board, userLastMove, hasMoved);
                
                //Determines you are not currently in check and staying in it/moving into check
                kingPosition = findKing(board, turn);
                inCheck = checkForCheck(kingPosition, board, initialPlacement, endPlacement);

                if (inCheck == 1){
                    validMove = false;
                } else if (inCheck == 2){
                    /*
                    I recognize that sometimes pieces may be able to intersect and interrupt the path to the king
                    And I know this may result in an inCheck == 2 and the game may be able to be continued
                    However, as things stand I don't want to check that in this version see the ReadMe for more info
                    */
                    gameOngoing = false;
                }

            } while (!validMove);
            
            //typically this will just set it equal to pieceMoved (itself) unless if it's a promoting pawn
            pieceMoved = pawnPromotionCheck(pieceMoved, endPlacement);
            
            if (board[initialPlacement] == '_'){
                /*
                This is impossible except in the case of castling where I already went in and changed
                the individual board[square numbers].
                otherwise initial placement cannot be == to _ because you can't move nothing
                without this, when the user castles they will gain another king
                */
            } else {
                board[endPlacement] = pieceMoved;
                board[initialPlacement] = '_';
            }

            //registers last piece moved (this is used to check for en passants) and occurs after move is valid
            userLastMove = endPlacement;

            if (turn){
                //if white become black
                turn = false;
            } else {
                turn = true;
            }    

            kingPosition = findKing(board, turn);
            inCheck = checkForCheck(kingPosition, board);

            if (inCheck == 1 || inCheck == 2){
                cout << "You are in check! You have one chance to save your king!" << endl;
            } 

        } while (gameOngoing);

        if(turn == true){
            cout << "White wins!" << endl;
        } else {
            cout << "Black wins!" << endl;
        }

        cout << "Want to play again? Type 1 for yes and anything else for no." << endl;

        cin >> gameStart;

    } while (gameStart == 1);



    return 0;
}