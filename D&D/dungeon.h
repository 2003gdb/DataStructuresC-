// Crea una Dungeon con forma de Grafo, con cuartos adentro, que tienen un tipo de dato
// Carlos A Galvez Diaz Barriga - A01067590
// 24/11/24

#include <iostream>
#include "graph.h"
using namespace std;

class Cuarto {
    public:
        Monster monstruo;

        // Sobrecarga del operador << para imprimir el contenido del cuarto.
        // Parámetros:
        //   os - el stream de salida.
        //   cuarto - la instancia de Cuarto que será impresa.
        // Retorno:
        //   El stream de salida con la información del cuarto.
        friend ostream& operator<<(ostream& os, const Cuarto& cuarto) {
            os << "Cuarto con " << cuarto.monstruo;
            return os; 
        }

        // Constructor por defecto de Cuarto.
        Cuarto() {}

        // Constructor que inicializa el cuarto con un monstruo.
        // Parámetros:
        //   monstruo - el monstruo que se almacenará en el cuarto.
        Cuarto(Monster& monstruo) { this->monstruo = monstruo; }
};

class Dungeon {
    public:
        Graph<Cuarto> grafo;
        ListaLigada<Cuarto> ruta;
        ListaLigada<Cuarto>:: iterator current;

        // Constructor por defecto de Dungeon.
        Dungeon() {}

        // Destructor de Dungeon.
        ~Dungeon() {}

        // Crea un nuevo cuarto en el dungeon con el monstruo proporcionado.
        // Parámetros:
        //   monstruo - el monstruo que se agregará en el cuarto.
        // Retorno:
        //   true si se creó el cuarto exitosamente, false en caso contrario.
        bool createRoom(unsigned int index, Monster& monstruo);

        // Imprime todos los cuartos del dungeon.
        // Retorno:
        //   true si la lista de cuartos tiene elementos, false si está vacía.
        bool imprimeCuartos();

        // Imprime todos los cuartos del dungeon.
        // Retorno:
        //   true si la lista de cuartos tiene elementos, false si está vacía.
        bool createDungeon(const string& filename);

        // Regresa el numero de Cuartos en la Dungeon.
        // Retorno:
        //   Regresa el numero de cuartos en la Dungeon.
        int getSize();

        // Crea una lista ligada con cuartos, que trazan la ruta de un cuarto a otro.
        // Retorno:
        //  true si fue exitoso, false lo contrario.
        bool trazaRuta(unsigned int inicio, unsigned int final);

        // Regresa el cuarto actual en el que se esta de la ruta.
        // Retorno:
        // Un apuntador al cuarto actual.
        Cuarto *cuartoActualRuta();

        // Avanza al siguiente cuarto de la ruta (Lista Ligada)
        // Retorno:
        //  true si fue exitoso, false lo contrario.
        bool avanzaRuta();
};

int Dungeon::getSize(){
    return grafo.getSize();
}

bool Dungeon::createDungeon(const string& filename){
    return grafo.loadFile(filename);
}

bool Dungeon::createRoom(unsigned int index, Monster& monstruo){
    Cuarto cuarto(monstruo);
    return grafo.setVertex(index, cuarto);
}

bool Dungeon::imprimeCuartos(){
    if (grafo.getSize() != 0){
        grafo.print();
        return true;
    }
    return false;
}

bool Dungeon::trazaRuta(unsigned int inicio, unsigned int final){
    if (grafo.BFS_Best_Path(inicio, final, ruta)){
        current = ruta.begin();
        return true;
    }
    return false;
}

Cuarto *Dungeon::cuartoActualRuta(){
    return &(*current); 
}

bool Dungeon::avanzaRuta(){
    if (cuartoActualRuta()){
        ++current;
        return true;
    }
    return false;
}
