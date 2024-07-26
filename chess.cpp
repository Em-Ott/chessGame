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
Current issues:
when doing Bbishop 2nd move check, Wqueen sacrifice Wbishop + Wking cannot take Bbishop (Whorse can)
-bishop having broken diagonal movement (received not valid message)? couldn't replicate issue but keep an eye out for it
-Problems with moving king? Not sure, keep watching
Current TO DO:
-fix issues
-implement checkmate
*/


int main(){
    /*
    could also do a multidimensional array [8][8]
    it would mainly just change the way the board is created (double loop)
    and in checking if valid would check row and column
    */
    char board[64], pieceMoved;
    int gameStart = 0, initialPlacement = 0, endPlacement = 0, kingPosition = 0;
    int userLastMove = 0; //this is straight up only for en passant 
    bool validMove = true, gameOngoing = true, turn = true, gotInitial = false, inCheck = false;
    //variable turn: true = white, false = black for which color's turn it is.
    int hasMoved[6] = {0, 0, 0, 0, 0, 0};
    /*
    This is to check if a piece necessary for castling has moved yet (as castling has to be a pieces' first move if done)
    They stand for the pieces as follows:
    White left rook, white king, white right rook (uppercase pieces)
    Black left rook, black king, black right rook (undercase pieces)
    */

    cout << "The pieces are abbreviated as the following: " << endl << "Pawn: p" << endl << 
    "Rook: r" << endl << "Knight/Horse: h" << endl << "Bishop: b" << endl << "Queen: q" << endl <<
    "King: k" << endl << "The white pieces are capital letters and the black pieces are lower case." << endl;
    cout << "To castle enter your King's location as the starting square and your Rook's location as the ending square." << endl;
    cout << "To begin type 1." << endl;

    cin >> gameStart;

    while (gameStart == 1){
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
                    if (inCheck){
                        cout << "You are currently in check or moving into check, please save your king." << endl;
                        inCheck = false;
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

                if (inCheck){
                    validMove = false;
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


            kingPosition = findKing(board, turn);
            inCheck = checkForCheck(kingPosition, board, initialPlacement, endPlacement);

            if (inCheck){
                //checkForCheckmate + cout to tell them they are currently in check if not in checkmate
            }

           /*
           if the game is ongoing (not in checkmate) it will return the opposite of whether it is checkmate or not
            so if it's true (in checkmate) the gameOngoing will be false and the game will be exited
           */

           //gameOngoing = !(checkForCheckmate);

            if (turn){
                turn = false;
            } else {
                turn = true;
            }    

        } while (gameOngoing);

        if(turn == true){
            cout << "White wins!" << endl;
        } else {
            cout << "Black wins!" << endl;
        }

        cout << "Want to play again? Type 1 for yes and anything else for no." << endl;

        cin >> gameStart;
    } 



    return 0;
}