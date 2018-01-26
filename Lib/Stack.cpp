#include "Stack.h"
#include <iostream>

void error_msg(bool check){
     if(!check) 
           std::cout<<"Error\n";
}

void Stack::push(int x){
     st.add_front(x);
}

void Stack::pop(){
     st.remove_front();
}

int& Stack::top(){
     return st.top();
}

int Stack::size(){
     return st.size();
}

bool Stack::empty(){
     return st.is_empty();
}
