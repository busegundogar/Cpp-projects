//
//  busegundogar_Gundogar_Buse_hw_Board.cpp
//  busegundogar_Gundogar_Buse_hw6
//
//  Created by Buse Gündoğar on 2.05.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "busegundogar_Gundogar_Buse_hw_Board.h"


//template <class T>
//Board<T>::Board(){
    //?? 
    //rowNum = 0;
    //colNum = 0;
//}

template <class T>
Board<T>::Board(int rows, int cols){
    boardMat = new Card<T>*[rows];
    
    //Filling the rows
    for(int i = 0; i < rows; i++){
        boardMat[i] = new Card<T>[cols];
    }
    
    rowNum = rows;
    colNum = cols;
    
}

template <class T>
Board<T>::~Board(){
    
    for(int i = 0; i < rowNum; i++){
        delete[] boardMat[i];
    }
    delete[] boardMat;
}

  

template <class T>
void Board<T>::readBoardFromFile(ifstream& input){
 
    string line;
    T temp;
                            
    for(int i = 0; i < rowNum; i++){
        
        getline(input,line);
        stringstream ss(line);
        
        for(int j = 0; j < colNum; j++){ //This loop takes the templated element to board
            ss >> temp;
            Card<T> tempCard;
            tempCard.face = temp;
            tempCard.status = false;

            boardMat[i][j] = tempCard;
        }
    }
    
}


template <class T>
int Board<T>::getColumn(){
    return colNum;
}
 
template <class T>
int Board<T>::getRow(){
    return rowNum;
}

template <class T>
void Board<T>::displayBoard(){
    
    for(int i = 0; i < rowNum; i++){
        
        for(int j = 0; j < colNum; j++){
            
            if( boardMat[i][j].status == false ){
                cout << "X ";
            }
            else{
                cout << boardMat[i][j].face << " ";
            }
        }
        cout << endl;
    }
}

template <class T>
void Board<T>::closeCard( int r, int c){
 
    boardMat[r][c].status = false;
}

template <class T>
void Board<T>::openCard( int r, int c){
 
    boardMat[r][c].status = true;
}

template <class T>
T Board<T>::getFace(int r, int c){
 
    return boardMat[r][c].face;
}

template <class T>
bool Board<T>::openCheck(int r, int c){ 
    if(boardMat[r][c].status == true){
        return true;
    }
    return false;
}



