#pragma once

template <typename T>
class NodoListaDL{
public:
    T                   info;
    NodoListaDL<T>      *next;
    NodoListaDL<T>      *prev;
    NodoListaDL(T dato) : info(dato), next(nullptr), prev(nullptr) {}
};

template <typename T>
class ListaDL{
private:
    NodoListaDL<T>   *head;
    int size;
public:
    ListaDL(){
        head = nullptr;
        size = 0;
    }
    ~ListaDL(){
        borrar();
    }

    int getSize() {
        return size;
    }

    bool insertarFinal(T dato){
        NodoListaDL<T> *nuevo = nullptr, *tmp = nullptr;

        nuevo = new(std::nothrow) NodoListaDL<T>(dato);
        if(!nuevo)
            return false;

        if(!head) {
            head = nuevo;
            size ++;
            return true;
        }

        tmp = head;
        while(tmp->next) {
            tmp = tmp->next;
        }
        
        tmp->next = nuevo;
        nuevo->prev = tmp;
        size ++;
        return true;
    }  

    void borrar() {
        while(head) {
            NodoListaDL<T> *siguiente = nullptr;

            siguiente = head->next;
            delete head;
            head = siguiente;
        }
        size = 0;
    }

    T* buscar(T dato) {
        NodoListaDL<T> *actual = nullptr;

        actual = head;
        while(actual != nullptr) {
            if(actual->info == dato)
                return &(actual->info);
            else
                actual = actual->next;
        }
        return nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const ListaDL& lista) {
        NodoListaDL<T> *tmp = nullptr;

        tmp = lista.head;
        while(tmp) {
            os << tmp->info << " ";
            tmp = tmp->next;
        }
        os << std::endl;
        return os;
    }
};
