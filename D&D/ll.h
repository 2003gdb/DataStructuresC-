#include <iostream>
#pragma once
using namespace std;

// Representa un nodo individual en una lista ligada.
template <typename t>
class NodoListaLigada{
    public:
        // Dato almacenado en el nodo.
        t dato;

        // Puntero al siguiente nodo en la lista.
        NodoListaLigada<t> *next;

        // Constructor por defecto de NodoListaLigada.
        NodoListaLigada(): dato(t()), next(nullptr){}
};

// Implementa una lista ligada genérica con métodos para manipular los nodos.
template <typename t>
class ListaLigada{
    private:
        // Puntero al primer nodo de la lista.
        NodoListaLigada<t> *head;
    public:
        // Constructor por defecto de ListaLigada.
        ListaLigada() : head(nullptr){}

        // Destructor de ListaLigada.
        ~ListaLigada(){
            if (!destruirLista()){
                cout << "No se pudo destruir Lista" << endl;
            }
        }

        // Inserta un nuevo nodo al final de la lista.
        // Parámetros:
        //   dato - el valor que se insertará en la lista.
        // Retorno:
        //   true si la inserción fue exitosa, false en caso contrario.
        bool insertar(t dato);

        // Destruye un nodo específico basado en el valor proporcionado.
        // Parámetros:
        //   datoIdentificador - el valor del nodo que se desea eliminar.
        // Retorno:
        //   true si el nodo fue eliminado, false en caso contrario.
        bool destruirNodo(t datoIdentificador);

        // Imprime todos los valores de la lista en la consola.
        // Retorno:
        //   true si la lista tiene nodos y se imprimió, false si está vacía.
        bool imprimirLista();

        // Destruye todos los nodos de la lista, liberando la memoria asignada.
        // Retorno:
        //   true si la lista fue destruida exitosamente, false en caso contrario.
        bool destruirLista();

        // Busca un nodo específico basado en el valor proporcionado.
        // Parámetros:
        //   dato - el valor del nodo que se desea buscar.
        // Retorno:
        //   true si el nodo fue encontrado, false en caso contrario.
        bool search(t dato);

        // Clase anidada iterator
        // Proporciona un iterador para recorrer la lista ligada.
        class iterator {
            public:
                // Constructor del iterador.
                // Parámetros:
                //   node - puntero al nodo inicial para el iterador.
                iterator(NodoListaLigada<t>* node) : current(node) {}
                iterator() : current(nullptr) {}

                // Sobrecarga del operador *.
                // Retorno:
                //   Referencia al dato del nodo actual.
                t& operator*() {
                    return current->dato;
                }

                // Sobrecarga del operador ++.
                // Avanza el iterador al siguiente nodo.
                iterator& operator++() {
                    if(current)
                        current = current->next;
                    return *this;
                }

                // Sobrecarga del operador ==.
                // Compara dos iteradores para verificar si apuntan al mismo nodo.
                // Parámetros:
                //   other - otro iterador con el que se compara.
                // Retorno:
                //   true si los iteradores apuntan al mismo nodo, false en caso contrario.
                bool operator==(const iterator& other) const {
                    return current == other.current;
                }

                // Sobrecarga del operador !=.
                // Compara dos iteradores para verificar si apuntan a nodos diferentes.
                // Parámetros:
                //   other - otro iterador con el que se compara.
                // Retorno:
                //   true si los iteradores apuntan a nodos diferentes, false en caso contrario.
                bool operator!=(const iterator& other) const {
                    return current != other.current;
                }

            private:
                // Puntero al nodo actual del iterador.
                NodoListaLigada<t>* current;
            };

            // Retorna un iterador apuntando al primer nodo de la lista.
            // Retorno:
            //   Iterador inicial.
            iterator begin() {
                return iterator(head);
            }

            // Retorna un iterador apuntando al final de la lista (nullptr).
            // Retorno:
            //   Iterador final.
            iterator end() {
               return iterator(nullptr);
            }
};

template <typename t>
bool ListaLigada<t>::search(t dato){
    if (!head) {
        return false;
    }

    NodoListaLigada<t> *current = head;

    while (current && current->dato != dato) {
        current = current->next;
    }

    if (!current) {
        return false;
    }

    return true;
}

template <typename t>
bool ListaLigada<t>::insertar(t dato){
    NodoListaLigada<t> *nuevo = nullptr;
    NodoListaLigada<t> *temp = nullptr;

    nuevo = new(nothrow) NodoListaLigada<t>;

    if (!nuevo){
        return false;
    }

    nuevo->dato = dato;

    if (!head){
        head = nuevo;
        return true;
    }

    temp = head;
    while (temp->next){
        temp = temp->next;
    }
    temp->next = nuevo;
    return true;
}

template <typename t>
bool ListaLigada<t>::imprimirLista(){
    NodoListaLigada<t> *temp = head;

    if (!head)
        return false;

    while (temp){
        cout << temp->dato << " ";
        temp = temp->next;
    }
    cout << endl;
    return true;
}

template <typename t>
bool ListaLigada<t>::destruirLista(){
    NodoListaLigada<t> *destructorNodal = head, *temp = nullptr;

    if (!head){
        return false;
    }
        
    while (destructorNodal){
        temp = destructorNodal->next;
        delete destructorNodal;
        destructorNodal = temp;
    }
    head = nullptr;
    return true;
    
}

template <typename t>
bool ListaLigada<t>::destruirNodo(t dato) {
    if (!head) {
        return false;
    }

    if (head->dato == dato) {
        NodoListaLigada<t> *tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    NodoListaLigada<t> *current = head;
    NodoListaLigada<t> *previous = nullptr;

    while (current && current->dato != dato) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        return false;
    }

    previous->next = current->next;
    delete current;
    return true;

}

