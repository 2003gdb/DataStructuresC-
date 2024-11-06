// Crea un Jugador que actualmente solo tiene atributos y una lista ligada referenciando a los monstruos derrotados.
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include <iostream>
#include <string>
#include "ll.h"
using namespace std;

template <typename t>
class Jugador {
    private:
        ListaLigada<t> monstruosDerrotados;
        string nombreJugador;
        int hp;

    public:
        // Imprime la lista de monstruos derrotados por el jugador.
        // Retorno:
        //   true si la lista de monstruos se imprime correctamente, false si la lista está vacía.
        bool imprimirMonstruosDerrotados() {
            return monstruosDerrotados.imprimirLista();
        }

        // Inserta un monstruo en la lista de monstruos derrotados en orden.
        // Parámetros:
        //   monstruo - un puntero al monstruo que se desea insertar en la lista de monstruos derrotados.
        // Retorno:
        //   true si el monstruo se inserta correctamente, false si ocurre algún error.
        bool insertarMonstruoDerrorado(t* monstruo){
            return monstruosDerrotados.insertarInOrder(monstruo);
        }
};
