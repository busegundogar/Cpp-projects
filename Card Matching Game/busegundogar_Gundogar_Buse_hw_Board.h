//
//  busegundogar_Gundogar_Buse_hw_Board.h
//  busegundogar_Gundogar_Buse_hw6
//
//  Created by Buse Gündoğar on 2.05.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//


#ifndef busegundogar_Gundogar_Buse_hw_Board_h
#define busegundogar_Gundogar_Buse_hw_Board_h

#include <string>
using namespace std;

template <class T>
struct Card{
    T face;
    bool status; //False = close,
                 //True = open
    
    //Default constructor
    Card(){
        status = false;
    }
    //Parametric constructor
    Card(T value): face(value), status(false){}

};

template <class T>
class Board{
public:
    //Board();
    ~Board();
    Board(int rows, int cols);
        
    void readBoardFromFile(ifstream&);
    void displayBoard();
    void closeCard( int rows,  int cols);
    void openCard( int rows,  int cols);
    int getRow();
    int getColumn();
    T getFace(int rows, int cols);
    bool openCheck(int rows, int cols);
    
private:
    
    Card<T> **boardMat;
    int rowNum;
    int colNum;
};


#include "busegundogar_Gundogar_Buse_hw_Board.cpp"
#endif /* busegundogar_Gundogar_Buse_hw_Board_h */
