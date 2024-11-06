// Crea una Lista Doblemente Ligada para organizar datos y contiene funciones para interactuar con ella.
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include <iostream>
using namespace std;

template <typename T>
class NodoDLL {
    public:
        T dato;
        NodoDLL<T> *before;
        NodoDLL<T> *next;

        // Constructor: Inicializa un nodo doblemente ligado con valores por defecto.
        NodoDLL(): dato(T()), before(nullptr), next(nullptr) {}
};

template <typename T>
class ListaDobleLigada {
    private:
        NodoDLL<T> *head;
        NodoDLL<T> *tail;
    
    public:
        // Constructor: Inicializa una lista doblemente ligada vacía.
        ListaDobleLigada(): head(nullptr), tail(nullptr) {}

        // Destructor: Destruye la lista al eliminar todos los nodos.
        ~ListaDobleLigada(){
            if (!destruirLista()){
                cout << "NO se eliminó correctamente" << endl;
            }
        }

        // Inserta un dato al final de la lista.
        // Parámetros:
        //   dato - el valor a insertar.
        // Retorno:
        //   true si la inserción fue exitosa, false en caso de fallo.
        bool insertarFinal(T dato);

        // Inserta un dato al inicio de la lista.
        // Parámetros:
        //   dato - el valor a insertar.
        // Retorno:
        //   true si la inserción fue exitosa, false en caso de fallo.
        bool insertarInicio(T dato);

        // Imprime todos los elementos de la lista.
        // Retorno:
        //   true si la lista tiene elementos, false si está vacía.
        bool imprimirLista();

        // Elimina todos los nodos de la lista.
        // Retorno:
        //   true si la destrucción fue exitosa, false en caso de error.
        bool destruirLista();

        // Elimina el nodo en la cabeza de la lista.
        // Retorno:
        //   true si se eliminó correctamente, false si la lista está vacía.
        bool eliminarHead();

        // Elimina el nodo en la cola de la lista.
        // Retorno:
        //   true si se eliminó correctamente, false si la lista está vacía.
        bool eliminarTail();

        // Elimina un nodo que contenga el dato especificado.
        // Parámetros:
        //   dato - el valor del nodo a eliminar.
        // Retorno:
        //   true si se eliminó correctamente, false si el dato no fue encontrado.
        bool eliminarDato(T dato);
};

template <typename T>
bool ListaDobleLigada<T>::insertarFinal(T dato){
    NodoDLL<T> *nuevo = nullptr;
    NodoDLL<T> *beforeNodo = nullptr;
    NodoDLL<T> *temp = head;


    nuevo = new(nothrow) NodoDLL<T>;
    if (!nuevo)
        return false;

    nuevo->dato = dato;
    
    if (!head){
        head = nuevo;
        tail = nuevo;
        return true;
    }

    while (temp->next){
        beforeNodo = temp;
        temp = temp->next;
    }
    beforeNodo->next = nuevo; 
    tail = nuevo;
    tail->before = beforeNodo;
    return true;
}

template <typename T>
bool ListaDobleLigada<T>::insertarInicio(T dato){
    NodoDLL<T> *nuevo = nullptr;

    nuevo = new(nothrow) NodoDLL<T>;
    if (!nuevo){
        return false;
    }
    
    if (!head){
        tail = nuevo;
    } else {
        head->before = nuevo;
        nuevo->next = head;
    }
    nuevo->dato = dato;
    head = nuevo;

    return true;
}

template <typename T>
bool ListaDobleLigada<T>::imprimirLista(){
    NodoDLL<T> *temp = head;

    if(!head){
        return false;
    }

    while (temp){
        cout << temp->dato << endl;
        temp = temp->next;
    }
    return true;
}

template <typename T>
bool ListaDobleLigada<T>::destruirLista(){
    NodoDLL<T> *destructorNodal = head, *temp = nullptr;

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

template <typename T>
bool ListaDobleLigada<T>::eliminarHead(){
    NodoDLL<T> *temp = head;
    if (!head){
        return false;
    }

    if (!head->next){
        delete temp;
        head = nullptr;
        tail = nullptr;
        return true;
    }

    head = head->next;
    head->before = nullptr;
    delete temp;
    return true;
}

template <typename T>
bool ListaDobleLigada<T>::eliminarTail(){
    NodoDLL<T> *temp = tail;
    if (!head){
        return false;
    }

    if (!tail->before){
        delete temp;
        temp = nullptr;
        head = nullptr;
        tail = nullptr;
        return true;
    }

    tail = temp->before;
    tail->next = nullptr;
    delete temp;
    return true;
}

template <typename T>
bool ListaDobleLigada<T>::eliminarDato(T dato){
    NodoDLL<T> *temp = head;
    if (!head){ 
        return false;
    }

    while (dato != temp->dato){
        temp = temp->next;
    }

    if (temp == head){
        temp->next->before = nullptr;
        head = temp->next;
    } else {
        temp->before->next = temp->next;
    }

    if (temp == tail){
        temp->before->next = nullptr;
        tail = temp->before;
    } else {
        temp->next->before = temp->before;
    }

    delete temp;
    return true;
}