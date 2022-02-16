//
//  busegundogar_Gundogar_Buse_hw_Player.cpp
//  busegundogar_Gundogar_Buse_hw6
//
//  Created by Buse Gündoğar on 2.05.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//

#include <iostream>
#include "busegundogar_Gundogar_Buse_hw_Player.h"


//template <class T>
//Player<T>::Player(){
    //score = 0;
    //gameBoard = Board<T>();
//}

template <class T>
Player<T>::Player(Board<T> &givenBoard):gameBoard(givenBoard){
    score = 0;
}

//This function takes a card row,col and returns its face value by opening the card
template <class T>
T Player<T>::openCard(int r, int c){
    gameBoard.openCard(r, c);
    return gameBoard.getFace(r, c);
}

//This function checks the row and column inputs
template <class T>
bool Player<T>::validMove(int r, int c){ 
    
    int rows = gameBoard.getRow();
    int cols = gameBoard.getColumn();
    
    if(r + 1 > rows){ //If row is out of limits, returns false
        cout << "a" << endl;
        return false;
    }
    else if(c + 1 > cols){ //If col is out of limits, returns false
        cout << "b" << c << cols << endl;
        
        return false;
    }
    else if(gameBoard.openCheck(r, c)){ //If the card is open, returns false
        cout << "c" << endl;

        return false;
    }
    
    return true;
}

template <class T>
void Player<T>::increaseNumberOfSuccess(){
    score = score + 1;
}

template <class T>
int Player<T>::getNumberOfSuccess(){
    return score;
}
