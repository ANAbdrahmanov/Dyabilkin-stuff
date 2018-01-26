#include "Single_list.h"

class Stack{
	Single_list st;
public:
	void push(int);
	void pop();
	int& top();
	int size();
	bool empty();
	Stack(){}
	~Stack(){}
};

void error_msg(bool);
