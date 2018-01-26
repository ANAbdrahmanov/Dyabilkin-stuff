template<class T> class Binary_tree{
	struct Tree_node{
		T val;
		Tree_node* left;
		Tree_node* right;
		Tree_node* parent;
		Tree_node(T _val, Tree_node* l = 0, Tree_node* r = 0, Tree_node* p = 0){
			val = _val;
			left = l;
			right = r;
			parent = p;
		}
		Tree_node(Tree_node* l = 0, Tree_node* r = 0, Tree_node* p = 0){
			left = l;
			right = r;
			parent = p;
		}
	};
	
	Tree_node* root;

public:
	Binary_tree(){
		root = new Tree_node();	
	}
	Binary_tree(const T& val){
		root = new Tree_node();
		root->left = new Tree_node(val,0,0,root);
	}
	void Destruct(Tree_node* r){
	    if(r){
		    Destruct(r->left);
		    Destruct(r->right);
		    delete r;
    	}
    }
    ~Binary_tree(){
    	Destruct(root);
	}
	bool add(T val){
		if(root->left == 0){
			root->left = new Tree_node(val,0,0,root);
			return true;
		}
		Tree_node* current = root->left;
		while(true){
			if(val < current->val)
            	if(current->left == 0){
            		current->left = new Tree_node(val,0,0,current);
            		break;
				}
				else current = current->left;
			else
				if(current->val < val)
                	if(current->right == 0){
						current->right = new Tree_node(val,0,0,current);
						break;
					}
					else current = current->right;
				else
					return false;
		}
		return true;
	}
	void remove(T k){
	    Tree_node* current = root->left;
	    Tree_node* parent = root->left;
	    while(current && current->val != k)
	        if(k < current->val){
	            parent = current;
	            current = current->left;
	        }
	        else{
	            parent = current;
	            current = current->right;
	        }
	    if(current == 0) return;
	    if(!current->right)
	        if(parent == current){
	            root->left = current->left;
	            delete current;
	        }
	        else{
	            if(parent->left == current)
	                parent->left = current->left;
	            else
	                parent->right = current->left;
	            delete current;
	        }
	    else
	        if(!current->left){     
	            if(parent == current){
	                root->left = current->right;
	                delete current;
	            }
	            else{
	                if(parent->left == current)
	                    parent->left = current->right;
	                else
	                    parent->right = current->right;
	                delete current;
	            }
	        }
	        else{
	            Tree_node* N_root = current->right;
	            Tree_node* N_parent = current;
	            while(N_root->left){
	                N_parent = N_root;
	                N_root = N_root->left;
	            }
	            current->val = N_root->val;
	            if(N_parent->left == N_root)
	                N_parent->left = N_root->right;
	            else
	                N_parent->right = N_root->right;
	            delete N_root;
	        }
	}

	
	
	class iterator{
		Tree_node* current;
	public:
		iterator(Tree_node* node){
			current = node;
		}	
		const T& operator*() {
			return current->val;
		}
		iterator& operator++(){
			if(current->right){
				current = current->right;
				while(current->left){
					current = current->left;
				}
				return *this;
			}
			else{
				while(current->parent->right == current){
					current = current->parent;
				}
				current = current->parent;
				return *this;
			}
		}
		iterator operator++(int){
			Tree_node* temp = current;
			if(current->right){
				current = current->right;
				while(current->left){
					current = current->left;
				}
				return temp;
			}
			else{
				while(current->parent->right == current){
					current = current->parent;
				}
				current = current->parent;
				return temp;
			}
		}
		iterator& operator--(){
			if(current->left){
				current = current->left;
				while(current->right){
					current = current->right;
				}
				return *this;
			}
			else{
				while(current->parent->left == current){
					current = current->parent;
				}
				current = current->parent;
				return *this;
			}
		}
		iterator operator--(int){
			Tree_node* temp = current;
			if(current->left){
				current = current->left;
				while(current->right){
					current = current->right;
				}
				return temp;
			}
			else{
				while(current->parent->left == current){
					current = current->parent;
				}
				current = current->parent;
				return temp;
			}
		}
		bool operator==(iterator a){ return this->current == a.current; }
		bool operator!=(iterator a){ return this->current != a.current; }
		iterator operator+(int n){
			iterator it = *this;
			for(int i = 0; i < n; i++, it++);
			return it;
		}
		iterator operator-(int n){
			iterator it = *this;
			for(int i = 0; i < n; i++, it++);
			return it;
		}
		int operator-(iterator& a){
			int range = 0;
			iterator b = a;
			while(b != *this){
				b++;
				range++;
			}
			return range;
		}
	};
	iterator begin(){
		Tree_node* current = root;
		while(current->left){ current = current->left; }
		return iterator(current);
	}
	iterator end(){
		return iterator(root);
	}
};
