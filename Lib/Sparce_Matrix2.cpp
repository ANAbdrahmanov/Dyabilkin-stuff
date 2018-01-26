#include <iostream>
#include "Sparse_Matrix2.h"

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

Sparse_Matrix2::Sparse_Matrix2(int def){
    def_value = def;
    head = new Cell(-1,-1);
}

Sparse_Matrix2::~Sparse_Matrix2(){
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

int Sparse_Matrix2::r_access(int row, int col) const{
    Cell* current = head;
    while(current->right && current->col < col) current = current->right;
    if(current->col == col){
        while(current->down && current->row < row) current = current->down;
        if(current->row == row) return current->data;
        else return def_value;
    }
    else return def_value;
}

int& Sparse_Matrix2::w_access(int row, int col){
    Cell* current = head;
    Cell* up_start;
    while(current->right && current->right->col < col) current = current->right;
    if(current->right && current->right->col == col)
        up_start = current->right;
    else{
        up_start = new Cell(-1, col, current->right);
        current->right = up_start;
    }

    current = head;
    Cell* left_start;
    while(current->down && current->down->row < row) current = current->down;
    if(current->down && current->down->row == row)
        left_start = current->down;
    else{
        left_start = new Cell(row, -1, 0, current->down);
        current->down = left_start;
    }

    while(up_start->down && up_start->down->row < row) up_start = up_start->down;
    if(up_start->down && up_start->down->row == row) return up_start->down->data;
    else
    {
        while(left_start->right && left_start->right->col < col) left_start = left_start->right;
        Cell* New_cell = new Cell(def_value, row, col, left_start->right, up_start->down);
        up_start->down = New_cell;
        left_start->right = New_cell;
        return New_cell->data;
    }
}

void Sparse_Matrix2::print(){

    for(Cell* r_current = head->down; r_current; r_current = r_current->down){
        Cell* current = r_current;
        while(current->right){
            std::cout<<"[("<<current->right->row<<","<<current->right->col<<") "<<current->right->data<<"] ";
            current = current->right;
        }
        if(r_current->right) std::cout<<"\n";
    }
}
