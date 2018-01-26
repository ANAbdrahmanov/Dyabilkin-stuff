template<class T> class Single_list{
	struct Single_node{
	    Single_node *next;
	    T val;
	    Single_node(){}
	    Single_node(T x){
		    val= x;
		}
	    Single_node(T x, Single_node *y){
		    val = x;
		    next = y;
		}
	};
    Single_node *head;
    Single_node *tail;
    void Delete(){
	    while(head != tail){
	        Single_node *temp;
	        temp = head->next;
	        delete head;
	        head = temp;
	    }
	}
	void merger(Single_node*& first, Single_node* r, Single_node* last){
		Single_node* l = first;
		Single_node* sorted;
		if(l->val < r->val){
			sorted = l;
			l = l->next;
		} else{
			sorted = r;
			r = r->next;
		}
		first = sorted;
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
	}
	void sort_helper(Single_node*& first, Single_node* last, int length){
		if(length > 1){
			int mid = length/2; 
			Single_node* premid = first;
			for(int i = 0; i < mid - 1; premid = premid->next, i++);
			Single_node* middle = premid->next;
			premid->next = last;
			sort_helper(first, last, mid);
			sort_helper(middle, last, length - mid);
			merger(first, middle, last);
		}
	}
public:
    Single_list(){
	    head = new Single_node;
	    tail = head;
	}
    Single_list(T x){
	    tail = new Single_node;
	    head = new Single_node(x);
	    head->next = tail;
	}
    Single_list(const Single_list& x){
		if(x.is_empty()){
			head = new Single_node;
	    	tail = head;
		}
		else{
			tail = new Single_node;
			head = new Single_node(x.top(), tail);
			Single_node* current = head;
			Single_node* x_current = x.head;
			while(x_current->next != x.tail){
				current->next = new Single_node(x_current->next->val, tail);
				current = current->next;
				x_current = x_current->next;
			}
		}
	}
    ~Single_list(){
	    this->Delete();
	    delete head;
	}
    Single_list& operator=(const Single_list& x){
		this->Delete();
		if(!x.is_empty()){
			head = new Single_node(x.top(), tail);
			Single_node* current = head;
			Single_node* x_current = x.head;
			while(x_current->next != x.tail){
				current->next = new Single_node(x_current->next->val, tail);
				current = current->next;
				x_current = x_current->next;
			}
		}
		return *this;
	}
    bool is_empty() const {
	    return head == tail;
	}
    void add_front(const T& new_node){
	    head = new Single_node(new_node,head);
	}
    T remove_front(){
	    T temp_val = head->val;
	    Single_node *temp_p = head;
	    head = head->next;
	    delete temp_p;
	    return temp_val;
	}
    bool find(T we_need) const {
	    Single_node *current = head;
	    while (current != tail)
	        if(current->val == we_need)
	            return true;
	        else current = current->next;
	    return false;
	};
    T get_nth(int n) const {
	    Single_node *current = head;
	    for(int i = 0; i<n; i++)
	        current = current->next;
	    return current->val;
	}
    int size() const {
	    Single_node *current = head;
	    int sz = 0;
	    while(current != tail){
	        current = current->next;
	        sz++;
	    }
	    return sz;
	}
    T& top() const {
	    return head->val;
	}
	void sort(){
		int l = iterator(tail) - iterator(head);
		sort_helper(head, tail, l);
	}
    class iterator{
		Single_node* current;
	public:
		iterator(Single_node* x){ current = x; }
		T& operator*(){ return current->val; }
		iterator& operator++(){ 
            current = current->next;
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
		iterator operator++(int){
			iterator temp = *this;
			current = current->next;
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
    iterator begin(){
		return iterator(head);
	}
    iterator end(){
		return iterator(tail);
	}
};

template<class T> void print_slist(Single_list<T>& ref){
    int n = ref.size();
    for(int i = 0; i<n; i++)
    	std::cout<<ref.get_nth(i)<<" ";
    std::cout<<std::endl;
}
