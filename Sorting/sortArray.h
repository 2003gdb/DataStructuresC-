#pragma once
#include <new>

class Arreglo {
    private:
        int *arr;
        int size;

    public:
        Arreglo(){
            // Declaramos arr a nullptr, para que no apunte a cualquier cosa
            arr = nullptr;

	    }
        ~Arreglo() { 
            std::cout << "Array destruido\n"; 
            if (arr != nullptr){
                delete[] arr;
                arr = nullptr;
            }
        }

        int setSize(int size);
        void menu(Arreglo arr, int opcion);

        void llenarArreglo();
        void printArreglo();

        void bubbleSort();
        void insertionSort();
        void selectionSort();

        void mergeSortExecute();
        void mergeSort(int start, int end);
        void merge(int left, int middle, int right);

};