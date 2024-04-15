#ifndef CHESS_H

#define CHESS_H

#include <iostream>
#include <string>

using namespace std;

void boardInitalization (char board[]);
void boardCreation(char board[]);
int userMoveColumn(string userMove, bool& validMove);
int getUserInputAndConvert(bool turn, char board[], bool initialInput);

#endif

