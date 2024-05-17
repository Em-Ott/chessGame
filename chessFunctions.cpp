#include "chess.h"

void boardInitalization (char board[]){
    for (int i = 0; i < 64; ++i){
        board[i] = '_';
    }

    board[0] = 'r';
    board[1] = 'h';
    board[2] = 'b';
    board[3] = 'q';
    board[4] = 'k';
    board[5] = 'b';
    board[6] = 'h';
    board[7] = 'r';

    for (int i = 8; i < 16; ++i){
        board[i] = 'p';
    }

    for (int i = 48; i < 56; ++i){
        board[i] = 'P';
    }

    board[56] = 'R';
    board[57] = 'H';
    board[58] = 'B';
    board[59] = 'Q';
    board[60] = 'K';
    board[61] = 'B';
    board[62] = 'H';
    board[63] = 'R';
}

void boardCreation(char board[]){
    int row = 1;
    for (int i = 0; i < 64; ++i){
        if (i == 0){
            cout << "   A  B  C  D  E  F  G  H" << endl;
            for (int j = 0; j < 8; ++j){
                if (j == 0){
                    cout << "   _ ";
                } else {
                    cout << " _ ";
                }
            }
            cout << endl;
            cout << row << " ";
            ++row;
        } 
        cout << "|" << board[i] << "|";
        if ((i + 1 )%8 == 0){
            cout << endl;
            if (row != 9){
                cout << row << " ";
                ++row;
            }
        }
    }
}

int userMoveColumn(string userMove, bool& validMove){
    char column;
    int columnNumber;
    column = userMove[0];

    switch (column){
        case 'A':
            columnNumber = 0;
            break;

        case 'B':
            columnNumber = 1;
            break;

        case 'C':
            columnNumber = 2;
            break;

        case 'D':
            columnNumber = 3;
            break;

        case 'E':
            columnNumber = 4;
            break;

        case 'F':
            columnNumber = 5;
            break;

        case 'G':
            columnNumber = 6;
            break;

        case 'H':
            columnNumber = 7;
            break;

        default:
            validMove = false;
            break;
        } 
    return columnNumber;
}

int getUserInputAndConvert(bool turn, char board[], bool initialInput){
    bool validMove;
    string userMove; 
    int userColumn, userRow, squareMoved;
    //turn = white !turn = black

    do{
        validMove = true; //resets validMove value if previously false
        cin >> userMove;
        userColumn = userMoveColumn(userMove, validMove);
        //the -48 accounts for userRow taking userMove[1] as its ASCII value. ASCII 49 = 1.
        userRow = userMove[1] - 49;
        if (userRow >= 8){
            validMove = false;
        }

        for (int i = 0; i < 64; ++i){
            if ((userColumn + (userRow* 8)) == i){
                squareMoved = i;
            }
        }

        /*
        This is just to make sure the piece they're moving is their own
        It isn't applicable to the space they're moving it to so initialInput
        keeps track of whether or not it's the first time this function is used
        or second for the current turn. 
        */
        if (!initialInput){
            //If white it'll be a capital letter (lower ASCII value)
            if (turn){
                if (board[squareMoved] > 'Z'){
                    validMove = false;
                }
            } else {
                if (board[squareMoved] < 'a'){
                    validMove = false;
                }
            }
        }

        if (!validMove){
            cout << "That move was invalid please enter it again." << endl 
            << "Remember to use capital letters and a number under 9." << endl;
        }
    } while (!validMove);

    return squareMoved;
}

bool checkIfPossible(int startingPosition, int endingPosition, char piece, char board[]){
    bool validMove = true;

    switch (piece){
        case 'P':
            validMove = whitePieceMoveOnWhitePiece(endingPosition, board);
            //pawns don't have a seperate function since they can only move forward so the ifs are different
            
            if ((startingPosition - 8 == endingPosition) && (board[endingPosition] == '_')){
                //these do nothing so if validMove was made false by the previous function call above it will remain false
            } else if ((startingPosition - 16 == endingPosition) && (startingPosition >= 48) 
            && (board[endingPosition] == '_')){
                //if in starting spot can move 2 forward
            } else if (((startingPosition - 7 == endingPosition) || (startingPosition - 9 == endingPosition)) 
            && ((board[endingPosition] <= 'z') && (board[endingPosition] != '_'))){
               //allows for taking of other pieces using the ASCII value of lowercase (less than uppercase) 
               //and excluding '_' (ASCII value 95)
            } else {
                validMove = false;
            }
        break;

        case 'p':
            validMove = blackPieceMoveOnBlackPiece(endingPosition, board);

            if ((startingPosition + 8 == endingPosition) && (board[endingPosition] == '_')){
                
            } else if ((startingPosition + 16 == endingPosition) && (startingPosition < 16) 
            && (board[endingPosition] == '_')){
            
            } else if (((startingPosition + 7 == endingPosition) || (startingPosition + 9 == endingPosition)) 
            && (board[endingPosition] > 'z')){
               //allows for taking of other pieces using the ASCII value of lowercase (less than uppercase) 
            } else {
                validMove = false;
            }
            
        break;

        case 'R':
        validMove = whitePieceMoveOnWhitePiece(endingPosition, board);
        //using validMove as a variable allows it to remain false if it already is false
        validMove = horizontalAndVerticalMoveCheck(startingPosition, endingPosition, board, validMove);
        break;

        case 'r':
        validMove = blackPieceMoveOnBlackPiece(endingPosition, board);
        validMove = horizontalAndVerticalMoveCheck(startingPosition, endingPosition, board, validMove);
        break;

        case 'H':


        case 'h':

        break;
        case 'B':
        case 'b':

        break;
        case 'Q':
        case 'q':

        break;
        case 'K':
        case 'k':

        break;
    } 


    return validMove;
}

bool blackPieceMoveOnBlackPiece(int endingPosition, char board[]){
    bool validMove = true;
    //black pieces are all lowercase
    if((board[endingPosition] < 'z') && board[endingPosition] != '_'){
        validMove = false;
    }

    return validMove;
}

bool whitePieceMoveOnWhitePiece(int endingPosition, char board[]){
    bool validMove = true;
    //white pieces are uppercase (ASCII values higher than z)
    if(board[endingPosition] > 'z'){
        validMove = false;
    }

    return validMove;
}

bool horizontalAndVerticalMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove){
    int distanceMoved = 0;
    distanceMoved = abs(startingPosition - endingPosition);

    if (distanceMoved == 0){
        validMove = false;
    }
    if ((startingPosition/8) == (endingPosition/8)){
        //checks if they are in the same row, integer division rounds down so 0/8 and 7/8 are both 0
        /*
        next every spot on the way to their ending position needs to be checked since a piece 
        can't fly over other pieces
        */
        if (startingPosition < endingPosition){
            for (int i = 1; i <= distanceMoved; ++i){
              if (board[startingPosition + i] == '_'){
                if (distanceMoved == i){
                  return validMove;
                }
              } else {
                 validMove = false;
                }
            }
        } else if (endingPosition < startingPosition){
              for (int i = 1; i <= distanceMoved; ++i){
                if (board[startingPosition - i] == '_'){
                  if (distanceMoved == i){
                    return validMove;
                   }
                } else {
                    validMove = false;
                 }
            }
       }
    } else if (distanceMoved%8 == 0){
        //vertical movement
        if (startingPosition < endingPosition){
            for(int i = 1; i*8 <= distanceMoved; ++i){
              if(board[startingPosition + (i*8)] == '_'){
                    if (distanceMoved == i*8){
                        return validMove;
                    }
                } else {
                    validMove = false;
                }
            }
        } else if (endingPosition < startingPosition){
            for(int i = 1; i*8 <= distanceMoved; ++i){
              if(board[startingPosition - (i*8)] == '_'){
                    if (distanceMoved == i*8){
                        return validMove;
                    }
                } else {
                    validMove = false;
                }
            }
        }
    } else {
        validMove = false;
    }
    return validMove;
}

bool verticalMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove){
    int distanceMoved = 0;
    distanceMoved = abs(startingPosition - endingPosition);
}