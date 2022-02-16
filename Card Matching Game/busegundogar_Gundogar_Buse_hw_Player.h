//
//  busegundogar_Gundogar_Buse_hw_Player.h
//  busegundogar_Gundogar_Buse_hw6
//
//  Created by Buse Gündoğar on 2.05.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//

#ifndef busegundogar_Gundogar_Buse_hw_Player_h
#define busegundogar_Gundogar_Buse_hw_Player_h
#include "busegundogar_Gundogar_Buse_hw_Board.h"

using namespace std;

template <class T>
class Player{
public:
    
    //Player(); 
    Player(Board<T> &);
    
    T openCard(int r, int c);
    bool validMove(int r, int c);
    void increaseNumberOfSuccess();
    int getNumberOfSuccess(); 
    
    
private:
    int score;
    Board<T> &gameBoard; 
    
};





#include "busegundogar_Gundogar_Buse_hw_Player.cpp"
#endif /* busegundogar_Gundogar_Buse_hw_Player_h */
