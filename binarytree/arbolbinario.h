#include <iostream>
#include "queue.h"

using namespace std;

template <typename t>
class NodoArbolBinario {
    public: 
        t dato;
        NodoArbolBinario<t> *left;
        NodoArbolBinario<t> *right;
        NodoArbolBinario(): dato(t()), left(nullptr), right(nullptr) {}

        ~NodoArbolBinario(){}
};

template <typename t>
class ArbolBinario {
    private:
        NodoArbolBinario<t> *root;
        bool insertaRecursivamente(NodoArbolBinario<t> *&nodo, t dato);
        NodoArbolBinario<t> *&buscarRecursivamente(NodoArbolBinario<t> *&nodo, t dato);

        bool borrarRama(NodoArbolBinario<t> *nodo);
        bool ramaInOrder(NodoArbolBinario<t> *actual);
        bool ramaPreOrder(NodoArbolBinario<t> *actual);
        bool ramaPostOrder(NodoArbolBinario<t> *actual);

    public:
        ArbolBinario(): root(nullptr){}

        ~ArbolBinario(){
            borrarArbol();
        }

        bool inserta(t dato);
        NodoArbolBinario<t> *&buscarNodo(t dato);

        bool imprimeInOrder();
        bool imprimePreOrder();
        bool imprimePostOrder();
        bool imprimeBFS();
        bool borrarNodo(t dato);

        bool borrarArbol();

};

template <typename t>
bool ArbolBinario<t>::inserta(t dato){
    return insertaRecursivamente(root, dato);
}

template <typename t>
bool ArbolBinario<t>::insertaRecursivamente(NodoArbolBinario<t> *&actual, t dato){
    if (!actual){
        actual = new(nothrow) NodoArbolBinario<t>;
        if (!actual)
            return false;
        actual->dato = dato;
        return true;
    }
    if (actual->dato > dato)
        return insertaRecursivamente(actual->left, dato);
    else if (actual->dato < dato)
        return insertaRecursivamente(actual->right, dato);
    
    return false;
}

template <typename t>
NodoArbolBinario<t> *&ArbolBinario<t>::buscarNodo(t dato){
    return buscarRecursivamente(root, dato);
}

template <typename t>
NodoArbolBinario<t> *&ArbolBinario<t>::buscarRecursivamente(NodoArbolBinario<t> *&actual, t dato){
    if (!actual){
        return actual;
    }
    if (actual->dato > dato)
        return buscarRecursivamente(actual->left, dato);
    else if (actual->dato < dato)
        return buscarRecursivamente(actual->right, dato);
    else {
        return actual;
    }
}

template <typename t>
bool ArbolBinario<t>::borrarArbol(){
    if (!root)
        return false;

    borrarRama(root);
    root = nullptr;
    return true;
}

template <typename t>
bool ArbolBinario<t>::borrarRama(NodoArbolBinario<t> *actual){
    
    if (actual->left){
        borrarRama(actual->left);
    }
    if (actual->right){
        borrarRama(actual->right);
    }
    delete actual;
    return true;
}

template <typename t>
bool ArbolBinario<t>::borrarNodo(t dato){ 
    NodoArbolBinario<t> *temp = nullptr;
    NodoArbolBinario<t> *ptr = nullptr;
    NodoArbolBinario<t> *actual = nullptr;

    if (!buscarNodo(dato)) {
        return false;
    }

    NodoArbolBinario<t> *&direccionPtr = buscarNodo(dato);
    ptr = direccionPtr;

    if ((ptr->left) && (ptr->right)){
        temp = ptr;
        ptr = ptr->left;
        actual = ptr;

        while (ptr->right){
            actual = ptr;
            ptr = ptr->right;
        }
        temp->dato = ptr->dato;

        if (ptr == temp->left){
            temp->left = nullptr;
        }

        delete ptr;
        actual->right = nullptr;

        return true;

    } else if ((!ptr->left) && (!ptr->right)){
        delete direccionPtr;
        direccionPtr = nullptr;
        return true;

    } else if (ptr->left){
        temp = ptr->left;
        ptr->dato = ptr->left->dato;
        ptr->right = ptr->left->right;
        ptr->left = ptr->left->left;

        delete temp;
        temp = nullptr;
        ptr = nullptr;
        return true;
        
    } else if (ptr->right){
        temp = ptr->right;
        ptr->left = ptr->right->left;
        ptr->dato = ptr->right->dato;
        ptr->right = ptr->right->right;

        delete temp;
        temp = nullptr;
        ptr = nullptr;
        return true;
    }
    return true;
}

template <typename t>
bool ArbolBinario<t>::imprimeBFS(){
    Queue<NodoArbolBinario<t>*> queue;
    NodoArbolBinario<t> *ptr = nullptr;
    int numNodes;
    
    if (!root)
        return false;

    if (queue.isEmpty()){
        if (!queue.enqueue(root))
            return false;
    }

    while (!queue.isEmpty()){
        numNodes = queue.getSize();

        while (numNodes){
            ptr = *queue.getFront();
            cout << ptr->dato << " ";

            queue.dequeue();

            if (ptr->left){
                if (!queue.enqueue(ptr->left))
                    return false;
            }

            if (ptr->right){
                if (!queue.enqueue(ptr->right))
                    return false;
            }
            numNodes--;
        }
        cout << endl; 
    }
    return true;
}


template <typename t>
bool ArbolBinario<t>::imprimeInOrder(){
    if (!root)
        return false;

    ramaInOrder(root);
    return true;
}

template <typename t>
bool ArbolBinario<t>::ramaInOrder(NodoArbolBinario<t> *actual){
    if (actual->left){
        ramaInOrder(actual->left);
    }
    cout << actual->dato << endl;
    if (actual->right){
        ramaInOrder(actual->right);
    }
    return true;
}

template <typename t>
bool ArbolBinario<t>::imprimePreOrder(){
    if (!root)
        return false;

    ramaPreOrder(root);
    return true;
}

template <typename t>
bool ArbolBinario<t>::ramaPreOrder(NodoArbolBinario<t> *actual){
    cout << actual->dato << endl;
    if (actual->left){
        ramaPreOrder(actual->left);
    }
    if (actual->right){
        ramaPreOrder(actual->right);
    }
    return true;
}

template <typename t>
bool ArbolBinario<t>::imprimePostOrder(){
    if (!root)
        return false;

    ramaPostOrder(root);
    return true;
}

template <typename t>
bool ArbolBinario<t>::ramaPostOrder(NodoArbolBinario<t> *actual){
    if (actual->left){
        ramaPostOrder(actual->left);
    }
    if (actual->right){
        ramaPostOrder(actual->right);
    }
    cout << actual->dato << endl;
    return true;
}

