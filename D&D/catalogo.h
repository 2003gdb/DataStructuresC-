// Crea un Catalogo de datos con un Arbol binario y una funcion para cargar datos en el arbol y sacar un nodo aleatorio.
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include "monstruo.h"
#include "arbolbinario.h"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

template <typename t>
class Catalogo {
    private:
        ArbolBinario<t> arbol;

        // Selecciona recursivamente un nodo aleatorio en el árbol.
        // Parámetros:
        //   nodo - referencia al nodo desde donde comienza la búsqueda.
        //   chosenNodo - nodo aleatorio seleccionado.
        //   actual - puntero al contador de nodos visitados.
        //   randNum - número aleatorio para seleccionar el nodo.
        void getRandomNodoRecursivo(NodoArbolBinario<t>*& nodo, NodoArbolBinario<t>*& chosenNodo, int *actual, int randNum);
    
    public:
        // Constructor: Inicializa el catálogo y establece el tamaño a cero.
        Catalogo(){}

        // Destructor: No realiza ninguna acción especial.
        ~Catalogo(){}

        // Carga los datos del catálogo desde un archivo CSV.
        // Parámetros:
        //   filename - nombre del archivo CSV a cargar.
        // Retorno:
        //   true si la carga es exitosa, false en caso de error.
        bool loadFromCSV(const string& filename);

        // Devuelve un monstruo seleccionado aleatoriamente del catálogo.
        // Retorno:
        //   Monstruo seleccionado aleatoriamente.
        t *getRandomMonster();
};

template <typename t>
t *Catalogo<t>::getRandomMonster() {
    return arbol.getRandomNodo();
}

template <typename t>
bool Catalogo<t>::loadFromCSV(const string& filename){
    ifstream file;
    string line;

    file.open(filename);
    if (!file.is_open()){
        cerr << "Error al abrir el archivo" << filename  << endl;
        return false;
    }

    if (!getline(file, line)){
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo de criaturas" << endl;
    int counter;
    while (getline(file, line)){
        Monster monstruo;
        stringstream ss(line);
        string celda;
        counter = 1;

        while (getline(ss, celda, ',')){
            if (counter == 1)
                monstruo.setName(celda);
            else if (counter == 2)
                monstruo.setCr(stod(celda));  
            else if (counter == 3)
                monstruo.setType(celda);
            else if (counter == 4)
                monstruo.setSize(celda);
            else if (counter == 5)
                monstruo.setAc(stoi(celda));  
            else if (counter == 6)
                monstruo.setHp(stoi(celda));  
            else if (counter == 7)
                monstruo.setAlign(celda);
            counter++;
        }

        if (!arbol.inserta(monstruo)){
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

