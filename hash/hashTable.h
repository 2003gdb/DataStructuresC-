#include <iostream>
#include "dll.h"

template <typename T>
class HashTable {
    public:
        using HashFunction = unsigned int (*)(T&, unsigned int tableSize);

        HashTable() {
            hashFunction = nullptr;
            table = nullptr;
            size = 0;
        }
        ~HashTable() { deleteTable(); }
        bool createTable(unsigned int nSize, HashFunction hashF);
        void deleteTable();
        bool insert(T dato);
        bool borrar(T dato);
        int *buscar(T dato);

    private:
        unsigned int getIndex(T dato);
        ListaDobleLigada<int> *table;
        unsigned int size;
        HashFunction hashFunction;
};

template <typename T>
bool HashTable<T>::createTable(unsigned int nSize, HashFunction hashF) {
    if(nSize == 0 || table || !hashF)
        return false;
    table = new(std::nothrow) ListaDobleLigada<int>[nSize];
    if(!table)
        return false;
    size = nSize;
    hashFunction = hashF;
    return true;
}

template <typename T>
void HashTable<T>::deleteTable() {
    if(table) {
        delete [] table;
        table = nullptr;
        size = 0;
    }
}

template <typename T>
unsigned int HashTable<T>::getIndex(T dato) {
    if (!hashFunction)
        return 0;

    return hashFunction(dato, size) % size;
}

template <typename T>
bool HashTable<T>::insert(T dato) {
    unsigned int index = 0;
    if(!table)
        return false;
    index = getIndex(dato);
    return table[index].insertarFinal(dato);
}

template <typename T>
bool HashTable<T>::borrar(T dato) {
    unsigned int index = getIndex(dato);
    if (!table || index >= size)
        return false;
    return table[index].eliminarDato(dato);
}

template <typename T>
int *HashTable<T>::buscar(T dato) {
    unsigned int index = 0;
    if(!table)
        return nullptr;
    index = getIndex(dato);
    return table[index].buscar(dato);
}


