using namespace std;

class Rational{
    int chs;
    int znt;
public:
    Rational(){
        chs = 0;
        znt = 1;
    }
    Rational(int);
    Rational(int,int);
    Rational operator-(){
        return Rational(-chs,znt);
	}
	Rational operator+(Rational);
	Rational operator-(Rational);
	Rational operator*(Rational);
	Rational operator/(Rational);
	bool operator>(Rational);
	bool operator<(Rational);
	bool operator<=(Rational);
	bool operator>=(Rational);
	bool operator==(Rational);
	bool operator!=(Rational);
	Rational& operator+=(Rational);
    Rational& operator-=(Rational);
	Rational& operator*=(Rational);
	Rational& operator/=(Rational);
	int getCHS(){
        return chs;
    }
    int getZNT(){
        return znt;
    }
};

Rational operator+(int, Rational);
Rational operator-(int, Rational);
Rational operator*(int, Rational);
Rational operator/(int, Rational);
ostream& operator<<(ostream&, Rational);
istream& operator>>(istream&, Rational&);
