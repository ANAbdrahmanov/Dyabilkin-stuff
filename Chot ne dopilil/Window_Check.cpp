#include <windows.h>
#include <algorithm>

using namespace std;

class Window{
	
};

struct Point{ 
	int x,y;
	Point(){}
	Point(int _x, int _y){
		x = _x;
		y = _y;
	}
};

class ConsoleWindow : public Window{
	HANDLE hConsole;
	int width;
	int height;
public:
	ConsoleWindow(int w, int h){
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		width = w;
		height = h;
	}
	void plot(int x, int y){
		if(x < width && y < height){
			COORD Pos; Pos.X = x; Pos.Y = y;
			SetConsoleCursorPosition(hConsole, Pos);
			WriteConsoleA(hConsole,"*",1,0,0);
		}
	}
	void plot(Point P){
		if( P.x < width && P.y < height){
			COORD Pos; Pos.X = P.x; Pos.Y = P.y;
			SetConsoleCursorPosition(hConsole, Pos);
			WriteConsoleA(hConsole,"*",1,0,0);
		}
	}
	~ConsoleWindow(){
		COORD Pos; Pos.X = 0; Pos.Y = height;
		SetConsoleCursorPosition(hConsole, Pos);
		CloseHandle(hConsole);
	}
};

class Shape{
public:
	virtual void draw(ConsoleWindow* w) = 0;
};

class Dot : public Shape {
	Point dot;
public:	
	Dot(int x, int y){
		dot.x = x;
		dot.y = y;
	}
	Dot(Point x){
		dot = x;
	}
	void draw(ConsoleWindow* w){
		w->plot(dot);
	}
};

class Rectangle_ : public Shape {
	int up;
	int left;
	int right;
	int down;
public:
	Rectangle_(){}
	Rectangle_(Point p1, Point p2){
		up = p1.y;
		left = p1.x;
		right = p2.x;
		down = p2.y;
	}
	void draw(ConsoleWindow* w){
		for(int i = left; i <= right; i++){
			w->plot(i,up);
			w->plot(i,down);
		}
		for(int i = up + 1; i < down; i++){
			w->plot(left,i);
			w->plot(right,i);
		}
	}
};

class Line : public Shape {
	Point a;
	Point b;
public:
	Line(){}
	Line(Point A, Point B){
		a = A;
		b = B;
	}
	void draw(ConsoleWindow* w){
		Point B(b.x - a.x, a.y - b.y);
		bool xIsChanged = false;
		bool yIsChanged = false;
		bool octIsChanged = false;
		if(B.x < 0){
			B.x = -B.x;
			xIsChanged = true;
		}
		if(B.y < 0){
			B.y = -B.y;
			yIsChanged = true;
		}
		if(B.x < B.y){
			swap(B.x,B.y);
			octIsChanged = true;
		}
		int e = 2*B.y - B.x;
		int deleS = 2*B.y;
		int deleD = 2*B.y - 2*B.x;
		int x = 0, y = 0;
		while(x < B.x){
			int X = x, Y = y;
			if(octIsChanged) { swap(X,Y); }
			X = xIsChanged? -X : X;
			Y = yIsChanged? -Y : Y;
			X += a.x;
			Y = -(Y-a.y);
			w->plot(X,Y);
			
			if(e > 0){
				x++;
				y++;
				e += deleD;
			}
			else{
				x++;
				e += deleS;
			}
		}
		w->plot(b);
	}
};

class Ellipse_ : public Shape {
	Point left;
	Point right;
public:
	Ellipse_(){}
	Ellipse_(Point a, Point b){
		left = a;
		right = b;
	}
	void draw(ConsoleWindow* w){
		int b = (right.y - left.y + 1)/2;
		int a = (right.x - left.x + 1)/2;
		int x = 0;
		int y = b;
		int del = (4*b*b*(x+1)*(x+1)) + (a*a*(2*y-1)*(2*y-1)) - (4*a*a*b*b);
		while(2*b*b*(x+1) < a*a*(2*y - 1)){
			w->plot(x + a + left.x + 1, - y + left.y + b);
			w->plot(-x + a + left.x + 1, - y + left.y + b);
			w->plot(x + a + left.x + 1, y + left.y + b);
			w->plot(-x + a + left.x + 1, y + left.y + b);
			if(del < 0){
				del += (4*b*b*(2*x+3));
				x++;
			} 
			else{
				del += (4*b*b*(2*x+3) - 8*a*a*(y-1));
				x++;
				y--;
			}
		}
		del = b*b*(2*x+1)*(2*x+1) + 4*a*a*(y-1)*(y-1) - 4*a*a*b*b;
		while(y>0){
			w->plot(x + a + left.x + 1, - y + left.y + b);
			w->plot(-x + a + left.x + 1, - y + left.y + b);
			w->plot(x + a + left.x + 1, y + left.y + b);
			w->plot(-x + a + left.x + 1, y + left.y + b);
			if(del < 0){
				del += ((x+1)*b*b*8 + (-2*y+3)*4*a*a);
				y--;
				x++;
			} 
			else{
				del += ((-2*y+3)*4*a*a);
				y--;
			}
		}

		w->plot(x + a + left.x + 1, - y + left.y + b);
		w->plot(-x + a + left.x + 1, - y + left.y + b);
		w->plot(x + a + left.x + 1, y + left.y + b);
		w->plot(-x + a + left.x + 1, y + left.y + b);
	}
};

class Triangle : public Shape {
	Line a;
	Line b;
	Line c;
public:
	Triangle(Point A, Point B, Point C){
		a = Line(B,A);
		b = Line(B,C);
		c = Line(A,C);
	}
	void draw(ConsoleWindow* w){
		a.draw(w);
		b.draw(w);
		c.draw(w);
	}
};

class Square : public Shape {
	Rectangle_ sq;
public: 
	Square(Point c, int r){
		sq = Rectangle_(Point(c.x,c.y), Point(c.x+r,c.y+r));
	}
	void draw(ConsoleWindow* w){
		sq.draw(w);
	}
};

class Circle : public Shape {
	Ellipse_ cr;
public:
	Circle(Point cnt, int rad){
		cr = Ellipse_(Point(cnt.x - rad, cnt.y - rad), Point(cnt.x + rad, cnt.y + rad));
	}
	void draw(ConsoleWindow* w){
		cr.draw(w);
	}
};

int main() {
	ConsoleWindow w(50,50);
//	Ellipse_ l(Point(4,4),Point(20,20));
//	Triangle t(Point(49,1),Point(1,20),Point(20,30));
//	Square s(Point(6,6),20);
	Circle c(Point(10,10),5);
//	l.draw(&w);
//	t.draw(&w);
//	s.draw(&w);
	c.draw(&w);
	return 0;
}
