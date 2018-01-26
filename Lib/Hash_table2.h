struct Cell{
    int data;
    char* key;
    Cell* next;
    Cell(){}
    Cell(int, char*, Cell*);
    ~Cell();
};

class Hash_table2{
    Cell** table;
    int table_size;
    int n_entries;
    int not_found;
    int hash(char*);
public:
    Hash_table2(int, int);
    ~Hash_table2();
    bool add(int, char*);
    void remove(char*);
    int find(char*);
    void print();
};
