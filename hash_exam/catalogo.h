#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "hashtable.h"
#include "colors.h"

#define TABLE_SIZE 100

class Catalogo {
private:
    HashTable<Color> tablaColores;
    unsigned int size;

    bool isValidNumeric(const std::string& str);
public:
    Catalogo() : size(0) { 
        srand(time(nullptr));
    }

    void imprimir();
    bool loadFromCSV(const std::string& filename);
    Color *buscar(unsigned int r, unsigned int g, unsigned int b);
};