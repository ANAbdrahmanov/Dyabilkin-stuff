#include "Double_list.h"

class Queue{
    Double_list qu;
public:
    Queue(){}
    ~Queue(){}
    bool empty();
    int size();
    int& front();
    int& back();
    void push(int);
    void pop();
};

void error_msg(bool);
