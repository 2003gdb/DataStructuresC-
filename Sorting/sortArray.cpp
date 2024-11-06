#include <iostream>
#include "sortArray.h"
using namespace std;

#include <ctime>

void Arreglo::llenarArreglo(){
    
    srand(time(0));
    for (int i = 0; i < size; i++){
        // rand() da un numero aleactorio
        // "%" es para obtener el residuo de la división
        // con % nos aseguramos que el numero sea menor que 100
        // ya que el RESIDUO nunca puede SER MAYOR que el DIVISOR
        arr[i] = rand() % 100;
    }
}

void Arreglo::printArreglo(){
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int Arreglo::setSize(int userSize){

    size = userSize;

    // Declaramos memoria dinamica para el array
    arr = new(std::nothrow) int[size]; 
    if (arr == nullptr) {
        std::cout << "No hay memoria\n";
        return 1;
    }

    return 0;

}

void Arreglo::bubbleSort(){
    int temp;
    for (int k = 0; k < size; k++){
        for (int i = 0; i < (size - 2); i++){
            if (arr[i] > arr[i+1]){
                temp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = temp;
            }
        }   
    }
}

void Arreglo::insertionSort(){
    int temp;
    // Empieza en la segunda posición
    for (int i = 1; i < size; i++){
        // Si es menor "i"
        if (arr[i] < arr[i-1]){
            // Comparamos "i" con cada una de los lugares anteriores
            for (int k = 0; k < i; k++){
                // Si es menor "i" 
                if (arr[i] < arr[k]){
                    // guardamos "i" en otra variable
                    temp = arr[i];
                    // recorremos todas los valores uno arriba, hasta "k"
                    for(int j = i-1; j >= k; j--){
                        arr[j+1] = arr[j];
                    }
                    // Se posiciona "i", donde es "k"
                    arr[k] = temp;
                }
            }
        }
    }
}

void Arreglo::selectionSort(){
    int temp;
    int menor;
    int posicionMenor;
    
    for(int i = 0; i < size; i++){
        menor = arr[i];
        for (int k = i+1; k < size; k++){
            if (menor > arr[k]){
                menor = arr[k];
                posicionMenor = k;
            }
        }
        temp = arr[posicionMenor];
        arr[posicionMenor] = arr[i];
        arr[i] = temp;
    }
}

void Arreglo::mergeSortExecute() {
	mergeSort(0, size - 1);
}

void Arreglo::mergeSort(int start, int end) {
	int middle = 0;
	if (start >= end)
		return;

	middle = start + (end - start) / 2;

	mergeSort(start, middle);
	mergeSort(middle + 1, end);

	merge(start, middle, end);
}

void Arreglo::merge(int left, int middle, int right) {
	int sizeLeft = middle - left + 1;
	int sizeRight = right - middle;

	int* leftArr = new(nothrow) int[sizeLeft];
	if (!leftArr) {
		cout << "No hay memoria suficienta para el leftArr";
		delete[] leftArr;
		return;
	}

	int* rightArr = new(nothrow) int[sizeRight];
	if (!rightArr) {
		cout << "No hay memoria suficiente para el rightArr";
		delete[] rightArr;
		return;
	}

	for (int i = 0; i < sizeLeft; i++)
		leftArr[i] = arr[left + i];

	for (int j = 0; j < sizeRight; j++)
		rightArr[j] = arr[middle + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < sizeLeft && j < sizeRight) {
		if (leftArr[i] <= rightArr[j]) {
			arr[k] = leftArr[i];
			i++;
		}
		else {
			arr[k] = rightArr[j];
			j++;
		}
		k++;
	}	

	while (i < sizeLeft) {
		arr[k] = leftArr[i];
		i++;
		k++;
	}

	while (j < sizeRight) {
		arr[k] = rightArr[j];
		j++;
		k++;
	}
}
