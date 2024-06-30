#ifndef CHESS_H

#define CHESS_H

#include <iostream>
#include <string>
#include <cmath>

/*cmath may seem strange to include but I'm using it mainly for the abs() function, in regards to distance
a piece may've moved.
the other two are pretty self explanatory. 
*/

using namespace std;

void boardInitalization (char board[]);
void boardCreation(char board[]);
int userMoveColumn(string userMove, bool& validMove);
int getUserInputAndConvert(bool turn, char board[], bool initialInput);
bool checkIfPossible(int startingPosition, int endingPosition, char piece, char board[]);
bool blackPieceMoveOnBlackPiece(int endingPosition, char board[]);
bool whitePieceMoveOnWhitePiece(int endingPosition, char board[]);
bool horizontalAndVerticalMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove);
bool diagonalMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove);
bool horseMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove);
bool kingMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove);
char pawnPromotionCheck(char pieceMoved, int endingPosition);

#endif

