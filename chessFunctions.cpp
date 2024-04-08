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

int userMoveColumn(string userMove){
    char column;
    int columnNumber;
    column = userMove[0];
    
    switch (column){
        case 'A':
        columnNumber = 1;
        break;

        case 'B':
        columnNumber = 2;
        break;

        case 'C':
        columnNumber = 3;
        break;

        case 'D':
        columnNumber = 4;
        break;

        case 'E':
        columnNumber = 5;
        break;

        case 'F':
        columnNumber = 6;
        break;

        case 'G':
        columnNumber = 7;
        break;

        case 'H':
        columnNumber = 2;
        break;
    }
    return columnNumber;
}