// Crea un arbol binario para organizar datos y contiene funciones para interactuar con el.
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include <iostream>
using namespace std;

template <typename t>
class NodoArbolBinario {
    public: 
        t dato;
        NodoArbolBinario<t> *left;
        NodoArbolBinario<t> *right;

        // Constructor: Inicializa un nodo con valores por defecto.
        NodoArbolBinario(): dato(t()), left(nullptr), right(nullptr) {}

        // Destructor: Libera los recursos asociados al nodo.
        ~NodoArbolBinario(){}
};

template <typename t>
class ArbolBinario {
    private:
        NodoArbolBinario<t> *root;

        // Inserta recursivamente un dato en el árbol.
        // Parámetros:
        //   nodo - referencia al nodo donde se está realizando la inserción.
        //   dato - valor a insertar en el árbol.
        // Retorno:
        //   true si la inserción es exitosa, false en caso contrario.
        bool insertaRecursivamente(NodoArbolBinario<t> *&nodo, t dato);

        // Busca recursivamente un nodo que contenga el dato especificado.
        // Parámetros:
        //   nodo - referencia al nodo donde comienza la búsqueda.
        //   dato - valor a buscar en el árbol.
        // Retorno:
        //   Referencia al nodo encontrado, o nullptr si no se encuentra.
        NodoArbolBinario<t> *&buscarRecursivamente(NodoArbolBinario<t> *&nodo, t dato);

        // Borra recursivamente todos los nodos a partir de una rama.
        // Parámetros:
        //   nodo - nodo a partir del cual se eliminarán los nodos.
        // Retorno:
        //   true si se eliminaron los nodos correctamente.
        bool borrarRama(NodoArbolBinario<t> *nodo);

        // Recorre e imprime los nodos del árbol en orden InOrder.
        // Parámetros:
        //   actual - nodo desde donde comienza el recorrido.
        // Retorno:
        //   true si el recorrido fue exitoso.
        bool ramaInOrder(NodoArbolBinario<t> *actual);

        // Recorre e imprime los nodos del árbol en orden PreOrder.
        // Parámetros:
        //   actual - nodo desde donde comienza el recorrido.
        // Retorno:
        //   true si el recorrido fue exitoso.
        bool ramaPreOrder(NodoArbolBinario<t> *actual);

        // Recorre e imprime los nodos del árbol en orden PostOrder.
        // Parámetros:
        //   actual - nodo desde donde comienza el recorrido.
        // Retorno:
        //   true si el recorrido fue exitoso.
        bool ramaPostOrder(NodoArbolBinario<t> *actual);

    public:
        // Constructor: Inicializa un árbol binario vacío.
        ArbolBinario(): root(nullptr){}

        // Destructor: Elimina todos los nodos del árbol al destruir el objeto.
        ~ArbolBinario(){
            borrarArbol();
        }

        // Inserta un dato en el árbol binario.
        // Parámetros:
        //   dato - valor a insertar en el árbol.
        // Retorno:
        //   true si la inserción es exitosa.
        bool inserta(t dato);

        // Busca un nodo que contenga el dato especificado.
        // Parámetros:
        //   dato - valor a buscar en el árbol.
        // Retorno:
        //   Referencia al nodo encontrado o nullptr si no se encuentra.
        NodoArbolBinario<t> *&buscarNodo(t dato);

        // Imprime los nodos del árbol en orden InOrder.
        // Retorno:
        //   true si la impresión es exitosa.
        bool imprimeInOrder();

        // Imprime los nodos del árbol en orden PreOrder.
        // Retorno:
        //   true si la impresión es exitosa.
        bool imprimePreOrder();

        // Imprime los nodos del árbol en orden PostOrder.
        // Retorno:
        //   true si la impresión es exitosa.
        bool imprimePostOrder();

        // Borra un nodo que contenga el dato especificado.
        // Parámetros:
        //   dato - valor a eliminar del árbol.
        // Retorno:
        //   true si el nodo se elimina correctamente.
        bool borrarNodo(t dato);

        // Elimina todos los nodos del árbol, dejando el árbol vacío.
        // Retorno:
        //   true si el árbol se elimina correctamente.
        bool borrarArbol();

        // Devuelve el valor del nodo raíz.
        // Retorno:
        //   El valor del dato en la raíz del árbol.
        t getRootMonstruo(){return root->dato;}
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

