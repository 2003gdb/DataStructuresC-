#include <iostream>
#include "dll.h"

class HashTable {
    public:
        HashTable() {
        table = nullptr;
        size = 0;
        }
        ~HashTable() { deleteTable(); };
        bool createTable(unsigned int nSize);
        void deleteTable();
        bool insert(int dato);
        bool borrar(int dato);
        int *buscar(int dato);

    private:
        unsigned int hashToIndex(int dato);
        ListaDobleLigada<int> *table;
        unsigned int size;
};

