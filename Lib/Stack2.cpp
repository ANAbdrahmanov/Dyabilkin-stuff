#include <iostream>
#include "Stack2.h"

void error_msg(bool check){
    if(!check) std::cout<<"Error\n";
}

Stack2::Stack2(int n){
    st = new int[n];
    Top = 0;
}

Stack2::~Stack2(){
    delete[] st;
}

void Stack2::push(int x){
    st[Top++] = x;
}

void Stack2::pop(){
    Top--;
}

int& Stack2::top(){
    return st[Top-1];
}

int Stack2::size(){
    return Top;
}

bool Stack2::empty(){
    return Top == 0;
}
