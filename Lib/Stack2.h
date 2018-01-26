class Stack2{
    int* st;
    int Top;
public:
    void push(int);
    void pop();
    int& top();
    int size();
    bool empty();
    Stack2(int);
    ~Stack2();
};

void error_msg(bool);
