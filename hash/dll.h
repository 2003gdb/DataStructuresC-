#include <iostream>

using namespace std;

template <typename T>
class NodoDLL{
    public:
        T dato;
        NodoDLL<T> *before;
        NodoDLL<T> *next;

        NodoDLL(): dato(T()), before(nullptr), next(nullptr){}
};

template <typename T>
class ListaDobleLigada{
    private:
        NodoDLL<T> *head;
        NodoDLL<T> *tail;
    
    public:
        ListaDobleLigada(): head(nullptr), tail(nullptr){}
        ~ListaDobleLigada(){
            if (!destruirLista()){
                cout << "NO se elimino correctamente" << endl;
            }
        }

        bool insertarFinal(T dato);
        bool insertarInicio(T dato);
        bool imprimirLista();
        bool destruirLista();

        void eliminarHead();
        void eliminarTail();
        void eliminarDato(T dato);

        T *buscar(T dato);
};

template <typename T>
bool ListaDobleLigada<T>::insertarFinal(T dato){
    NodoDLL<T> *nuevo = nullptr;
    NodoDLL<T> *beforeNodo = nullptr;
    NodoDLL<T> *temp = head;

    nuevo = new(nothrow) NodoDLL<T>;
    if (!nuevo)
        return false;

    
    if (!head){
        head = nuevo;
        tail = nuevo;
        return true;
    }

    while (temp->next){
        beforeNodo = temp;
        temp = temp->next;
    }
    nuevo->dato = dato;
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
        cout << temp->dato << " ";
        temp = temp->next;
    }
    cout << endl;
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
void ListaDobleLigada<T>::eliminarHead(){
    NodoDLL<T> *temp = head;
    if (!head){
        return;
    }

    if (!head->next){
        delete temp;
        head = nullptr;
        tail = nullptr;
        return;
    }

    head = head->next;
    head->before = nullptr;
    delete temp;
}

template <typename T>
void ListaDobleLigada<T>::eliminarTail(){
    NodoDLL<T> *temp = tail;
    if (!head){
        return;
    }

    if (!tail->before){
        delete temp;
        temp = nullptr;
        head = nullptr;
        tail = nullptr;
        return;
    }

    tail = temp->before;
    tail->next = nullptr;
    delete temp;
}

template <typename T>
void ListaDobleLigada<T>::eliminarDato(T dato){
    NodoDLL<T> *temp = head;
    if (!head){
        cout << "No hubo memoria" <<endl;   
        return;
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
}

template <typename T>
T *ListaDobleLigada<T>::buscar(T dato){
    NodoDLL<T> *temp = head;
    
    if (!head){
        return nullptr;
    }

    while (dato != temp->dato){
        temp = temp->next;
    }

    return temp;
}