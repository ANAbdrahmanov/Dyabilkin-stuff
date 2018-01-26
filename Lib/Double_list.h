template<class T> class Double_list{
	
	struct Double_node{
		T val;
		Double_node* next;
		Double_node* prev;
		Double_node(){ }
		Double_node(T _val){
			val = _val;
		}
		Double_node(T _val, Double_node* _next, Double_node* _prev){
			val = _val;
			next = _next;
			prev = _prev;
		}
	};
	
	Double_node* tail;
	int sz;
	
	Double_node* merger(Double_node* l, Double_node* r, Double_node* last){
		Double_node* sorted;
		if(l->val < r->val){
			sorted = l;
			l = l->next;
		} else{
			sorted = r;
			r = r->next;
		}
		Double_node* sav = sorted;
		while(l != last && r != last){
			if(l->val < r->val){
				sorted->next = l;
				l = l->next;
			}
			else{
				sorted->next = r;
				r = r->next;
			}
			sorted = sorted->next;
		}
		sorted->next = l != last ? l : r;
		return sav;	
	}
	
	Double_node* sort_helper(Double_node* first, Double_node* last, int length){
		if(length > 1){
			int mid = length/2; 
			Double_node* premid = first;
			for(int i = 0; i < mid - 1; premid = premid->next, i++);
			Double_node* middle = premid->next;
			premid->next = last;
			return merger(sort_helper(first, last, mid), sort_helper(middle, last, length - mid), last);
		}
		else return first;
	}
	
public:
	Double_list(){
		tail = new Double_node;
		tail->next = tail;
		tail->prev = tail;
		sz = 0;
	}
	Double_list(T _val){
		tail = new Double_node;
		tail->next = new Double_node(_val,tail,tail);
		tail->prev = tail->next;
		sz = 1;
	}
	~Double_list(){
		Double_node* current = tail->next;
		while(current != tail){
			Double_node* temp = current;
			current = current->next;
			delete temp;
		}
		delete tail;
	}
	bool is_empty(){
		return sz == 0;
	}
	void add_front(T val){
		Double_node* new_node = new Double_node(val, tail->next, tail);
		tail->next->prev = new_node;
		tail->next = new_node;
		sz++;
	}
	void add_rear(T val){
		Double_node* new_node = new Double_node(val, tail, tail->prev);
		tail->prev->next = new_node;
		tail->prev = new_node;
		sz++;
	}
	T remove_front(){
		Double_node* temp = tail->next;
		tail->next = tail->next->next;
		temp->next->prev = tail;
		T val = temp->val;
		delete temp;
		sz--;
		return val;
	}
	T remove_rear(){
		Double_node* temp = tail->prev;
		tail->prev = tail->prev->prev;
		temp->prev->next = tail;
		T val = temp->val;
		delete temp;
		sz--;
		return val;
	}
//	void insert_after(T x, int n){
//		Double_node* current = tail->next;
//	    for(int i = 0; i<n; i++, current = current->next);
//	    Double_node* inserted = new Double_node(x,current->next,current);
//	    current->next->prev = inserted;
//	    current->next = inserted;
//	    sz++;
//	}
//	T remove(int n){
//	    Double_node* current = tail->next;
//	    for(int i = 0; i<n; i++, current = current->next);
//	    current->prev->next = current->next;
//	    current->next->prev = current->prev;
//	    int mem = current->val;
//	    delete current;
//	    sz--;
//	    return mem;
//	}
	bool find(T x){
		for(Double_node* current = tail->next; current != tail; current = current->next)
    		if(current->val == x)
    			return true;
    	return false;
	}
	T get_nth(int n){
		Double_node *current = tail->next;
    	for(int i = 0; i<n; i++, current = current->next);
		return current->val;
	}
	int size(){
		return sz;
	}
	void print(){
	    for(Double_node *current = tail->next; current != tail; current = current->next)
	    	std::cout<<current->val<<" ";
	    std::cout<<std::endl;
	}
	T& top(){
    	return tail->next->val;
	}
	T& back(){
	    return tail->prev->val;
	}
	void sort(){
		tail->next = sort_helper(tail->next, tail, sz);
		Double_node* current = tail;
		for(;current->next != tail; current = current->next){
			current->next->prev = current;
		}
		current->next->prev = current;
	}
	
	class iterator{
		Double_node* current;
		friend void Double_list<T>::insert(iterator,T);
		friend void Double_list<T>::remove(iterator);
	public: 
		iterator(Double_node* x){ current = x; }
		T& operator*(){ return current->val; }
		iterator& operator++(){ 
             current = current->next;
             return *this; 
        }
		iterator& operator--(){ 
            current = current->prev;
            return *this; 
        }
		bool operator==(iterator a){ return this->current == a.current; }
		bool operator!=(iterator a){ return this->current != a.current; }
		iterator operator+(int n){
			iterator cur = *this;
			for(int i = 0; i < n; i++){
				cur.current = cur.current->next;
			}
			return cur;
		}
		iterator operator-(int n){
			iterator cur = *this;
			for(int i = 0; i < n; i++){
				cur.current = cur.current->prev;
			}
			return cur;
		}
		iterator operator++(int){
			iterator temp = *this;
			current = current->next;
			return temp;
		}
		iterator operator--(int){
			iterator temp = *this;
			current = current->prev;
			return temp;
		}
		int operator-(iterator a){
			int range = 0;
			while(a != *this){
				a++;
				range++;
			}
			return range;
		}
	};
	
	class reverse_iterator{
		Double_node* current;
	public:
		reverse_iterator(Double_node* x){ current = x; }
		T& operator*(){ return current->val; }
		reverse_iterator& operator++(){ 
             current = current->prev; 
             return *this; 
        }
		reverse_iterator& operator--(){ 
            current = current->next; 
            return *this; 
        }
		bool operator==(reverse_iterator a){ return this->current == a.current; }
		bool operator!=(reverse_iterator a){ return this->current != a.current; }
		reverse_iterator operator+(int n){
			reverse_iterator cur = *this;
			for(int i = 0; i < n; i++){
				cur.current = cur.current->prev;
			}
			return cur;
		}
		reverse_iterator operator-(int n){
			reverse_iterator cur = *this;
			for(int i = 0; i < n; i++){
				cur.current = cur.current->next;
			}
			return cur;
		}
		reverse_iterator operator++(int){
			reverse_iterator temp = *this;
			current = current->prev;
			return temp;
		}
		reverse_iterator operator--(int){
			reverse_iterator temp = *this;
			current = current->next;
			return temp;
		}
		int operator-(reverse_iterator a){
			int range = 0;
			while(a != *this){
				a--;
				range++;
			}
			return range;
		}
	};
	
	iterator begin(){ return iterator(tail->next); }
	iterator end(){ return iterator(tail); }
	reverse_iterator rbegin(){ return reverse_iterator(tail->prev); }
	reverse_iterator rend(){ return reverse_iterator(tail); }
	
	void insert(iterator it, T val){
		Double_node* inserted = new Double_node(val, it.current, it.current->prev);
	    it.current->prev->next = inserted;
	    it.current->prev = inserted;
		sz++;
	}
	void remove(iterator it){
		Double_node* to_delete = it.current;
		it++; //на случай если нужно итератор рабочим сохранить
		to_delete->prev->next = to_delete->next;
	    to_delete->next->prev = to_delete->prev;
	    delete to_delete;
	    sz--;
	}
};
