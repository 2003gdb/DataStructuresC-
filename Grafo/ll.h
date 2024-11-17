#include <iostream>
using namespace std;

template <typename t>
class NodoListaLigada{
    public:
        t dato;
        NodoListaLigada<t> *next;

        NodoListaLigada(): dato(t()), next(nullptr){}
};

template <typename t>
class ListaLigada{
    private:
        NodoListaLigada<t> *head;
    public:
        ListaLigada() : head(nullptr){}
        ~ListaLigada(){
            if (!destruirLista()){
                cout << "No se pudo destruir Lista" << endl;
            }
        }
        bool insertar(t dato);
        bool destruirNodo(t datoIdentificador);
        bool imprimirLista();
        bool destruirLista();

        class iterator {
            public:
                iterator(NodoListaLigada<t>* node) : current(node) {}

                t& operator*() {
                    return current->dato;
                }

                iterator& operator++() {
                    if(current)
                        current = current->next;
                    return *this;
                }

                bool operator==(const iterator& other) const {
                    return current == other.current;
                }

                bool operator!=(const iterator& other) const {
                    return current != other.current;
                }

            private:
                NodoListaLigada<t>* current;
            };

            iterator begin() {
                return iterator(head);
            }

            iterator end() {
               return iterator(nullptr);
            }
};

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
        cout << temp->dato;
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

