#include <iostream>

using namespace std;

template <typename T>
class Nodo{
    public:
        T dato;
        Nodo<T> *next;

        Nodo();
};

template <typename T>
class LinkedList{
    private:
        Nodo<T> *head;

    public:
        LinkedList();
        ~LinkedList();

        bool insertarInicio(T dato);
        bool insertarFinal(T dato);

        int cuentaMenores(T dato);
        //void destruirNodo(int datoIdentificador);
        //void imprimirLista();

        bool eliminaFinal();
        bool borraLista();
};

template <typename T>
Nodo<T>::Nodo(){
    Nodo<T> *next = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList(){
    borraLista();
    head = nullptr;
}

// complejidad (O(n))
template <typename T>
bool LinkedList<T>::borraLista(){
    Nodo<T> *destructorNodal = head, *temp = nullptr;

    if (!head){
        cout << "No hay lista " << endl;
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

// complejidad (O(n))
template <typename T>
bool LinkedList<T>::eliminaFinal(){
    Nodo<T> *temp = nullptr;
    if (!head){
        cout << "No hay lista, head = nullptr" << endl;
        return false;
    }

    temp = head;

    if (!temp->next){
        delete temp;
        temp = nullptr;
        head = nullptr;
        return true;
    }

    if (!temp->next->next){
        delete temp->next;
        temp->next = nullptr;
        return true;
    }

    while (temp->next->next) {
        temp = temp->next;
    }

    temp->next = nullptr;

    delete temp->next;
    temp = nullptr;
    return true;
}

// complejidad (O(1))
template <typename T>
bool LinkedList<T>::insertarInicio(T dato){
    Nodo<T> *nuevo = nullptr;

    nuevo = new(nothrow) Nodo<T>;
    if (!nuevo){
        // no hubo memoria
        return false;
    }
    
    if (head){
        nuevo->next = head;
    } 

    nuevo->dato = dato;
    head = nuevo;

    return true;
}

// complejidad (O(n))
template <typename T>
bool LinkedList<T>::insertarFinal(T dato){
    Nodo<T> *nuevo = nullptr;
    Nodo<T> *temp = nullptr;

    nuevo = new(nothrow) Nodo<T>;
    if (!nuevo){
        cout << "no hubo memoria" << endl;
        return false;
    }
    temp = head;
    nuevo->dato = dato;
    
    if (!head){
        head = nuevo;
        return true;
    }

    while (temp->next){
        temp = temp->next;
    }
    temp->next = nuevo; 
    return true;
}

// complejidad (O(n))
template <typename T>
int LinkedList<T>::cuentaMenores(T dato){
    Nodo<T> *temp = nullptr;
    int count = 0;

    if (!head){
        cout << "No hubo memoria" <<endl;   
        return 0;
    }
    temp = head;
    
    while (dato != temp->dato){
        count++;
        temp = temp->next;
    }

    return count;
}
