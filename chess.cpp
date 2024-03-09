#include <iostream>
#include <sstream> 

using namespace std;

char horsePiece(double x, double y);

int main(){
    char piece = '_';
    int whitePawn1 = 56;

    /*
    -Need way to assign piece numbers to areas (maybe something to do with checking if divisble by?) or make the loop by 64
    for (int i = 0; i < 64; ++i){
        for (int j = 0; j < 8; ++j){
        if ((whitePawn + ) == i) (is that possible in c++){
            piece = 'p';
        }}
    then do with rest of pieces, is there a way less tedious? 
    I'm thinking there could also be a way to do it where we use both character and integer (a8) but I feel like that's a lot of variables
    Maybe make into a function whitePawn1(character, integer)
    }
    -Remove chess pieces once they are considered "dead"
    -Need function checking if player move is valid. 
    -Pawn promotion system
    
    
    */
    

    //This allows for the chessboard to be printed out with pieces in the correct location
    for (int i = 0; i < 8; ++i){
        //this allows for the top of the chess board to also be squares
        for (int j = 0; j < 8; ++j){
            if (i == 0){
            cout << " _ ";
            }
        }
    //prints out chess board in following layout: |piece| where default piece is _
    cout << endl;
    for (int i = 0; i < 8; ++i){
    cout << "|" << piece << "|";
    }
    }

    return 0;
}

char horsePiece(double x, double y){
    bool valid;
    if ((x+1)||(x-1)){
        if ((y+2)||(y-2)){
            valid == true;
        } else {
            valid == false;
        }
    } else {
        valid == false;
    }

    if (valid){
    return 'h';
    } else {
        cout << "That is an invalid movement, enter again." << endl;
        cin >> x;
        cin >> y;
    }

}