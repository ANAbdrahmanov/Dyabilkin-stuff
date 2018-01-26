#include <iostream>
#include "Hash_table2.h"

Cell::Cell(int _data, char* _key, Cell* _next = 0){
    data = _data;
    next = _next;
    key = new char[strlen(_key)];
    strcpy(key,_key);
}

Cell::~Cell(){
    delete[] key;              
}

int Hash_table2::hash(char* k){
    int result = 0;
    for(int i = 0; k[i]; i++)
        if(!i%2)
            result+=k[i];
        else
            result-=k[i];
    return result>0?result%table_size:(-result)%table_size;
}

Hash_table2::Hash_table2(int size, int not_f){
    table_size = size;
    not_found = not_f;
    n_entries = 0;
    table = new Cell*[size];
    for(int i = 0; i<table_size; i++)
        table[i] = 0;
}

Hash_table2::~Hash_table2(){
    for(int i = 0; i<table_size; i++){
        Cell* current = table[i];
        while(current){
            Cell* temp = current->next;
            delete current;
            current = temp;
        }
    }
    delete[] table;
}

bool Hash_table2::add(int item, char* _key){
    if(n_entries/table_size >= 5){
        for(Cell* current = table[hash(_key)]; current; current = current->next)
            if(!strcmp(current->key,_key))
                return false;
        Cell** Old_table = table;
        int Old_table_size = table_size;
        table_size*=2;
        table = new Cell*[table_size];
        for(int i = 0; i<table_size; i++)
            table[i] = 0;
        n_entries = 0;
        for(int i = 0; i<Old_table_size; i++){
            for(Cell* current = Old_table[i]; current;){
                add(current->data,current->key);
                Cell* temp = current->next;
                delete current;
                current = temp;
            }
        }
        delete[] Old_table;
        return add(item, _key);
    }
    else {
        int required_row = hash(_key);
        for(Cell* current = table[required_row]; current; current = current->next)
            if(!strcmp(current->key,_key))
                return false;
        table[required_row] = new Cell(item, _key, table[required_row]);
        n_entries++;
        return true;
    }
}

void Hash_table2::remove(char* _key){
    Cell* current = table[hash(_key)];
    Cell* prev = current;
    while(current && strcmp(current->key,_key)){
        prev = current;
        current = current->next;
    }
    if(!current) return;
    if(prev == current){
        table[hash(_key)] = current->next;
        delete current;
    }
    else{
        prev->next = current->next;
        delete current;
    }
    n_entries--;
}

int Hash_table2::find(char* _key){
    Cell* current = table[hash(_key)];
    while(current && strcmp(current->key,_key))
        current = current->next;
    if(!current)
        return not_found;
    else
        return current->data;
}

void Hash_table2::print(){
    for(int i = 0; i<table_size; i++){
        std::cout<<i<<":";
        Cell* current = table[i];
        while(current){
            std::cout<<"["<<current->data<<", "<<current->key<<"] ";
            current = current->next;
        }
        std::cout<<"\n";
    }
}
