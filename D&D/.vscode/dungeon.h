// Crea una Dungeon con forma de Lista doblemente ligada, con cuartos adentro, que tienen un tipo de dato
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include <iostream>
#include "dll.h"
using namespace std;

template <typename t>
class Cuarto {
    public:
        t monstruo;

        // Sobrecarga del operador << para imprimir el contenido del cuarto.
        // Parámetros:
        //   os - el stream de salida.
        //   cuarto - la instancia de Cuarto que será impresa.
        // Retorno:
        //   El stream de salida con la información del cuarto.
        friend ostream& operator<<(ostream& os, const Cuarto& cuarto) {
            os << "Cuarto con: " << cuarto.monstruo;
            return os; 
        }

        // Constructor por defecto de Cuarto.
        Cuarto() {}

        // Constructor que inicializa el cuarto con un monstruo.
        // Parámetros:
        //   monstruo - el monstruo que se almacenará en el cuarto.
        Cuarto(t& monstruo) { this->monstruo = monstruo; }
};

template <typename t>
class Dungeon {
    public:
        ListaDobleLigada< Cuarto<t> > dll;

        // Constructor por defecto de Dungeon.
        Dungeon() {}

        // Destructor de Dungeon.
        ~Dungeon() {}

        // Crea un nuevo cuarto en el dungeon con el monstruo proporcionado.
        // Parámetros:
        //   monstruo - el monstruo que se agregará en el cuarto.
        // Retorno:
        //   true si se creó el cuarto exitosamente, false en caso contrario.
        bool createRoom(t& monstruo);

        // Imprime todos los cuartos del dungeon.
        // Retorno:
        //   true si la lista de cuartos tiene elementos, false si está vacía.
        bool imprimeCuartos();
};

template <typename t>
bool Dungeon<t>::createRoom(t& monstruo){
    Cuarto<t> cuarto(monstruo);
    return dll.insertarInicio(cuarto);
}

template <typename t>
bool Dungeon<t>::imprimeCuartos(){
    return dll.imprimirLista();
}
