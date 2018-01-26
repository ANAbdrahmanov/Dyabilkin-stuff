#include "Sparse_Matrix.h"
#include <iostream>

Cell::Cell(int _data, int _row, int _col, Cell* _right, Cell* _down){
    data = _data;
    row = _row;
    col = _col;
    right = _right;
    down = _down;
}

Cell::Cell(int _row, int _col, Cell* _right = 0, Cell* _down = 0){
    row = _row;
    col = _col;
    right = _right;
    down = _down;
}

Sparse_Matrix::Sparse_Matrix(int rows, int cols, int def){
    n_rows = rows;
    n_cols = cols;
    def_value = def;
    head = new Cell(-1,-1);
    Cell* current = head;
    for (int i = 0; i < n_cols; i++){
        Cell* New_cell = new Cell(-1,i);
        current->right = New_cell;
        current = New_cell;
    }
    current = head;
    for (int i = 0; i < n_rows; i++){
        Cell* New_cell = new Cell(i,-1);
        current->down = New_cell;
        current = New_cell;
    }
}

Sparse_Matrix::~Sparse_Matrix(){
    Cell* r_current = head;
    while(r_current){
        Cell* current = r_current;
        r_current = r_current->right;
        while(current){
            Cell* temp = current->down;
            delete current;
            current = temp;
        }
    }
}

int Sparse_Matrix::r_access(int row, int col) const{
    Cell* current = head;
    while(current->col < col) current = current->right;
    while(current->down && current->row < row) current = current->down;
    if(current->row == row) return current->data;
    else return def_value;
}

int& Sparse_Matrix::w_access(int row, int col){
    Cell* current = head;
    while(current->col < col) current = current->right;
    while(current->down && current->down->row < row) current = current->down;
    if(current->down && current->down->row == row) return current->down->data;
    else
    {
        Cell* r_current = head;
        while(r_current->row < row) r_current = r_current->down;
        while(r_current->right && r_current->right->col < col) r_current = r_current->right;
        Cell* New_cell = new Cell(def_value,row,col,r_current->right,current->down);
        current->down = New_cell;
        r_current->right = New_cell;
        return New_cell->data;
    }
}

void Sparse_Matrix::print(){

    for(Cell* r_current = head->down; r_current; r_current = r_current->down){
        Cell* current = r_current;
        while(current->right){
            std::cout<<"[("<<current->right->row<<","<<current->right->col<<") "<<current->right->data<<"] ";
            current = current->right;
        }
        if(r_current->right) std::cout<<"\n";
    }
}
