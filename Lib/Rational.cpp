#include <iostream>
#include "Rational.h"

int Euclid(int A, int B){
	while (B) {
		A %= B;
		swap (A, B);
	}
	return A;
}

Rational operator/(int a, Rational b){
	return Rational(a*b.getZNT(), b.getCHS());
}

Rational operator*(int a, Rational b){
	return Rational(a*b.getCHS(), b.getZNT());
}

Rational operator+(int a, Rational b){
	return Rational(a*b.getZNT() + b.getCHS(), b.getZNT());
}

Rational operator-(int a, Rational b){
	return Rational(a*b.getZNT() - b.getCHS(), b.getZNT());
}

ostream& operator<<(ostream& c, Rational a){
	c<<a.getCHS();
	if(a.getZNT() != 1)
		c<<'/'<<a.getZNT();
	return c;
}

istream& operator>>(istream& c, Rational& a){
	int ch;
	int zn;
	c>>ch>>zn;
	a = Rational(ch,zn);
	return c;
}

Rational::Rational(int C){
    chs = C;
    znt = 1; 
}

Rational::Rational(int C, int Z){
    if(Z < 0){
        Z=-Z;
        C=-C;          
    }                   
    int nod = Euclid(C<0?-C:C, Z);
    if(nod == 1){
        chs = C;
        znt = Z;
    }
    else{
        chs = C/nod;
        znt = Z/nod;
    }
}

Rational Rational::operator+(Rational b){
	return Rational(chs*b.znt + b.chs*znt, znt*b.znt);;
}

Rational Rational::operator-(Rational b){
	return Rational(chs*b.znt - b.chs*znt, znt*b.znt);
}

Rational Rational::operator*(Rational b){
	return Rational(chs*b.chs, znt*b.znt);
}

Rational Rational::operator/(Rational b){
	return Rational(chs*b.znt, znt*b.chs);
}

bool Rational::operator<(Rational b){
	return chs*b.znt < znt*b.chs;
}

bool Rational::operator>(Rational b){
	return chs*b.znt > znt*b.chs;
}

bool Rational::operator<=(Rational b){
	return chs*b.znt <= znt*b.chs;
}

bool Rational::operator>=(Rational b){
	return chs*b.znt >= znt*b.chs;
}

bool Rational::operator==(Rational b){
	return chs*b.znt == znt*b.chs;
}

bool Rational::operator!=(Rational b){
	return chs*b.znt != znt*b.chs;
}

Rational& Rational::operator+=(Rational b){
	return *this=*this+b;
}

Rational& Rational::operator-=(Rational b){
	return *this=*this-b;
}

Rational& Rational::operator*=(Rational b){
    return *this=*this*b;
}

Rational& Rational::operator/=(Rational b){
    return *this=*this/b;
}
