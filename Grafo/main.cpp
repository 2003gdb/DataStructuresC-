#include <iostream>
#include "graph.h"

int main() {
    Graph<int> grafo;

    if (!grafo.loadFile("test.txt")){
        cerr << "No se pudo cargar" << endl;
    }

    if (!grafo.saveFile("test.txt")){
        cerr << "No se pudo cargar" << endl;
    }
    return 0;
}
