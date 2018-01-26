#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string a, b;
	cin>>a>>b;
	int sz = a.size();
	for(int i = 0; i < sz; i++){
		if( a[i] < b[i] ){
			cout<<-1;
			return 0;
		}
	}	
	cout<<b;
	return 0;
}
