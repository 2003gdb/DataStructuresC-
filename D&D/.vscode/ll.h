// Crea una lista ligada para organizar datos y contiene funciones para interactuar con ella.
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include <iostream>
using namespace std;

template <typename t>
class NodoListaLigada {
    public:
        t* dato;
        NodoListaLigada<t> *next;

        // Constructor que inicializa los miembros 'dato' y 'next' a nullptr.
        NodoListaLigada(): dato(nullptr), next(nullptr){}
};

template <typename t>
class ListaLigada {
    private:
        NodoListaLigada<t> *head;

    public:
        // Constructor que inicializa head de la lista como nullptr.
        ListaLigada() : head(nullptr) {}

        // Destructor que destruye la lista al liberar la memoria de todos los nodos.
        ~ListaLigada(){
            if (!destruirLista()){
                cout << "No se pudo destruir Lista" << endl;
            }
        }

        // Imprime todos los elementos de la lista en orden.
        // Retorno:
        //   true si la lista se imprime correctamente, false si la lista está vacía.
        bool imprimirLista();

        // Libera la memoria de todos los nodos de la lista.
        // Retorno:
        //   true si la lista se destruye correctamente, false si ocurre algún error.
        bool destruirLista();

        // Inserta un nuevo dato en la lista de manera ordenada.
        // Parámetros:
        //   dato - un puntero al dato que se desea insertar en la lista.
        // Retorno:
        //   true si el dato se inserta correctamente, false si ocurre algún error.
        bool insertarInOrder(t* dato);
};


template <typename t>
bool ListaLigada<t>::insertarInOrder(t* dato) {
    NodoListaLigada<t>* nuevo = new NodoListaLigada<t>;
    NodoListaLigada<t>* actual = head;
    nuevo->dato = dato;

    if (!head || *dato < *(head->dato)) {
        nuevo->next = head;
        head = nuevo;
        return true;
    }

    while (actual->next && *(actual->next->dato) < *dato) {
        actual = actual->next;
    }

    nuevo->next = actual->next;
    actual->next = nuevo;
    return true;
}

template <typename t>
bool ListaLigada<t>::imprimirLista(){
    NodoListaLigada<t> *temp = head;

    if (!head)
        return false;

    while (temp){
        cout << *(temp->dato) << endl;
        temp = temp->next;
    }
    return true;
}

template <typename t>
bool ListaLigada<t>::destruirLista(){
    NodoListaLigada<t> *destructorNodal = head, *temp = nullptr;

    if (!head)
        return false;

    while (destructorNodal){
        temp = destructorNodal->next;
        delete destructorNodal;
        destructorNodal = temp;
    }
    head = nullptr;
    return true;
    
}
