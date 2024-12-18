#include <iostream>

using namespace std;

template <typename t>
class NodoQueue {
    public: 
        t dato;
        NodoQueue<t> *prev;
        NodoQueue(): dato(t()), prev(nullptr) {}
};

template <typename t>
class Queue {
    private:
        NodoQueue<t> *front;
        NodoQueue<t> *back;
        int size;
    public:
        Queue(): front(nullptr), back(nullptr), size(0){}
        ~Queue(){borrarQueue();}

        bool enqueue(t dato);
        bool dequeue();
        bool isEmpty();
        t *getFront();
        int getSize(){
            return size;
        }

        bool borrarQueue();
        bool imprimirQueue();

};

template <typename t>
bool Queue<t>::enqueue(t dato){
    NodoQueue<t> *nuevo = nullptr;
    
    nuevo = new(nothrow) NodoQueue<t>;
    if (!nuevo)
        return false;

    nuevo->dato = dato;
    if (!front){
        front = nuevo;
    } else {
        back->prev = nuevo;
    }
    back = nuevo;
    size++;
    return true;
}

template <typename t>
bool Queue<t>::dequeue(){
    NodoQueue<t> *tmp = front;
    if (!front) 
        return false;
    
    if (!front->prev){
        front = nullptr;
        back = nullptr;
    } else {
        front = front->prev;
    }
    delete tmp;
    tmp = nullptr;
    size--;
    return true;
}

template <typename t>
bool Queue<t>::isEmpty(){
    return front == nullptr;
}

template <typename t>
t *Queue<t>::getFront(){
    if (!front)
        return nullptr;
    return &(front->dato);
}

template <typename t>
bool Queue<t>::borrarQueue(){
    NodoQueue<t> *tmp = nullptr;
    
    while(front){
        tmp = front;
        front = front->prev;
        delete tmp;
    }
    size = 0;
    return true;
}

template <typename t>
bool Queue<t>::imprimirQueue(){
    NodoQueue<t> *tmp = front;
    
    while(tmp){
        cout << tmp->dato << endl;
        tmp = tmp->prev;
    }
    return true;
}
