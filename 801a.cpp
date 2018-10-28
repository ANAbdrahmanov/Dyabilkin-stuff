#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string a;
	cin>>a;
	int sz = a.size();
	int vk_c = 0;
	bool combo = false;
	bool isV = a[0] == 'V'? true : false;
	if(!isV && sz > 1 && a[1] == 'K') combo = true; 
	for(int i = 1; i < sz - 1; i++){
		if(isV && a[i] == 'K') vk_c++;
		else if((isV && a[i] == a[i + 1] && a[i + 1] == 'V') || (!isV && a[i] == a[i + 1] && a[i + 1]== 'K')) combo = true;
		isV = a[i] == 'V'? true : false;
	}
	if(isV && sz > 1 && a[sz - 1] == 'V') combo = true;	
	if(isV && a[sz - 1] == 'K') vk_c++;
	if(combo) vk_c++;
	cout<<vk_c;
	return 0;
}
