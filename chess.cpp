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
    int gameStart, userRow, userColumn, pieceMovedSquare;
    string userMove;

    cout << "The pieces are abbreviated as the following: " << endl << "Pawn: p" << endl << 
    "Rook: r" << endl << "Horse: h" << endl << "Bishop: b" << endl << "Queen: q" << endl <<
    "King: k" << endl << "The white pieces are capital letters and the black pieces are lower case." << endl;
    cout << "To begin type 1." << endl;
    cin >> gameStart;

    while (gameStart == 1){
        //board initalization 
        boardInitalization (board);
        //board creation
        boardCreation(board);
        cout << "White moves first. Enter the location of the piece you want to move." << endl;
        cout << "For example, A2 would move the pawn in the first column, second row." << endl;
        cin >> userMove;
        userColumn = userMoveColumn(userMove);
        //the -48 accounts for userRow taking userMove[1] as its ASCII value. ASCII 49 = 1.
        userRow = userMove[1] - 48;
        for (int i = 0; i < 64; ++i){
            if (((userColumn * 8) + userRow) == i){
                pieceMovedSquare = i;
            }
        }
        pieceMoved = board[pieceMovedSquare];
        cout << "Where would you like to move this piece to?" << endl;
        cout << "Enter as A2, E6, F8, etc." << endl;
        cout << pieceMoved;
    } 



    return 0;
}