#include <iostream>
#include "graph.h"

int main() {
    Graph<unsigned int> grafo;
    //ListaLigada<unsigned int> path;

    if (!grafo.loadFile("dungeon.txt")){
        cerr << "No se pudo cargar" << endl;
    }

    for (int i = 0; i < grafo.getSize(); i++) {
        grafo.setVertex(i, i);
    }

    grafo.print();

    if (!grafo.saveFile("dungeon.txt")){
        cerr << "No se pudo cargar" << endl;
    }
    return 0;
}
