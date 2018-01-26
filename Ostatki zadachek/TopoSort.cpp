#include <iostream>
#include "Single_list.h"

using namespace std;

struct Cell{
	int item;
	int parents;
	Single_list<Cell*> childs;
	Cell(int i, int p, Single_list<Cell*> c){
		item = i;
		parents = p;
		childs = c;
	}
};

void Toposort(int* a, int* b, int n){
	Cell* first = new Cell(a[0],0,Single_list<Cell*>());
	Single_list<Cell*> graph(first);
	for(int i = 0; i < n; i++){
		Single_list<Cell*>::iterator par = graph.begin();
		for(; par != graph.end() && (*par)->item != a[i]; par++);
		if(par == graph.end()){
			Cell* temp = new Cell(a[i],0,Single_list<Cell*>());
			graph.add_front(temp);
			par = graph.begin();
		}
		Single_list<Cell*>::iterator ch = graph.begin();
		for(; ch != graph.end() && (*ch)->item != b[i]; ch++);
		if(ch == graph.end()){
			Cell* temp = new Cell(b[i],1,Single_list<Cell*>());
			graph.add_front(temp);
			ch = graph.begin();
		}
		else{
			(*ch)->parents++;
		}
		(*par)->childs.add_front(*ch);
	}
	
	int size = graph.size();
	int* res = new int[size];
	Single_list<int> heads;
	for(Single_list<Cell*>::iterator it = graph.begin(); it != graph.end(); it++){
		if((*it)->parents == 0){
			heads.add_front((*it)->item);
		}
	}
	for(int i = 0; i < size; i++){
		int current = heads.remove_front();
		for(Single_list<Cell*>::iterator it = graph.begin(); it != graph.end(); it++){
			if((*it)->item == current){
				(*it)->parents--;
				for(Single_list<Cell*>::iterator red = (*it)->childs.begin(); red != (*it)->childs.end(); red++){
					if((*red)->parents-- == 1){
						heads.add_front((*red)->item);
					}
				}
				break;
			}
		}
		res[i] = current;
	}
	for(int i = 0; i < size; i++){
		cout<<res[i]<<" ";
		graph.remove_front();
	}
	delete[] res;
}

int main(){
	int n;
	cin>>n;
	int* a = new int[n];
	for(int i = 0; i < n; i++){
		cin>>a[i];
	}
	int* b = new int[n];
	for(int i = 0; i < n; i++){
		cin>>b[i];
	}
	Toposort(a,b,n);
	delete[] a;
	delete[] b;
	return 0;
}
