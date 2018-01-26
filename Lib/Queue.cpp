#include <iostream>
#include "Queue.h"

void error_msg(bool check){
if(!check) std::cout<<"Error\n";
}

bool Queue::empty(){
    return qu.is_empty();
}

int Queue::size(){
    return qu.size();
}

int& Queue::front(){
    return qu.top();
}

int& Queue::back(){
    return qu.back();
}

void Queue::push(int x){
    qu.add_rear(x);
}

void Queue::pop(){
    qu.remove_front();
}
