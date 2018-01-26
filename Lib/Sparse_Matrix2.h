struct Cell{
    int row;
    int col;
    Cell* right;
    Cell* down;
    int data;
    Cell(){}
    Cell(int,int,int,Cell*,Cell*);
    Cell(int,int,Cell*,Cell*);
};

class Sparse_Matrix2{
    int def_value;
    Cell* head;
public:
    Sparse_Matrix2(int);
    int r_access(int, int) const;
    int& w_access(int, int);
    ~Sparse_Matrix2();
    void print();
};
