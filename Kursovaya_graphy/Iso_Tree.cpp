#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <ctime>

using namespace std;

struct Bracket{    //структура для определения ячеек кода, вида ((...),...)
	bool pure_;     //на случай, если текущая скобка - висячая вершина
	int size_;
	Bracket* tuple_;
public:
	Bracket(){}
	Bracket(int n, Bracket* data){
		if(data == 0){
			pure_ = 1;
			tuple_ = 0;
			size_ = 1;
		}
		else{
			tuple_ = data;
			pure_ = 0;
			size_ = n;
		}
	}
	Bracket operator[](int index){              
		return tuple_[index];
	}
};

bool** CreateTree(int n) { 
	bool** a = new bool*[n]; 
	srand(time(NULL)); 
	int j; 
	a[0] = new bool[n]; 
	for (int k = 0; k < n; a[0][k++] = 0); 
	for (int i = 1; i < n; i++) { 
		a[i] = new bool[n]; 
		for (int k = 0; k < n; a[i][k++] = 0); 
		j = rand() % i; 
		a[i][j] = 1; 
		a[j][i] = 1; 
	}
	return a; 
};

bool Less(Bracket a, Bracket b){
		if(a.pure_ && !b.pure_){
			return true;
		} else if((!a.pure_ && b.pure_) || (a.pure_ && b.pure_)){
			return false;
		} else if(a.size_ == b.size_){ 
			int i = 0;
			for(; (i < a.size_) && !(Less(a[i], b[i]) || Less(b[i],a[i])); i++);  //проверка на равенство содержимого
			if(i == a.size_)
				return false;
			else 
				return Less(a[i],b[i]);
		} else 
			return a.size_ < b.size_;
}

int center(int n, bool**& tree, bool& im){
	bool** copy = new bool*[n];
	for(int i = 0; i < n; i++){       //копируем дерево
		copy[i] = new bool[n];
		for(int j = 0; j < n; j++){
			copy[i][j] = tree[i][j];
		}
	} 
	list< pair<int,bool> > leaf;        // список помеченных невисячих вершин
	for(int i = 0; i < n; i++){
		leaf.push_front(pair<int,bool>(i,false));
	}
	while(leaf.size() > 2){
		for(list< pair<int,bool> >::iterator it = leaf.begin(); it != leaf.end(); it++){  //помечаем висячие вершины
			int k = 0;
			for(list< pair<int,bool> >::iterator jt = leaf.begin();  jt != leaf.end(); jt++){
				if(copy[(*it).first][(*jt).first])
					k++;
			}
			if(k == 1){
				(*it).second = true;
			}
		}
		for(list< pair<int,bool> >::iterator it = leaf.begin(); it != leaf.end();){  //удаляем помеченные
			if((*it).second){
				pair<int,bool> p((*it).first,true);
				it++;
				leaf.remove(p);
			}
			else it++;
		}
	}
	if(leaf.size() == 2){  //запоминаем искуственный ли центр и возвращаем номер центральной вершины
		im = true;
		bool** newTree = new bool*[n+1];
		for(int i = 0; i < n; i++){
			newTree[i] = new bool[n+1];
			for(int j = 0; j < n; j++){
				newTree[i][j] = tree[i][j];
			}
			newTree[i][n] = ((i == leaf.back().first)||(i == leaf.front().first))? 1:0;
		}
		newTree[n] = new bool[n+1];
		for(int i = 0; i < n+1; i++){
			newTree[n][i] = ((i == leaf.back().first)||(i == leaf.front().first))? 1:0;
		}
		for(int i = 0; i < n; i++){    //очищаем память заменяем матрицу смежности на новую
			delete[] tree[i];
		}
		newTree[leaf.back().first][leaf.front().first] = 0;   //разрываем связь между вершинами, бывшими инцидентными центральному ребру
		newTree[leaf.front().first][leaf.back().first] = 0;
		tree = newTree;
		return n;
	}
	else {
		im = false;
		return leaf.front().first;
	}
} 

class IsoTree{
	bool imaginary_;       //если центр искусственно добавленный
	Bracket tree_;
	
	Bracket Build(int n, bool** tree, int x){ 		 //строим структуру будущего дерева
		int count = 0;
		for(int i = 0; i < n; i++)
			if(tree[x][i])
				count++;
		if(count == 0) return Bracket(1,0);
		Bracket* tuple = new Bracket[count];
		count = 0;
		for(int i = 0; i < n; i++){
			if(tree[x][i]){
				tree[x][i] = 0;
				tree[i][x] = 0;
				tuple[count] = Build(n,tree,i);
				count++;
			}
		}
		return Bracket(count,tuple);
	}
	
	void code(string& _code, Bracket cell){          //кодируем имеющуюся структуру
		if(cell.pure_) _code+= "0";
		else{
			_code += "(";
			for(int i = 0; i < cell.size_; i++){
				code(_code,cell[i]);
				if(i < (cell.size_ - 1)) _code += ",";
			}
			_code+=")";
		}
	}
	void Bracket_sort(Bracket* tree, int size){                 //сортируем каждую подструктуру в структуре,а затем ее и саму
		if(tree == 0) return;
		else{
			for(int i = 0; i < size; i++){
				Bracket_sort(tree[i].tuple_,tree[i].size_);
			}
			sort(tree, tree + size, Less);
		}
	}
public:
	string treeCode_;
	IsoTree(int n, bool** treeMat){
		int root = center(n,treeMat,imaginary_);
		if(imaginary_) n++;
		tree_ = Build(n,treeMat,root);
		Bracket_sort(tree_.tuple_, tree_.size_);
		treeCode_ = imaginary_ == true?"-":"+";
		code(treeCode_, tree_);
	}
};

int main() {      
	int n; cin>>n;
	bool** a = CreateTree(n);
	IsoTree first(n,a);
	cout<<first.treeCode_;
	return 0;
}
