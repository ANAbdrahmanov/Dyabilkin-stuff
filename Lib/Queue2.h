class Queue2{
    int* qu;
    int head, sze, max_size;
public:
    Queue2(int);
    ~Queue2();
    bool empty();
    int size();
    int& front();
    int& back();
    void push(int);
    void pop();
};

void error_msg(bool);
