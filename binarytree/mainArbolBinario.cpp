#include <iostream>
#include <string>
#include "arbolbinario.h"

using namespace std;

#define OPCION_SALIDA	0

int main() {
	int 				option = 0;
	ArbolBinario<int>	BST;

	do {
		cout << "Elije una opcion:" << endl;
		cout << "1) Inserta dato" << endl;
		cout << "2) Imprimir In Order" << endl;
		cout << "3) Imprimir Pre Order" << endl;
		cout << "4) Imprimir Post Order" << endl;
		cout << "5) Imprimir BFS" << endl;
		cout << "6) Borrar Nodo" << endl;
		cout << "7) Borrar Todo" << endl << endl;
		
		
		cout << "0) Salir" << endl;

        cin >> option;

		if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            option = -1;
        }

		switch(option) {
			case 1: {	
				int dato = 0;

				cout << "Dame el dato a insertar: ";

                cin >> dato;
                if(cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    option = -1;
                }
				else {
					if(BST.inserta(dato))
						cout << "Valor insertado" << endl;
					else   
						cout << "Error al insertar nuevo valor" << endl;
				}
				break;
			}
			case 2:
				BST.imprimeInOrder();
				break;
			case 3:
				BST.imprimePreOrder();
				break;
			case 4:
				BST.imprimePostOrder();
				break;
			case 5:
				BST.imprimeBFS();
				break;
		    case 7:
				BST.borrarArbol();
				break;
			case 6: {	
				int dato = 0;

				cout << "Dame el dato a borrar: ";

                cin >> dato;
                if(cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    option = -1;
                }
				else {
					if(BST.borrarNodo(dato))
						cout << "Valor Borrado" << endl;
					else   
						cout << "Error al borrar valor" << endl;
				}
				break;
			}

				break;
			case OPCION_SALIDA:
				break;
			default:
				cout << "Opcion invalida" << endl;
				break;
		}
		cout << "\n";
	} while(option != OPCION_SALIDA);

	return 0;
}