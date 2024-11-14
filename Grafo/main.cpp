#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    Graph grafo;

    if (!grafo.loadFile("test.txt")){
        cerr << "No se pudo cargar" << endl;
    }

    grafo.eliminateEdge(0, 7);
    grafo.eliminateEdge(1, 7);

    if (!grafo.saveFile("test.txt")){
        cerr << "No se pudo guardar" << endl;
    }


    return 0;
}