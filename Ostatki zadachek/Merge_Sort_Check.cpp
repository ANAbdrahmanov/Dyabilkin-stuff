#include <iostream>
#include <algorithm>
#include "Single_list.h"

using namespace std;

template<class Value> class Greater{
public:
	bool operator()(Value& x, Value& y){
		return y<x;	
	}
};

template<class Value, class ForwardIterator> void merge(ForwardIterator first,  ForwardIterator mid, ForwardIterator last, Value* buf){
	ForwardIterator l = first;
	ForwardIterator r = mid;
	int i = 0;
	while(l != mid && r != last){
			if(*l < *r){
				buf[i++] = *l++;
			}
			else{
				buf[i++] = *r++;
			}
	}
	while(l != mid){
		buf[i++] = *l++;
	}
	while(r != last){
		buf[i++] = *r++;
	}
	ForwardIterator cur = first;
	for(int i = 0; cur != last; i++){
		*cur = buf[i];
		cur++;
	}
}

template<class Value, class ForwardIterator, class StrictWeakOrdering> void merge(ForwardIterator first,  ForwardIterator mid, ForwardIterator last, Value* buf, StrictWeakOrdering comp){
	ForwardIterator l = first;
	ForwardIterator r = mid;
	int i = 0;
	while(l != mid && r != last){
			if(comp(*l,*r)){
				buf[i++] = *l++;
			}
			else{
				buf[i++] = *r++;
			}
	}
	while(l != mid){
		buf[i++] = *l++;
	}
	while(r != last){
		buf[i++] = *r++;
	}
	ForwardIterator cur = first;
	for(int i = 0; cur != last; i++){
		*cur = buf[i];
		cur++;
	}
}

template<class Value, class ForwardIterator> void sort_helper(ForwardIterator first, ForwardIterator last, Value* buf, int length){
	if(length > 1){
		int mid = length/2;
		ForwardIterator middle = first + mid;
		sort_helper<Value>(first, middle, buf, mid);
		sort_helper<Value>(middle, last, buf, length - mid);
		merge<Value>(first, middle, last, buf);
	}
}

template<class Value, class ForwardIterator> void merge_sort(ForwardIterator first, ForwardIterator last){
    int length = last - first;
    Value* buf = new Value[length];
    sort_helper<Value>(first, last, buf, length);
    delete[] buf;
}

template<class Value, class ForwardIterator, class StrictWeakOrdering> void sort_helper(ForwardIterator first, ForwardIterator last, Value* buf, int length, StrictWeakOrdering comp){
	if(length >= 2){
		int mid = length/2;
		ForwardIterator middle = first + mid;
		sort_helper<Value>(first, middle, buf, mid, comp);
		sort_helper<Value>(middle, last, buf, length - mid, comp);
		merge<Value>(first, middle, last, buf, comp);
	}
}

template<class Value, class ForwardIterator, class StrictWeakOrdering> void merge_sort(ForwardIterator first, ForwardIterator last, StrictWeakOrdering comp){
    int length = last - first;
    Value* buf = new Value[length];
    sort_helper<Value>(first, last, buf, length, comp);
    delete[] buf;
}


int main() {
	int n;
	cin>>n;
//	int* a = new int[n];
//	for(int i = 0; i<n;i++){
//		a[i] = i + 1;
//	}
//	random_shuffle(a,a+n);
//	for(int i = 0; i<n;i++){
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;
//	merge_sort<int>(a,a+n);
//	for(int i = 0; i<n;i++){
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;
//	merge_sort<int>(a,a+n,Greater<int>());
//	for(int i = 0; i<n;i++){
//		cout<<a[i]<<" ";
//	}
//	delete[] a;
	Single_list<int> list;
	for(int i = 0; i<n;i++){
		int k;
		cin>>k;
		list.add_front(k);
	}
	cout<<endl;
	Single_list<int>::iterator p = list.begin();
	merge_sort<int>(list.begin(),list.end());
	print_slist<int>(list);
	merge_sort<int>(list.begin(), list.end(), Greater<int>());
	cout<<endl;
	print_slist<int>(list);
	cout<<endl;
	//list.sort();
	//print_slist<int>(list);
//	system("pause");
	return 0;
}
