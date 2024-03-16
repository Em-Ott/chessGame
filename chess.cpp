#include <iostream>
#include <sstream> 

using namespace std;

/*
Splitting up code: 
chess.cpp, has main function which:
-has cout at beginning explaining what letters are which pieces
-creates base chessboard with all pieces in starting place
then I plan to have files for:
user input, determining if it's valid, and if it will kill a piece
*/

int main(){
    bool gameWon = false;
    char piece = '_';
    //the starting spots for all chess pieces are their initial value
    //pieces 0-7, 0-1, 0, lower number pieces are white
    int pawn [16];
    int queen [2];
    int king [2];
    int bishop [4];
    int horse [4];
    int rook [4];
    //white pieces given their starting value
    pawn[7] = 55; 
    pawn[6] = 54; 
    pawn[5] = 53; 
    pawn[4] = 52; 
    pawn[3] = 51; 
    pawn[2] = 50; 
    pawn[1] = 49; 
    pawn[0] = 48;
    rook[0] = 63;
    rook[1] = 56;
    horse[0] = 57;
    horse[1] = 62;
    bishop[0] = 58;
    bishop[1] = 61;
    queen[0] = 59;
    king[0] = 60;
    //black pieces given their starting value
    pawn[8] = 15;
    pawn[9] = 14;
    pawn[10] = 13;
    pawn[11] = 12;
    pawn[12] = 11;
    pawn[13] = 10;
    pawn[14] = 9;
    pawn[15] = 8;
    rook[2] = 0;
    rook[3] = 7;
    horse[2] = 1;
    horse[3] = 6;
    bishop[2] = 2;
    bishop[3] = 5;
    queen[1] = 3;
    king[1] = 4;

    /*
    If statement to create the board with pieces in the accurate place.
    Using a count of 64, because 64 total spaces and it makes labeling and moving the pieces easier
    */
   for (int i = 0; i < 64; ++i){
    //below statement will check if any piece takes up that spot on the boards. 16 because it is the max # of pieces
    for (int j = 0; j < 16; ++j){
        if(pawn[j] == i){
            piece = 'p';
            break; //used so the loop doesn't continue once we know if there is a piece
        } else if (rook[j] == i){
            piece = 'r';
            break;
        } else if (horse[j] == i){
            piece = 'h';
            break;
        } else if (bishop[j] == i){
            piece = 'b';
            break;
        } else if (queen[j] == i){
            piece = 'q';
            break;
        } else if (king[j] == i){
            piece = 'k';
            break;
        } else {
            piece = '_';
        }
    }
        //this is for the top 8 lines of the board which will never have a piece
        if (i == 0){
            for (int j = 0; j < 8; ++j){
            cout << " _ ";
            }
        }    
        if (i%8 == 0){
            cout << endl;
        }
        cout << "|" << piece << "|";
   }

    return 0;
}