#include <iostream>
#include <sstream> 

using namespace std;

char horsePiece(double x, double y);

int main(){
    char piece = '_';
    //the starting spots for all chess pieces are their initial value
    int whitePawn8 = 55, whitePawn7 = 54, whitePawn6 = 53, whitePawn5 = 52, whitePawn4 = 51, whitePawn3 = 50, whitePawn2 = 49, whitePawn1 = 48;

    /*
    -Need way to assign piece numbers to areas (maybe something to do with checking if divisble by?) or make the loop by 64
    then do with rest of pieces, is there a way less tedious? 
    I'm thinking there could also be a way to do it where we use both character and integer (a8) but I feel like that's a lot of variables
    Maybe make into a function whitePawn1(character, integer)
    }
    -Remove chess pieces once they are considered "dead"
    -Need function checking if player move is valid. 
    -Pawn promotion system
    */

    /*
    If statement to create the board with pieces in the accurate place.
    Using a count of 64, because 64 total spaces and it makes labeling and moving the pieces easier
    */
   for (int i = 0; i < 64; ++i){
    //below statement will check if any piece takes up that spot on the boards
    for (int j = 1; j <= 8; ++j){
        /*would it be possible to do something like this?
        or would I just have to do:
        if((whitePawn1) == i){
            piece = 'p';
        } else if (whitePawn2 == i){
            piece = 'p';
        }....
        else {
            piece = '_';
        }
        */
        if((whitePawn + j) == i){
            piece = 'p';
        } else {
            piece = '_';
        }
    }
        if (i==0){
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

    while (!valid){
        cout << "That is an invalid movement, enter again." << endl;
        cin >> x;
        cin >> y;
        //rechecks conditions
        //another way i could do this is to do x + (y*8) and then check if it's mathematically possible for the piece to move there
        if ((x+1)||(x-1)){
            if ((y+2)||(y-2)){
                valid == true;
            }
        }
    }

    return 'h';
}