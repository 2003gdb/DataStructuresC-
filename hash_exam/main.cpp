#include <iostream>
#include "catalogo.h"

using namespace std;


int main() {
    Color       *res;
    Catalogo    miCatalogo;

    if(!miCatalogo.loadFromCSV("colors.csv")) {
        cout << "No se pudo crear el catalogo." << endl;
        return 0;
    }

    res = miCatalogo.buscar(153, 102, 102);                              
    if(res)
        cout << *res << endl;
    else
        cout << "No se encontro el Color." << endl;

    res = miCatalogo.buscar(0x48, 0x3d, 0x8b);                           
    if(res)
        cout << *res << endl;
    else
        cout << "No se encontro el Color." << endl;
    
    cout << "Resultados entregados\n";
    return 0;
}