#include <iostream>
#include <string>
#include <fstream>
#include "listaligada.h"

using namespace std;

#define IN_FILENAME    "datos_in.txt"

int main() {
    LinkedList<int>	miLista;
    ifstream        ifile(IN_FILENAME);
    string          line;

    cout << "Inicio: cargando el archivo a la lista ligada" << endl;
    if (!ifile.is_open()) {
        cerr << "Error cargando el archivo: " << IN_FILENAME << endl;
        return 0;
    }

    while (getline(ifile, line)) {
        int valor = 0;

        valor = 3*stoi(line);

        while (valor && getline(ifile, line)) {
            if(!miLista.insertarInicio(stoi(line))) {
                cout << "insertarInicio no tuvo exito" << endl;
                return 0;
            }
            valor --;
        }

        if(getline(ifile, line)) {
            valor = stoi(line);
			if(valor == 7) {
				if(!miLista.eliminaFinal())
					cout << "eliminaFinal no tuvo exito" << endl;
			}
            while (valor && getline(ifile, line)) {
                if(!miLista.insertarFinal(stoi(line))) {
                    cout << "insertarFinal no tuvo exito" << endl;
                    return 0;
                }
                valor--;
            }
        }
    }

    ifile.close();

	for(int i = 0; i < 10; i++) {		
		if(!miLista.eliminaFinal())
			cout << "eliminaFinal no tuvo exito" << endl;
	}

    for(int i = 0; i < 10; i++)
        cout << i << ": " << miLista.cuentaMenores(i) << " veces" << endl;

    miLista.borraLista();

	cout << "Final: terminando el main" << endl;
    
    return 0;
}

