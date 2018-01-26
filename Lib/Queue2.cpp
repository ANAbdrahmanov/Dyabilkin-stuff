#include "Queue2.h"
#include <iostream>

void error_msg(bool check){
     if(!check) 
            std::cout<<"Error\n";
}

Queue2::Queue2(int n){
    qu = new int[n];
    head = sze = 0;
    max_size = n;
}

Queue2::~Queue2(){
    delete qu;
}

bool Queue2::empty(){
    return sze == 0;
}

int Queue2::size(){
    return sze;
}

int& Queue2::front(){
    return qu[head];
}

int& Queue2::back(){
    return qu[(head + sze - 1) % max_size];
}

void Queue2::push(int x){
    qu[(head + sze++) % max_size] = x;
}

void Queue2::pop(){
    head = (head + 1) % max_size;
    sze--;
}
