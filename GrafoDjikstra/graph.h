#include <iostream>
#include <sstream>
#include <fstream>
#include "ll.h"
#include "stack.h"
#include "queue.h"

template <typename t>
class Graph{
    public:
        Graph() {
        arrVertex = nullptr;
        size = 0;
        }
        ~Graph() { eliminateGraph(); };
        bool createGraph(unsigned int nSize);
        void eliminateGraph();
        bool insertEdge(unsigned int vertex, unsigned int edge, unsigned int weight);
        bool eliminateEdge(unsigned int vertex, unsigned int edge);
        bool loadFile(const string& filename);
        bool saveFile(const string& filename);
        bool setVertex(unsigned int index, t dato);
        void print();
        int getSize(){return size;};

        bool DFS(unsigned int startVertex);
        bool BFS_Best_Path(unsigned int startVertex, unsigned int endVertex, ListaLigada<t> &path);

        class Edges {
            public:
                unsigned int weight;
                unsigned int vertex_index;
                Edges() : vertex_index(0), weight(0) {}
                Edges(unsigned int vertex_index, unsigned int weight): vertex_index(vertex_index), weight(weight) {}
        };

        class Vertex {
            public:
                ListaLigada<Edges> edges;
                t dato;
        };

    private:
        Vertex *arrVertex;
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
        queue.dequeue();
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
                        stack.push(current);
                        current = previousVertex[current];
                    }
                    stack.push(startVertex);
                    while (!stack.isEmpty()){
                        path.insertar(arrVertex[*stack.getTop()].dato);
                        stack.pop();
                    }

                    delete[] vertexVisited;
                    delete[] previousVertex;
                    return true;
                }
            }
        }
    }
    std::cout << "END VERTEX NOT FOUND" << endl;
    delete[] vertexVisited;
    delete[] previousVertex;
    return false;
}

template <typename t>
bool Graph<t>::DFS(unsigned int startVertex){
    if (!size || startVertex >= size)
        return false;

    Stack<unsigned int> stack;
    stack.push(startVertex);
    std::cout << "DFS (" << startVertex << "): ";

    bool *vertexVisited = new(std::nothrow) bool[size];
    for (unsigned int i = 0; i < size; ++i) {
        vertexVisited[i] = false;
    }

    while (!stack.isEmpty()) {
        unsigned int currentVertex = *stack.getTop();
        stack.pop();

        if (!vertexVisited[currentVertex]) {
            vertexVisited[currentVertex] = true;
            std::cout << currentVertex << " ";

            ListaLigada<unsigned int>:: iterator it(nullptr);
            for (it = arrVertex[currentVertex].edges.begin(); it != arrVertex[currentVertex].edges.end(); ++it) {
                if (!vertexVisited[*it]) {
                    stack.push(*it);
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
    for (int currentVertex = 0; currentVertex < size; currentVertex++) {
        std::cout << "[" << currentVertex << "]"<< arrVertex[currentVertex].dato << ":";

        typename ListaLigada<Graph<t>::Edges>:: iterator it(nullptr);
        for (it = arrVertex[currentVertex].edges.begin(); it != arrVertex[currentVertex].edges.end(); ++it) {
            std::cout << " e." << (*it).vertex_index << " w." << (*it).weight << " |||" ;
        }
        cout << endl;
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
bool Graph<t>::insertEdge(unsigned int vertex, unsigned int edge_index, unsigned int weight) {
    if (vertex < size) { // Falta revisar, que no se repita el numero en la lista ligada de edges
        Edges edge(edge_index, weight);
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
    int weight;
    while (getline(file, line)){
        stringstream ss(line);
        string edge;

        if (counter == -1){
            size = stoi(line);
            createGraph(size);
        } else {
            while (getline(ss, edge, ' ')){ 
                weight = stoi(edge) % counter;
                insertEdge(counter, stoi(edge), weight);
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
        typename ListaLigada<Graph<t>::Edges>:: iterator j(nullptr);
        
        for (j = arrVertex[counter].edges.begin(); j != arrVertex[counter].edges.end(); ++j) {
            file << (*j).vertex_index << ' ';
        }
        file << endl;
        counter++;
    }
    file.close();
    return true;

}