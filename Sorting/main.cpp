#include <iostream>
#include "sortArray.h"

using namespace std;

void menu(Arreglo &arr){
        int opcion = 0;

        while (opcion != 5){

        cout << "Elije una opción para el sort:" << endl;
        cout << "1) Bubble Sort" << endl;
        cout << "2) Insertion Sort" << endl;
        cout << "3) Selection Sort" << endl;
        cout << "4) Merge Sort" << endl;
        cout << "5) Salir" << endl;

        cin >> opcion;

        if (opcion == 1){
            arr.bubbleSort();
        }
        else if (opcion == 2){
            arr.insertionSort();
        }
        else if (opcion == 3){
            arr.selectionSort();
        }
        else if (opcion == 4){
            arr.mergeSortExecute();
        }
        else {
            cout << "Numero no es valido" << endl;
        }

        arr.printArreglo();
    }
}

int main(){
    Arreglo arr;
    int userSize;

    cout << "Cual es el tamaño del array: ";
    cin >> userSize;
    cout << endl;

    arr.setSize(userSize);
    arr.llenarArreglo();
    arr.printArreglo();

    menu(arr);

    return 0;
}