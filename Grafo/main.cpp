#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    Graph<int> grafo;

    if (!grafo.loadFile("test.txt")){
        cerr << "No se pudo cargar" << endl;
    }

    grafo.insertEdge(0, 2);

    if (!grafo.saveFile("test.txt")){
        cerr << "No se pudo cargar" << endl;
    }
    return 0;
}
