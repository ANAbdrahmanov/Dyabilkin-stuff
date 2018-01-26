#include <iostream>
#include <algorithm>      
#include "AVL_tree.h"


using namespace std;

AVL_node::AVL_node(int v, AVL_node* l = 0, AVL_node* r = 0, AVL_node* p = 0, int bal = 0){
    val = v;
    left = l;
    right = r;
    parent = p;
    balance_factor = bal;
}

AVL_tree::AVL_tree(){
    root = 0;
}

AVL_tree::AVL_tree(int v){
    root = new AVL_node(v);
}

AVL_tree::~AVL_tree(){
    Destruct(root);
}

void AVL_tree::Destruct(AVL_node* r){
    if(r){
    Destruct(r->left);
    Destruct(r->right);
    delete r;
    }
}

bool AVL_tree::add(int k){
    if(root == 0){
        root = new AVL_node(k);
        return true;
    }
    AVL_node* current = root;
    while(true)
        if(current->val > k)
            if(current->left == 0){
                current->left = new AVL_node(k,0,0,current);
                balance_add(current, -1);
                break;
            }
            else
                current = current->left;
        else
            if(current->val < k)
                if(current->right == 0){
                    current->right = new AVL_node(k,0,0,current);
                    balance_add(current, 1);
                    break;
                }
                else
                    current = current->right;
            else
                return false;
    return true;
}

void AVL_tree::balance_add(AVL_node* check, int change){
	while(check){
		check->balance_factor += change;
		if(check->balance_factor == 0) return;	
		else if(check->balance_factor == 1 || check->balance_factor == -1){
			if(check->parent)
				if(check->parent->left == check) 
					change = -1;
				else
					change = 1;
			check = check->parent;
		}
		else if(check->balance_factor == 2){
			if(check->right->balance_factor == 1)
				if(check->right->balance_factor == 1){
					check = LeftRotate(check->right);
				}
				else{
					check->right = RightRotate(check->right->left);
					check = LeftRotate(check->right);
				}
			break;	
		}
		else {
			if(check->left->balance_factor == -1){
				check = RightRotate(check->left);
			}
			else{
				check->left = LeftRotate(check->left->right);
				check = RightRotate(check->left);
			}
			break;
		}
	}	
}

AVL_node* AVL_tree::RightRotate(AVL_node* B){
	AVL_node* A = B->parent;
	AVL_node* Aparent = A->parent;
	A->left = B->right;
	A->parent = B;
	B->right = A;
	if(A->left){
		A->left->parent = A;
	}
	B->parent = Aparent;
	if(Aparent)
		if(Aparent->left == A)
			Aparent->left = B;
		else
			Aparent->right = B;
	B->balance_factor = 0;
	A->balance_factor = 0;
	if(B->parent == 0)
		root = B;
	return B;
}

AVL_node* AVL_tree::LeftRotate(AVL_node* B){
	AVL_node* A = B->parent;
	AVL_node* Aparent = A->parent;
	A->right = B->left;
	A->parent = B;
	B->left = A;
	if(A->right){
		A->right->parent = A;
	}
	B->parent = Aparent;
	if(Aparent)
		if(Aparent->left == A)
			Aparent->left = B;
		else
			Aparent->right = B;
	B->balance_factor = 0;
	A->balance_factor = 0;
	if(B->parent == 0)
		root = B;
	return B;
}

int AVL_tree::height(){
    return h(root);
}

int AVL_tree::h(AVL_node* r){
    if(r) return 0;
    else
        return max(h(r->left),h(r->right)) + 1;

}

void AVL_tree::print_preorder(){
    if(root == 0){
        cout<<"EMPTY\n";
        return;
    }
    pre_pr(root);
    cout<<"\n";
}

void AVL_tree::print_inorder(){
    if(root == 0){
        cout<<"EMPTY\n";
        return;
    }
    in_pr(root);
    cout<<"\n";
}

void AVL_tree::print_postorder(){
    if(root == 0){
        cout<<"EMPTY\n";
        return;
    }
    post_pr(root);
    cout<<"\n";
}

void AVL_tree::pre_pr(AVL_node* r){
    if(r){
        cout<<r->val<<" ";
        pre_pr(r->left);
        pre_pr(r->right);
    }
}

void AVL_tree::in_pr(AVL_node* r){
    if(r){
        in_pr(r->left);
        cout<<r->val<<" ";
        in_pr(r->right);
    }
}

void AVL_tree::post_pr(AVL_node* r){
    if(r){
        post_pr(r->left);
        post_pr(r->right);
        cout<<r->val<<" ";
    }
}

void AVL_tree::print(){
    if(root == 0){
        cout<<"EMPTY\n";
        return;
    }
     pr(root,0);
     cout<<"\n";
}

void AVL_tree::pr(AVL_node* r, int h){
    if(r == 0){
        for(int i = 0; i < h; i++)
            cout<<" ";
        cout<<"@\n";
        return;
    }
    pr(r->right, h+1);
    for(int i = 0; i < h; i++)
            cout<<" ";
    cout<<r->val<<"\n";
    pr(r->left, h+1);
}

void AVL_tree::remove(int k){
    AVL_node* current = root;
    AVL_node* parent = root;
    while(current && current->val != k)
        if(current->val > k){
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
            root = current->left;
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
                root = current->right;
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
            AVL_node* N_root = current->right;
            AVL_node* N_parent = current;
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
