#include <iostream>

using namespace std;

template <typename t>
class NodoArbolAVL {
    public: 
        t dato;
        int alturaNodo;
        NodoArbolAVL<t> *left;
        NodoArbolAVL<t> *right;
        NodoArbolAVL(): dato(t()), left(nullptr), right(nullptr), alturaNodo(0) {}
};

template <typename t>
class ArbolAVL {
    private:
        NodoArbolAVL<t> *root;

        bool insertaRecursivamente(NodoArbolAVL<t> *&nodo, t dato);
        NodoArbolAVL<t> *&buscarRecursivamente(NodoArbolAVL<t> *&nodo, t dato);
        bool borrarNodoRecursivamente(NodoArbolAVL<t> *&actual, t dato);

        void balancea(NodoArbolAVL<t> *&actual);
        void calculaAltura(NodoArbolAVL<t> *&actual);
        int getAltura(NodoArbolAVL<t> *actual);
        int revisaBalance(NodoArbolAVL<t> *actual);

        NodoArbolAVL<t> *rotacionDerecha(NodoArbolAVL<t> *actual);
        NodoArbolAVL<t> *rotacionIzquierdaDerecha(NodoArbolAVL<t> *actual);
        NodoArbolAVL<t> *rotacionIzquierda(NodoArbolAVL<t> *actual);
        NodoArbolAVL<t> *rotacionDerechaIzquierda(NodoArbolAVL<t> *actual);

        bool borrarRama(NodoArbolAVL<t> *nodo);
        bool ramaInOrder(NodoArbolAVL<t> *actual);
        bool ramaPreOrder(NodoArbolAVL<t> *actual);
        bool ramaPostOrder(NodoArbolAVL<t> *actual);

    public:
        ArbolAVL(): root(nullptr){}
        ~ArbolAVL(){borrarArbol();}

        bool inserta(t dato);
        NodoArbolAVL<t> *&buscarNodo(t dato);

        bool imprimeInOrder();
        bool imprimePreOrder();
        bool imprimePostOrder();
        bool borrarNodo(t dato);
        bool borrarArbol();

};

template <typename t>
bool ArbolAVL<t>::inserta(t dato){
    return insertaRecursivamente(root, dato);
}

template <typename t>
bool ArbolAVL<t>::insertaRecursivamente(NodoArbolAVL<t> *&actual, t dato){
    if (!actual){
        actual = new(nothrow) NodoArbolAVL<t>;
        if (!actual)
            return false;
        actual->dato = dato;
        return true;
    }
    if (actual->dato > dato) {
        if (insertaRecursivamente(actual->left, dato)){
            calculaAltura(actual);
            balancea(actual);
            return true;
        } else {
            return false;
        }
    }
    else if (actual->dato < dato){
        if (insertaRecursivamente(actual->right, dato)){
            calculaAltura(actual);
            balancea(actual);
            return true;
        } else {
            return false;
        }
    }
    return false;
}

template <typename t>
bool ArbolAVL<t>::borrarNodo(t dato){
    return borrarNodoRecursivamente(root, dato);
}

template <typename t>
bool ArbolAVL<t>::borrarNodoRecursivamente(NodoArbolAVL<t> *&actual, t dato){
    if (!actual){
        return false;
    }
    if (actual->dato > dato){
        if (!borrarNodoRecursivamente(actual->left, dato)){
            return false;
        }
    }
    else if (actual->dato < dato){
        if (!borrarNodoRecursivamente(actual->right, dato)){
            return false;
        }
    }
    else {
        NodoArbolAVL<t> *borrar = actual;
        NodoArbolAVL<t> *temp = nullptr;
        NodoArbolAVL<t> *padreTemp = nullptr;

        if (!actual->left)
            actual = actual->right;
        else if (!actual->right)
            actual = actual->left;
        else {
            temp = actual->left;
            padreTemp = temp;

            while (temp->right){
                padreTemp = temp;
                temp = temp->right;
            }
            actual->dato = temp->dato;

            if (temp == actual->left){
                actual->left = nullptr;
            }
            borrar = temp;
            padreTemp->right = nullptr;
        }
        delete borrar;
    }

    if (actual) {
        calculaAltura(actual);
        balancea(actual);
    }

    return true;
}

template <typename t>
void ArbolAVL<t>::balancea(NodoArbolAVL<t> *&actual){
    int balance = revisaBalance(actual);

    if (balance > 1){
        int balanceLeft = revisaBalance(actual->left);

        if (balanceLeft >= 0)
            actual = rotacionDerecha(actual);
        else
            actual = rotacionIzquierdaDerecha(actual);
    }

    if (balance < -1){
        int balanceRight = revisaBalance(actual->right);
        
        if (balanceRight <= 0)
            actual = rotacionIzquierda(actual);
        else
            actual = rotacionDerechaIzquierda(actual);
    }
}

template <typename t>
void ArbolAVL<t>::calculaAltura(NodoArbolAVL<t> *&actual){
    if (actual)
        actual->alturaNodo = 1 + max(getAltura(actual->left), getAltura(actual->right));
}

template <typename t>
int ArbolAVL<t>::getAltura(NodoArbolAVL<t> *actual){
    if (actual)
        return actual->alturaNodo;
    return -1;
}

template <typename t>
int ArbolAVL<t>::revisaBalance(NodoArbolAVL<t> *actual){
    if (!actual)
        return -1;
    return getAltura(actual->left) - getAltura(actual->right);
}

template <typename t>
NodoArbolAVL<t> *ArbolAVL<t>::rotacionDerecha(NodoArbolAVL<t> *actual){
    NodoArbolAVL<t>* tempLeft = actual->left;
    NodoArbolAVL<t>* tempLeftRight = tempLeft->right;

    tempLeft->right = actual;
    actual->left = tempLeftRight;

    calculaAltura(actual);
    calculaAltura(tempLeft);

    return tempLeft;
}

template <typename t>
NodoArbolAVL<t> *ArbolAVL<t>::rotacionIzquierda(NodoArbolAVL<t> *actual){
    NodoArbolAVL<t>* tempRight = actual->right;
    NodoArbolAVL<t>* tempRightLeft = tempRight->left;

    tempRight->left = actual;
    actual->right = tempRightLeft;

    calculaAltura(actual);
    calculaAltura(tempRight);

    return tempRight;
}

template <typename t>
NodoArbolAVL<t> *ArbolAVL<t>::rotacionDerechaIzquierda(NodoArbolAVL<t> *actual){
    actual->right = rotacionDerecha(actual->right);
    return rotacionIzquierda(actual);
}

template <typename t>
NodoArbolAVL<t> *ArbolAVL<t>::rotacionIzquierdaDerecha(NodoArbolAVL<t> *actual){
    actual->left = rotacionIzquierda(actual->left);
    return rotacionDerecha(actual);
}

template <typename t>
bool ArbolAVL<t>::borrarArbol(){
    if (!root)
        return false;

    borrarRama(root);
    root = nullptr;
    return true;
}

template <typename t>
bool ArbolAVL<t>::borrarRama(NodoArbolAVL<t> *actual){
    
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
bool ArbolAVL<t>::imprimeInOrder(){
    if (!root)
        return false;

    ramaInOrder(root);
    return true;
}

template <typename t>
bool ArbolAVL<t>::ramaInOrder(NodoArbolAVL<t> *actual){
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
bool ArbolAVL<t>::imprimePreOrder(){
    if (!root)
        return false;

    ramaPreOrder(root);
    return true;
}

template <typename t>
bool ArbolAVL<t>::ramaPreOrder(NodoArbolAVL<t> *actual){
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
bool ArbolAVL<t>::imprimePostOrder(){
    if (!root)
        return false;

    ramaPostOrder(root);
    return true;
}

template <typename t>
bool ArbolAVL<t>::ramaPostOrder(NodoArbolAVL<t> *actual){
    if (actual->left){
        ramaPostOrder(actual->left);
    }
    if (actual->right){
        ramaPostOrder(actual->right);
    }
    cout << actual->dato << endl;
    return true;
}

template <typename t>
NodoArbolAVL<t> *&ArbolAVL<t>::buscarNodo(t dato){
    return buscarRecursivamente(root, dato);
}

template <typename t>
NodoArbolAVL<t> *&ArbolAVL<t>::buscarRecursivamente(NodoArbolAVL<t> *&actual, t dato){
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
