#include "chess.h"

int main(){
    int gameStart = 0, column = 0;
    char piece = '_';
    /*Half of the list (0-7 for pawns) will be white and the other half (8-15 for pawns) will be black.
    I am doing it this way because it will make it easier to check for conditions using loops.
    I also decided to give the pieces a seperate variable for x and y as I think it will make
    checking whether a move is valid or not easier.*/
    int pawnX[16] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7};
    int pawnY[16] = {6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1};
    int rookX[4] = {0, 7, 0, 7};
    int rookY[4] = {7, 7, 0, 0};
    int horseX[4] = {1, 6, 1, 6};
    int horseY[4] = {7, 7, 0, 0};
    int bishopX[4] = {2, 5, 2, 5};
    int bishopY[4] = {7, 7, 0, 0};
    int queenX[2] = {3, 3};
    int queenY[2] = {7, 0};
    int kingX[2] = {4, 4};
    int kingY[2] = {7, 0};

    //Explanation of How This Is Set Up
    cout << "The pieces are abbreviated as the following: " << endl << "Pawn: p" << endl << 
    "Rook: r" << endl << "Horse: h" << endl << "Bishop: b" << endl << "Queen: q" << endl <<
    "King: k" << endl << "The white pieces are capital letters and the black pieces are lower case." << endl;
    cout << "To begin type 1." << endl;
    cin >> gameStart;

    while (gameStart == 0 || cin.fail()){
    cin.clear();
    cin.ignore(256, '\n');
    cin >> gameStart;
    }
    cout << endl; //just so it looks better visually

    /*
    Our loop with i creates the different rows
    Our loops with j creates the different columns
    */
    do {
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 8; ++j){
                if (i == 0 && j == 0){
                    for (int k = 0; k < 8; ++k){
                        //The if statements in this fix formatting from the integer on the left
                        //The k statements used to make the top row and numbers on the top
                        if (k == 0){
                            cout << "   " << k + 1 << " ";
                        } else {
                            cout << " " << k + 1 << " ";
                        }
                    }
                    cout << endl;
                    for (int k = 0; k < 8; ++k){
                        if (k == 0){
                            cout << "   _ ";
                        } else {
                            cout << " _ ";
                        }
                    }
                    cout << endl;
                }
                if (j == 0){
                    cout << i + 1 << " ";
                }
                for (int k = 0; k < 16; ++k){
                    if (pawnY[k] == i && pawnX[k] == j){
                        if (k < 8){
                            piece = 'P';
                        } else {
                            piece = 'p';
                        }
                    }
                }
                for (int k = 0; k < 4; ++k){
                    if (rookY[k] == i && rookX[k] == j){
                        if (k < 2){
                            piece = 'R';
                        } else {
                            piece = 'r';
                        }
                    }
                }
                for (int k = 0; k < 4; ++k){
                    if (horseY[k] == i && horseX[k] == j){
                        if (k < 2){
                            piece = 'H';
                        } else {
                        piece = 'h';
                        }
                    }
                }
                for (int k = 0; k < 4; ++k){
                    if (bishopY[k] == i && bishopX[k] == j){
                        if (k < 2){
                            piece = 'B';
                        } else {
                            piece = 'b';
                        }
                    }
                }
                for (int k = 0; k < 2; ++k){
                    if (queenY[k] == i && queenX[k] == j){
                        if (k < 1){
                            piece = 'Q';
                        } else {
                            piece = 'q';
                        }
                    }
                }
                for (int k = 0; k < 2; ++k){
                    if (kingY[k] == i && kingX[k] == j){
                        if (k < 1){
                            piece = 'K';
                        } else {
                            piece = 'k';
                        }
                    }
                }
                cout << "|" << piece << "|";
                piece = '_';
            }
            cout << endl;
        }
        cout << "White moves first. First select the piece you would like to move first type the column it's in." << endl;
        cin >> column;
    } while (gameStart == 0);

    return 0;
}