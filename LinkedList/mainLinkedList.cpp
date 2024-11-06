#include "ll.h"
#include <iostream>

using namespace std;

#define MAX_DATA 20

int main() {
    ListaLigada<int> linkedList;
    
    for (int i = 0; i < MAX_DATA; i++) {
        if(!linkedList.insertar(i)) {
            cout << "No hubo memoria\n";
            return 0;
        }
    }

    linkedList.imprimirLista();
    linkedList.insertar(0);
    linkedList.imprimirLista();
    linkedList.destruirNodo(5);
    linkedList.imprimirLista();

    return 0;
}