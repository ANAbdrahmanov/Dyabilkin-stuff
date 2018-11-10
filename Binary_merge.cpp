#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

DWORD WINAPI ThreadFunctionA(LPVOID param);
DWORD WINAPI ThreadFunctionB(LPVOID param);

const int n = 101;
const int m = 205;
int* a;
int* b;
int c[n+m];

int main() {
	srand(GetTickCount());
	int* T = new int[n+m];
	for(int i = 0; i < n + m; i++){
		T[i] = i+1;
	}
	random_shuffle(T,T+m+n);
	a = T; 
	b = T+n;
	sort(a, a+n);
	sort(b, b+m);
	
	for(int i = 0; i < m+n; i++){
		cout<<T[i]<<" ";
	}
	cout<<endl<<endl;
	
	HANDLE* hThreadArrayA = new HANDLE[n];
	HANDLE* hThreadArrayB = new HANDLE[m];
	for(int i = 0; i < n; i++){
		int* k = new int(i);
		hThreadArrayA[i] = CreateThread( 0, 0, ThreadFunctionA, (LPVOID)k, 0, 0 );	
	}
	for(int i = 0; i < m; i++){
		int* k = new int(i);
		hThreadArrayB[i] = CreateThread( 0, 0, ThreadFunctionB, (LPVOID)k, 0, 0 );	
	}
	
	WaitForMultipleObjects(n,hThreadArrayA, TRUE, INFINITE);
	WaitForMultipleObjects(m,hThreadArrayB, TRUE, INFINITE);
	
	for(int i = 0; i < n; i++){
		CloseHandle(hThreadArrayA[i]);
		cout<<c[i]<<" ";
	}
	for(int i = 0; i < m; i++){
		CloseHandle(hThreadArrayB[i]);
		cout<<c[i+n]<<" ";
	}
	delete[] T;
	delete[] hThreadArrayA;
	delete[] hThreadArrayB;
	return 0;
}

DWORD WINAPI ThreadFunctionA(LPVOID param){
	int i = *((int*)param);
	int R;
	if(a[i] < b[0]) R = i;
	else
		if(a[i] > b[m-1]) R = i + m;
		else{
			int l = 0, r = m;
			while(l<r){
				int mid = (l+r)/2;
				if(a[i] < b[mid]) 
					r = mid;
				else 
					l = mid + 1;
			}
			R = l + i;
		}
	c[R] = a[i];
	delete (int*)param;
	return 0;
}

DWORD WINAPI ThreadFunctionB(LPVOID param){
	int i = *((int*)param);
	int R;
	if(b[i] < a[0]) R = i;
	else
		if(b[i] > a[n-1]) R = i + n;
		else{
			int l = 0, r = n;
			while(l<r){
				int mid = (l+r)/2;
				if(b[i] < a[mid]) 
					r = mid;
				else 
					l = mid + 1;
			}
			R = l + i;
		}
	c[R] = b[i];
	delete (int*)param;
	return 0;
}
