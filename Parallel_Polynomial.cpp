#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

DWORD WINAPI ThreadFunction(LPVOID param);

const int n = 2;
const int m = 2;
int a[n+1];
int b[m+1];
int c[m+n+1];

int main() {
	int polSize = m+n+1;
	for(int i = 0; i < n+1; i++){
		cin>>a[i];
	}
	for(int i = 0; i < m+1; i++){
		cin>>b[i];
	}
	
    HANDLE* hThreadArray = new HANDLE[polSize];
    for(int i = 0; i < polSize; i++){
    	int* k = new int(i);
        hThreadArray[i] = CreateThread( 0, 0, ThreadFunction, (LPVOID)k, 0, 0 );	
    }
    
    WaitForMultipleObjects(polSize, hThreadArray, TRUE, INFINITE);

    for(int i = 0; i < polSize; i++){
        CloseHandle(hThreadArray[i]);
        cout<<c[i]<<" ";
    }
    delete[] hThreadArray;
	return 0;
}

DWORD WINAPI ThreadFunction(LPVOID param) { 
	int k = *((int*)param);
	int coef = 0;
	int upEdge = min(k,n) + 1; 			// +1, чтобы не писать <= строчкой ниже
	for(int j = max(0,k-m); j < upEdge; j++){
		coef += (a[j] * b[k-j]);
	}
	c[k] = coef;
	delete (int*)param;
    return 0; 
} 
