//
//  busegundogar_Gundogar_Buse_hw4_Stack.h
//  busegundogar_Gundogar_Buse_hw4
//
//  Created by Buse Gündoğar on 3.04.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//

#ifndef busegundogar_Gundogar_Buse_hw4_Stack_h
#define busegundogar_Gundogar_Buse_hw4_Stack_h

#include <iostream>
using namespace std;

//START: Taken and updated from QueenStack.h
struct Position{
    int row,col;
    Position::Position(int x = 0, int y = 0) : row(x), col(y){};
};

struct StackNode{
    char value; 
    
    Position pos;
    StackNode *next;
    StackNode::StackNode(int v = 0, Position p = Position(), StackNode *n = nullptr): value(v), pos(p), next(n){};
};
//END: Taken and updated from QueenStack.h



class DynStack{
private:
    StackNode *top;
    
public:

    DynStack();
    ~DynStack();
    void push(StackNode);
    void pop(StackNode&);
    bool isEmpty(void);
};


#endif /* busegundogar_Gundogar_Buse_hw4_Stack_h */
