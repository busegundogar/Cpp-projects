//
//  busegundogar_Gundogar_Buse_hw4
//
//  Created by Buse Gündoğar on 3.04.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "busegundogar_Gundogar_Buse_hw4_Stack.h"

using namespace std;

struct cellStruct{
    char num;
    bool boolFlag;
    
};

void clearStack(DynStack &stack){
    StackNode temp;
    
    while(!stack.isEmpty()){
        stack.pop(temp);
    }
}

bool isMatched(cellStruct **mat, int &row, int &col, char ch, int rowCheck, int colCheck){
    
    //Checking right mat[row][col+1].num == ch &&
    if(col + 1 < colCheck &&  mat[row][col+1].boolFlag == false){
        col++;
        return true;
    }
    else if(col + 1 < colCheck){
        mat[row][col+1].boolFlag = true;
    }

    //Checking down mat[row+1][col].num == ch &&
    if(row + 1 < rowCheck && mat[row+1][col].boolFlag == false){
        row++;
        return true;
    }
    else if(row + 1 < rowCheck){
        mat[row+1][col].boolFlag = true;
    }
    
    return false;
}

bool isUsed(DynStack&stack,int rowN,int colN){
    DynStack checkStck;
    StackNode node;
    bool check = false;
    
    while(!stack.isEmpty()){
        stack.pop(node);
        
        if(node.pos.row == rowN && node.pos.col == colN){
            check = true;
        }
        checkStck.push(node);
    }
    
    while(!checkStck.isEmpty()){
        checkStck.pop(node);
        stack.push(node);
    }
    
    return check;
}
bool searchIsDone(string searchStr, DynStack &theStack){
    
    DynStack checkStack;
    StackNode tmp;
    string checkStr = "";
    long int length = searchStr.length();
    
    
    while(!theStack.isEmpty()){
        
        theStack.pop(tmp);
        checkStack.push(tmp);
    }
    
    while(!checkStack.isEmpty()){
        checkStack.pop(tmp);
        checkStr += tmp.value;
        theStack.push(tmp);
    }
    
    for(int i = 0; i < length; i++){
        if(checkStr[i] != searchStr[i]){
            return false;
        }
    }
    
    return true;
}

void PrintResult(DynStack &theStack){
    
    DynStack reverseStack;
    string result = "";
    StackNode temp;
    
    while(!theStack.isEmpty()){
        theStack.pop(temp);
        reverseStack.push(temp);
    }
    
    while(!reverseStack.isEmpty()){
        reverseStack.pop(temp);
        cout << "(";
        cout << temp.pos.row << "," << temp.pos.col << ") ";
        theStack.push(temp);
    }
}

int StackSize(DynStack &stack){
    DynStack checkStack;
    StackNode temp;
    int count = 0;
    
    while(!stack.isEmpty()){
        stack.pop(temp);
        count++;
        checkStack.push(temp);
    }
    
    while(!checkStack.isEmpty()){
        checkStack.pop(temp);
        stack.push(temp);
    }
    return count;
}

int main() {
    
    int rows, cols;
    char ch;
    bool notFound = true;
    string filename, line, searchStr;
    
    cout << "Please enter the number of rows: ";
    cin >> rows;
    
    cout << "Please enter the number of cols: ";
    cin >> cols;
    
    cout << "Please enter the name of the input file that containts the matrix: ";
    cin >> filename;
    
    //Opening the file:
    ifstream input;
    input.open(filename.c_str());
    while(input.fail()){
        cin.clear();
        cout << "File cannot be opened.\nPlease enter the name of the input file again: ";
        cin >> filename;
        input.open(filename.c_str());
    }
    
    DynStack theStack;
    cellStruct **mat; //dynamic matrix to follow board
    
    //Creating the empty matrix
    mat = new cellStruct*[rows];
    for(int i = 0; i < rows; i++){
        mat[i] = new cellStruct[cols];
    }
    
    //Filling the dynamic matrix:
    for(int i = 0; i < rows;i++){
        getline(input,line);
        istringstream iss(line);
        
        for(int j = 0; j < cols;j++){
            iss >> ch;
            
            cellStruct newCell;
            newCell.boolFlag = false;
            newCell.num = ch;
            
            mat[i][j] = newCell;
        }
    }
    

    cout << "\nPlease enter a string of bits to search (CTRL+Z to quit): ";
    
    ch = ' ';
    int row = 0, col = 0, size = 0;
    
    
    while(cin >> searchStr){  

        //Clearing the flags for every input.
        for(int i = 0; i < rows;i++){
            for(int j = 0; j < cols;j++){
                mat[i][j].boolFlag = false;
            }
        }

        clearStack(theStack);
        notFound = true;
        row = 0;
        col = 0;
        
        if(searchStr.at(0) != mat[0][0].num){ //If first char is not the one being searched, change the flag.
            mat[0][0].boolFlag = true;
            notFound = true;
        }
        
        while(mat[0][0].boolFlag == false && notFound == true){
            
            size = StackSize(theStack);
            
            if(mat[row][col].boolFlag == false && mat[row][col].num == searchStr.at(size)){
                
                if(!isUsed(theStack,row,col)){
                    theStack.push(StackNode(searchStr.at(size),Position(row,col)));
                }
                
                //If the last index is added, finish.
                if(searchIsDone(searchStr,theStack)){
                    notFound = false;
                    continue;
                }
                else{ //If there are more char's to be searched,
                    
                    //If it is matched, there are no changes.Else:
                    if(!isMatched(mat,row,col,searchStr.at(size+1),rows,cols)){
                        StackNode popTemp;
                        mat[row][col].boolFlag = true;
                        theStack.pop(popTemp); //Popping the true flagged element.
                        
                        //Changing the row and col values to the previous one.
                        theStack.pop(popTemp);
                        row = popTemp.pos.row;
                        col = popTemp.pos.col;
                        //theStack.push(popTemp); //??????
                    }
                }
            }
            else if(mat[row][col].boolFlag == true){
                StackNode popTemp3;
                mat[row][col].boolFlag = true;
                
                //Changing the row and col values to the previous one.
                theStack.pop(popTemp3);
                row = popTemp3.pos.row;
                col = popTemp3.pos.col;
            }
            else if(mat[row][col].num != searchStr.at(size)){
                mat[row][col].boolFlag = true;
                StackNode popTemp2;

                //Changing the row and col values to the previous one.
                theStack.pop(popTemp2);
                row = popTemp2.pos.row;
                col = popTemp2.pos.col;
            }
        }
            

        if(notFound){
            cout << "The bit string " << searchStr << " could not be found.\n";
        }
        else{
            cout << "The bit string " << searchStr << " is found following these cells: \n";
            PrintResult(theStack);
        }
        cout << "\nPlease enter a string of bits to search (CTRL+Z to quit): ";
    }
    
    cout << "\nProgram ended successfully!" << endl;
    
    //Deleting the dynamic matrix
    for(int i = 0; i < rows; i++){
        delete[] mat[i];
    }
    delete[] mat;
    
    
    input.close();
    return 0;
}
