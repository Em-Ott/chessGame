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