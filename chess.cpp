#include "chess.h"

/*
What I've learned so far:
Can use .at(#) or [#] on strings to figure out what's at #
When using .at(#) or [#] on a string and I am expecting an integer (int var = string.at(#))
it will return the ASCII value of that integer (interesting)

*/
/*
To do, after basics:
Check for invalid input

*/

int main(){
    char board[64], pieceMoved;
    int gameStart = 0, initialPlacement = 0, endPlacement = 0;
    string userMove;
    bool validMove = true, gameOngoing = true, turn = true, gotInitial = false;
    //variable turn true = white, false = black for which color's turn it is.

    cout << "The pieces are abbreviated as the following: " << endl << "Pawn: p" << endl << 
    "Rook: r" << endl << "Horse: h" << endl << "Bishop: b" << endl << "Queen: q" << endl <<
    "King: k" << endl << "The white pieces are capital letters and the black pieces are lower case." << endl;
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

            cout << "Enter the location of the piece you want to move." << endl;
            cout << "For example, A2 would move the pawn in the first column, second row." << endl;

            initialPlacement = getUserInputAndConvert(turn, board, gotInitial);
            gotInitial = true; 
            pieceMoved = board[initialPlacement];
            cout << "Where would you like to move this piece to?" << endl;
            cout << "Enter as A2, E6, F8, etc." << endl;
            endPlacement = getUserInputAndConvert(turn, board, gotInitial);
            
            
            board[endPlacement] = pieceMoved;
            board[initialPlacement] = '_';

            /*
            After receiving end and initial placement check if possible
            based on piece. Check for checkmate function, add take pieces function. 
            And in getUserInputAndConvert do not allow them to move the other
            pieces places. Turn will likely become a parameter.
            */


            if (turn){
                turn = false;
            } else {
                turn = true;
            }
            
        } while (gameOngoing);
    } 



    return 0;
}