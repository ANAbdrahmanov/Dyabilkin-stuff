struct AVL_node{
    int val;
    AVL_node* left;
    AVL_node* right;
    AVL_node* parent;
    int balance_factor;
    AVL_node(){}
    AVL_node(int, AVL_node*, AVL_node*, AVL_node*, int);
};

class AVL_tree{
    AVL_node* root;
    void Destruct(AVL_node*);
    int h(AVL_node*);
    void pr(AVL_node*, int);
    void pre_pr(AVL_node*);
    void in_pr(AVL_node*);
    void post_pr(AVL_node*);
    void balance_add(AVL_node*, int);
    AVL_node* LeftRotate(AVL_node*);
    AVL_node* RightRotate(AVL_node*);
public:
    AVL_tree();
    AVL_tree(int);
    ~AVL_tree();
    bool add(int);
    int height();
    void print();
    void print_preorder();
    void print_inorder();
    void print_postorder();
    void remove(int);
};
