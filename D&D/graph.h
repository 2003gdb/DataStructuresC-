// Crea un Grafo para recorrer la Dungeon de diferentes maneras.
// Carlos A Galvez Diaz Barriga - A01067590
// 23/11/24

#include <iostream>
#include <sstream>
#include <fstream>
#include "ll.h"
#include "stack.h"
#include "queue.h"

template <typename t>
class Graph{
    public:
        // Constructor por defecto de Graph.
        // Inicializa el grafo con un tamaño de 0 y sin tabla.
        Graph(): arrVertex(nullptr), size(0){};

        // Destructor de Graph.
        // Libera la memoria asignada para el grafo.
        ~Graph() { eliminateGraph(); };

        // Crea un grafo de tamaño nSize, inicializando un arreglo de vértices.
        // Parámetros:
        //   nSize - el tamaño del grafo (número de vértices).
        // Retorno:
        //   true si el grafo se creó exitosamente; false en caso contrario.
        bool createGraph(unsigned int nSize);

        // Elimina el grafo, liberando la memoria asignada.
        void eliminateGraph();

        // Inserta una arista entre dos vértices.
        // Parámetros:
        //   vertex - índice del vértice de origen.
        //   edge - índice del vértice de destino.
        // Retorno:
        //   true si la arista se insertó exitosamente, false en caso contrario.
        bool insertEdge(unsigned int vertex, unsigned int edge);

        // Elimina una arista entre dos vértices.
        // Parámetros:
        //   vertex - índice del vértice de origen.
        //   edge - índice del vértice de destino.
        // Retorno:
        //   true si la arista se eliminó exitosamente, false en caso contrario.
        bool eliminateEdge(unsigned int vertex, unsigned int edge);

        // Carga un grafo desde un archivo.
        // Parámetros:
        //   filename - nombre del archivo que contiene la representación del grafo.
        // Retorno:
        //   true si el archivo se cargó exitosamente, false en caso contrario.
        bool loadFile(const string& filename);

        // Guarda el grafo en un archivo.
        // Parámetros:
        //   filename - nombre del archivo donde se guardará la representación del grafo.
        // Retorno:
        //   true si el grafo se guardó exitosamente, false en caso contrario.
        bool saveFile(const string& filename);

        // Asigna un valor a un vértice específico.
        // Parámetros:
        //   index - índice del vértice al que se asignará el dato.
        //   dato - valor que se asignará al vértice.
        // Retorno:
        //   true si el dato se asignó exitosamente, false en caso contrario.
        bool setVertex(unsigned int index, t dato);

        // Imprime el grafo en la consola.
        void print();

        // Obtiene el tamaño del grafo (número de vértices).
        // Retorno:
        //   Número de vértices en el grafo.
        int getSize(){return size;};

        // Realiza una búsqueda en profundidad (DFS) a partir del vértice inicial.
        // Parámetros:
        //   startVertex - índice del vértice desde el cual iniciar la búsqueda.
        // Retorno:
        //   true si la búsqueda se realizó exitosamente; false en caso contrario.
        bool DFS(unsigned int startVertex);

        // Encuentra el mejor camino entre dos vértices usando una búsqueda en amplitud (BFS).
        // Parámetros:
        //   startVertex - índice del vértice de inicio.
        //   endVertex - índice del vértice de destino.
        //   path - referencia a una lista ligada donde se almacenará el mejor camino encontrado.
        // Retorno:
        //   true si se encontró un camino entre los vértices; false en caso contrario.
        bool BFS_Best_Path(unsigned int startVertex, unsigned int endVertex, ListaLigada<t> &path);

        class Vertex {
            public:
                // Lista de aristas conectadas al vértice.
                ListaLigada<unsigned int> edges;
                // Dato almacenado en el vértice.
                t dato;
        };

    private:
        // Arreglo dinámico que almacena los vértices del grafo.
        Vertex *arrVertex;
        // Tamaño del grafo (número de vértices).
        unsigned int size;
};

template <typename t>
bool Graph<t>::BFS_Best_Path(unsigned int startVertex, unsigned int endVertex, ListaLigada<t> &path) {
    Queue<unsigned int> queue;
    if (!size || startVertex >= size)
        return false;
    
    if (!queue.enqueue(startVertex))
        return false;

    bool *vertexVisited = new(std::nothrow) bool[size];
    if (!vertexVisited)
        return false;

    for (unsigned int i = 0; i < size; ++i) {
        vertexVisited[i] = false;
    }

    unsigned int *previousVertex = new(std::nothrow) unsigned int[size];
    if (!previousVertex){
        delete[] vertexVisited;
        return false;
    }

    vertexVisited[startVertex] = true;
    unsigned int currentVertex = 0;

    while (!queue.isEmpty()) {
        unsigned int currentVertex = *queue.getFront();
        if (!queue.dequeue()){
            delete[] vertexVisited;
            delete[] previousVertex;
            return false;
        }

        if (currentVertex >= size) {
            delete[] vertexVisited;
            delete[] previousVertex;
            return false;
        }

        ListaLigada<unsigned int>:: iterator it(nullptr);
        for (it = arrVertex[currentVertex].edges.begin(); it != arrVertex[currentVertex].edges.end(); ++it) {
            if (!vertexVisited[*it]) {
                if (!queue.enqueue(*it)){
                    delete[] vertexVisited;
                    delete[] previousVertex;
                    return false;
                }
                vertexVisited[*it] = true;
                previousVertex[*it] = currentVertex;

                if (*it == endVertex) {
                    Stack<unsigned int> stack;

                    int current = endVertex;
                    while (current != startVertex) {
                        if (!stack.push(current)){
                            delete[] vertexVisited;
                            delete[] previousVertex;
                            return false;
                        }
                        current = previousVertex[current];
                    }
                    if (!stack.push(startVertex)){
                        delete[] vertexVisited;
                        delete[] previousVertex;
                        return false;
                    }
                    while (!stack.isEmpty()){
                        std::cout << *stack.getTop() << " ";
                        path.insertar(arrVertex[*stack.getTop()].dato);
                        stack.pop();
                    }
                    std::cout << endl;
                    delete[] vertexVisited;
                    delete[] previousVertex;
                    return true;
                }
            }
        }
    }
    delete[] vertexVisited;
    delete[] previousVertex;
    return false;
}

template <typename t>
bool Graph<t>::DFS(unsigned int startVertex){
    if (!size || startVertex >= size)
        return false;

    Stack<unsigned int> stack;
    if (!stack.push(startVertex)){return false;}
    std::cout << "DFS (" << startVertex << "): ";

    bool *vertexVisited = new(std::nothrow) bool[size];
    for (unsigned int i = 0; i < size; ++i) {
        vertexVisited[i] = false;
    }

    while (!stack.isEmpty()) {
        unsigned int currentVertex = *stack.getTop();
        if (!stack.pop()){
            delete[] vertexVisited;
            return false;
        }

        if (!vertexVisited[currentVertex]) {
            vertexVisited[currentVertex] = true;
            std::cout << currentVertex << " ";

            ListaLigada<unsigned int>:: iterator it(nullptr);
            for (it = arrVertex[currentVertex].edges.begin(); it != arrVertex[currentVertex].edges.end(); ++it) {
                if (!vertexVisited[*it]) {
                    if (!stack.push(*it)){
                        delete[] vertexVisited;
                        return false;
                    }
                }
            }
        }
    }
    std::cout << "\n";
    delete[] vertexVisited;
    return true;
}

template <typename t>
void Graph<t>::print(){
    for (int i = 0; i < size; i++) {
        std::cout << "[" << i << "]"<< arrVertex[i].dato << " : ";
        arrVertex[i].edges.imprimirLista();
    }
}

template <typename t>
bool Graph<t>::setVertex(unsigned int index, t dato){
    if (!size || index >= size) {
        return false;
    } 
    arrVertex[index].dato = dato;
    return true;
}

template <typename t>
bool Graph<t>::createGraph(unsigned int nSize) {
    if(nSize == 0 || arrVertex)
        return false;
    arrVertex = new(std::nothrow) Vertex[nSize];
    if(!arrVertex)
        return false;
    size = nSize;
    return true;
}

template <typename t>
void Graph<t>::eliminateGraph() {
    if(arrVertex) {
        delete [] arrVertex;
        arrVertex = nullptr;
        size = 0;
    }
}

template <typename t>
bool Graph<t>::insertEdge(unsigned int vertex, unsigned int edge) {
    if (vertex < size || !arrVertex[vertex].edges.search(edge)) {
        if (arrVertex[vertex].edges.insertar(edge))
            return true;
    } 
    return false;
}

template <typename t>
bool Graph<t>::eliminateEdge(unsigned int vertex, unsigned int edge) {
    if (vertex < size) {
        if (arrVertex[vertex].edges.destruirNodo(edge))
            return true;
    } 
    return false;
}

template <typename t>
bool Graph<t>::loadFile(const string& filename) {
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

    int counter = -1;
    while (getline(file, line)){
        stringstream ss(line);
        string edge;

        if (counter == -1){
            size = stoi(line);
            createGraph(size);
        } else {
            while (getline(ss, edge, ' ')){
                if(!insertEdge(counter, stoi(edge)))
                    return false;
            }
        }
        counter++;
    }
    file.close();
    return true;
}

template <typename t>
bool Graph<t>::saveFile(const string& filename) {
    ofstream file;

    file.open(filename);
    if (!file.is_open()){
        cerr << "Error al abrir el archivo" << filename  << endl;
        return false;
    }

    file << "Grafo" << endl;
    file << size << endl;

    int counter = 0;
    while (counter < size){
        ListaLigada<unsigned int>:: iterator j(nullptr);
        
        for (j = arrVertex[counter].edges.begin(); j != arrVertex[counter].edges.end(); ++j) {
            file << *j << ' ';
        }
        file << endl;
        counter++;
    }
    file.close();
    return true;

}