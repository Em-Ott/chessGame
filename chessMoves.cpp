#include "chess.h"

/*
This file is only for my very long functions of checking whether a move is possible or not
Includes the main checkIfPossible functions as well as the smaller functions for shared movesets:
-Horizontal/Vertical
-Diagonal
As well as functions inside of checkIfPossible which I added to try and make it more organized:
-Horse Function
-En Passant
*/

bool checkIfPossible(int startingPosition, int endingPosition, char piece, char board[], int lastMove){
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
            } else if (enPassant(startingPosition, endingPosition, board, lastMove) == true){
                board[lastMove] = '_';
                //enemy pawn is taken
            }
            else {
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
            } else if (enPassant(startingPosition, endingPosition, board, lastMove) == true){
                board[lastMove] = '_';
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

bool enPassant(int startingPosition, int endingPosition, char board[], int lastMove){
    bool valid = true; 

    if ((board[startingPosition] == 'p') && (startingPosition/8 == 4) 
    && (board[lastMove] == 'P') && (lastMove/8 == 4)
    && (endingPosition == lastMove + 8)){
        /*
        reminder: integer division rounds down, the row we will be looking at is 39-32 so it will round down to 4
        further more checks that the last move was a pawn moving to second row (32-39)
        THEN it has to check once more that the pawn is doing a diagonal move to be above the lastMoved pawn
        valid en passant for white
        I hate whoever made en passant a thing. They made me add a whole new variable for this dumb move
        */
    } else if ((board[startingPosition] == 'P') && (startingPosition/8 == 3)
    && (board[lastMove] == 'p') && (lastMove/8 == 3)
    && (endingPosition == lastMove - 8)){
        //row we are looking at is 24-31 any of these divided by 8 will be 3 
        //valid en passant for black
    } else {
        valid = false;
    }

    return valid;
}