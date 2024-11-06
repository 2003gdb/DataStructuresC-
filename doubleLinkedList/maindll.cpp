#include "dll.h"
#include <iostream>

using namespace std;

#define MAX_DATA 20

int main() {
    ListaDobleLigada<int> DLL;

    for (int i = 0; i < MAX_DATA; i++) {
        if(!DLL.insertarInicio(i)) {
            cout << "No hubo memoria\n";
            return 0;
        }
    }

    DLL.imprimirLista();
    DLL.insertarInicio(21);
    DLL.imprimirLista();
    DLL.insertarFinal(0);
    DLL.imprimirLista();
    DLL.insertarInicio(5);
    DLL.imprimirLista();
    DLL.eliminarDato(21);
    DLL.imprimirLista();
    DLL.insertarFinal(100);
    DLL.insertarFinal(100);
    DLL.imprimirLista();
    DLL.eliminarTail();
    DLL.imprimirLista();

    return 0;
}