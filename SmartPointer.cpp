#include <iostream>

struct Foo {
	Foo() { std::cout << "Foo::Foo\n"; }
	~Foo() { std::cout << "Foo::~Foo\n"; }
	void bar() { std::cout << "Foo::bar\n"; }
};

void f(const Foo &foo)
{
	std::cout << "f(const Foo&)\n";
}

template<class T> class Smart_ptr {
	T* ptr;
public:
	Smart_ptr() : ptr(){}
	Smart_ptr(T* value) {
		ptr = value;
	}
	~Smart_ptr() {
		delete ptr;
	}
	T& operator*() {
		return *ptr;
	}
	T* operator->(){
		return ptr;
	}
};

int main() {
	{
	Smart_ptr<Foo> pointer(new Foo());
	pointer->bar();
	}
	system("pause");
	return 0;
}