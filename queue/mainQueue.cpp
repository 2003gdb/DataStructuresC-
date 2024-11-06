#include <iostream>
#include "queue.h"

using namespace std;

#define OPCION_SALIDA   6

int main() {
    int             option = 0;
    Queue<int>      q;

    do {
        if(!q.isEmpty()) {
            cout << endl << "Cola actual:" << endl;
            q.imprimirQueue();
        }
        cout << "Elije una opcion:" << endl;
        cout << "1) Enqueue" << endl;
        cout << "2) Dequeue" << endl;
        cout << "3) getFront" << endl;
        cout << "4) isEmpty" << endl;        
        cout << "6) Salir" << endl;
        cin >> option;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch(option) {
            case 1: {   
                int dato = 0;

                cout << "Dame el dato a insertar: ";
                cin >> dato;

                if(cin.fail()) {
                    cin.clear(); 
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida. Inserta un numero entero." << endl;
                }
                else {
                    if(q.enqueue(dato))
                        cout << "Valor insertado" << endl;
                    else   
                        cout << "Error al insertar nuevo valor" << endl;
                }
                break;
            }
            case 2:
                if(!q.dequeue())
                    cout << "No se pudo eliminar head" << endl;
                break;
            case 3: {   
                const int *valor = nullptr;

                valor = q.getFront();
                if(valor)
                    cout << "El valor en top es: " << *valor << endl;
                else   
                    cout << "No existe el dato" << endl;
                break;
            }
            case 4:
                if(q.isEmpty())
                    cout << "La pila esta vacia" << endl;
                else 
                    cout << "La pila no esta vacia" << endl;
            case OPCION_SALIDA:
                break;
            default:
                cout << "Opcion invalida" << endl;
                break;
        }
    } while(option != OPCION_SALIDA);

    return 0;
}