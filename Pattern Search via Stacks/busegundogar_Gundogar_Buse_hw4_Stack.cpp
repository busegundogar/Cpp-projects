//
//  busegundogar_Gundogar_Buse_hw4_Stack.cpp
//  busegundogar_Gundogar_Buse_hw4
//
//  Created by Buse Gündoğar on 3.04.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//

#include <iostream>
#include "busegundogar_Gundogar_Buse_hw4_Stack.h"
using namespace std;

DynStack::DynStack(){
    top = nullptr;
}

DynStack::~DynStack(){
    
    while(top != nullptr){
        StackNode *temp = top->next;
        delete top;
        top = temp;
    }
}

//START: Taken and updated from QueenStack.cpp
void DynStack::push(StackNode n){
   
    StackNode *newNode = new StackNode(n.value,n.pos);
    
    if(isEmpty()){
        top = newNode;
        newNode->next = nullptr;
    }
    else{
        newNode->next = top;
        top = newNode;
    }
}

void DynStack::pop(StackNode &n){
    StackNode *temp;
    
    if(!isEmpty()){
        n.pos = top->pos;
        n.value = top->value;
        temp = top->next;
        delete top;
        top = temp;
    }
}

bool DynStack::isEmpty(void){
    
    if(top == nullptr){
        return true;
    }
    else{
        return false;
    }
}
//END: Taken and updated from QueenStack.cpp
