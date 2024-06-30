#include "chess.h"

/*
TO DO:
Check + Checkmate
Make it so king can't move into check
Current problems:
implement a feature which stops a king from moving into check
*/

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
            && ((board[endingPosition] > 'a') && (board[endingPosition] != '_'))){
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
            && (board[endingPosition] < 'a')){
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
        validMove = whitePieceMoveOnWhitePiece(endingPosition, board);
        validMove = horseMoveCheck(startingPosition, endingPosition, board, validMove);

        break;
        case 'h':
        validMove = blackPieceMoveOnBlackPiece(endingPosition, board);
        validMove = horseMoveCheck(startingPosition, endingPosition, board, validMove);

        break;
        case 'B':
        validMove = whitePieceMoveOnWhitePiece(endingPosition, board);
        validMove = diagonalMoveCheck(startingPosition, endingPosition, board, validMove);

        break;
        case 'b':
        validMove = blackPieceMoveOnBlackPiece(endingPosition, board);
        validMove = diagonalMoveCheck(startingPosition, endingPosition, board, validMove);

        break;
        case 'Q':
        validMove = whitePieceMoveOnWhitePiece(endingPosition, board);
        if ((horizontalAndVerticalMoveCheck(startingPosition, endingPosition, board, validMove)) == 
        (diagonalMoveCheck(startingPosition, endingPosition, board, validMove))){
            validMove = false;
        }

        break;
        case 'q':
        validMove = blackPieceMoveOnBlackPiece(endingPosition, board);
        /*
        if horizontal is false and diagonal is true then the queen is moving diagonally therefore the move
        is diagonal, and vice versa meaning the move would be valid.
        they can't both return true but they can both return false meaning the queen is neither moving
        diagonally or horizontally or vertically, meaning the move is illegal if they both return false
        and thus, if they return the same value
        */
        if ((horizontalAndVerticalMoveCheck(startingPosition, endingPosition, board, validMove)) == 
        (diagonalMoveCheck(startingPosition, endingPosition, board, validMove))){
            validMove = false;
        }

        break;
        case 'K':
        validMove = whitePieceMoveOnWhitePiece(endingPosition, board);
        validMove = kingMoveCheck(startingPosition, endingPosition, board, validMove);

        break; 
        case 'k':
        validMove = blackPieceMoveOnBlackPiece(endingPosition, board);
        validMove = kingMoveCheck(startingPosition, endingPosition, board, validMove);

        break;
    } 


    return validMove;
}

bool blackPieceMoveOnBlackPiece(int endingPosition, char board[]){
    bool validMove = true;
    //black pieces are all lowercase
    if((board[endingPosition] > 'a')){
        validMove = false;
    }

    return validMove;
}

bool whitePieceMoveOnWhitePiece(int endingPosition, char board[]){
    bool validMove = true;
    //white pieces are uppercase (ASCII values higher than z)
    if(board[endingPosition] < 'a' && board[endingPosition] != '_'){
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

    //horizontal 
    if ((startingPosition/8) == (endingPosition/8)){
        //checks if they are in the same row, integer division rounds down so 0/8 and 7/8 are both 0
        /*
        next every spot on the way to their ending position needs to be checked since a piece 
        can't fly over other pieces
        */
        if (startingPosition < endingPosition){
            for (int i = 1; i < distanceMoved; ++i){
              if (board[startingPosition + i] == '_'){
                //space clear, can continue checking
              } else {
                if (distanceMoved == i){
                  return validMove;
                }
                 validMove = false;
                }
            }
        } else if (endingPosition < startingPosition){
              for (int i = 1; i < distanceMoved; ++i){
                if (board[startingPosition - i] == '_'){
                  //space is clear can continue checking
                } else {
                    if (distanceMoved == i){
                        return validMove;
                   }
                    validMove = false;
                 }
            }
       }
    } else if (distanceMoved%8 == 0){
        //vertical movement
        if (startingPosition < endingPosition){
            for(int i = 1; i*8 < distanceMoved; ++i){
              if(board[startingPosition + (i*8)] == '_'){
                    //space is clear can continue checking
                } else {
                    if (distanceMoved == i*8){
                        return validMove;
                    }
                    validMove = false;
                }
            }
        } else if (endingPosition < startingPosition){
            for(int i = 1; i*8 < distanceMoved; ++i){
              if(board[startingPosition - (i*8)] == '_'){
                    //space is clear, can continue checking
                } else {
                    if (distanceMoved == i*8){
                        return validMove;
                    }
                    validMove = false;
                }
            }
        }
    } else {
        validMove = false;
    }
    return validMove;
}

bool diagonalMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove){
    //check for multiples of 9s and 7s
    int distanceMoved = 0, nineMovement = 0, sevenMovement = 0;
    distanceMoved = abs(startingPosition - endingPosition); 
    //using absolute value so it's easier to check in for loops

    if (distanceMoved == 0){
        validMove = false;
    }

    //then I use this to know which direction to check in
    if(startingPosition > endingPosition){
        sevenMovement = -7;
        nineMovement = -9;
    } else {
        sevenMovement = 7;
        nineMovement = 9;
    }

    if (distanceMoved%7 == 0){
        for(int i = 1; i*7 <= distanceMoved; ++i){
            if (board[startingPosition + i * sevenMovement] == '_'){
                //space is clear loop continues
            } else {
                if (distanceMoved == i * sevenMovement){
                    return validMove;
                }
                validMove = false;
            }     
        }
    } else if (distanceMoved%9 == 0) {

        for(int i = 1; i*9 <= distanceMoved; ++i){
            if (board[startingPosition + i * nineMovement] == '_'){
                //space is blank can continue checking
            } else {
                if (distanceMoved == i * abs(nineMovement)){
                    return validMove;
                }
                validMove = false;
            }     
        }
    } else {
        validMove = false;
    }
    
    return validMove;
}

bool horseMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove){
    //Knights are -17, -15, -10, -6, +6, +10, +15, +17 we don't need to check for it flying pver other pieces
    int distanceMoved = 0;
    distanceMoved = abs(endingPosition - startingPosition);
    if ((distanceMoved == 17) || (distanceMoved == 15) || (distanceMoved == 10) || (distanceMoved == 6)){

    } else {
        validMove = false;
    }
    return validMove;
}

bool kingMoveCheck(int startingPosition, int endingPosition, char board[], bool validMove){
    //-9, -8, -7, +9, +8, +7, +1 ,-1
    int distanceMoved = 0; 
    distanceMoved = abs(endingPosition - startingPosition);
    if ((distanceMoved == 9) || (distanceMoved == 8) || (distanceMoved == 7) || (distanceMoved == 1)){

    } else {
        validMove = false;
    }
    //add something to make sure the king can't move into somewhere it'd die
    return validMove;
}

char pawnPromotionCheck(char pieceMoved, int endingPosition){

    if (pieceMoved == 'P' && endingPosition < 8){
        //if your pawn reaches the end of the opponents board
        cout << "Your white pawn has been promoted!" << endl << 
        "What would you like to promote it to?" << endl;
        cin >> pieceMoved;
        while (pieceMoved != 'Q' && pieceMoved != 'H' && pieceMoved != 'B' && pieceMoved != 'R'){
            cout << "That is not a piece please enter Q, H, B, or R for Queen, Horse, Bishop, and Rook respectively." << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> pieceMoved;
        }
    } else if (pieceMoved == 'p' && endingPosition > 55){
        cout << "Your black pawn has been promoted!" << endl << 
        "What would you like to promote it to?" << endl;
        cin >> pieceMoved;
        while (pieceMoved != 'q' && pieceMoved != 'h' && pieceMoved != 'b' && pieceMoved != 'r'){
            cout << "That is not a piece please enter q, h, b, or r for Queen, Horse, Bishop, and Rook respectively." << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> pieceMoved;
        }
    }

    return pieceMoved;
}