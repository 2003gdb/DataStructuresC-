#include "hashTable.h"

bool HashTable::createTable(unsigned int nSize) {
    if(nSize == 0 || table)
        return false;
    table = new(std::nothrow) ListaDobleLigada<int>[nSize];
    if(!table)
        return false;
    size = nSize;
    return true;
}

void HashTable::deleteTable() {
    if(table) {
        delete [] table;
        table = nullptr;
        size = 0;
    }
}

unsigned int HashTable::hashToIndex(int dato) {
    return dato % size;
}

bool HashTable::insert(int dato) {
    unsigned int index = 0;
    if(!table)
        return false;
    index = hashToIndex(dato);
    return table[index].insertarFinal(dato);
}

bool HashTable::borrar(int dato) {
    return true;
}

int *HashTable::buscar(int dato) {
    unsigned int index = 0;
    if(!table)
        return nullptr;
    index = hashToIndex(dato);
    return table[index].buscar(dato);
}
