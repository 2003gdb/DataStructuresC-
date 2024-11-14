#include <iostream>
#include <sstream>
#include <fstream>
#include "ll.h"
using namespace std;

class Graph{
    public:
        Graph() {
        table = nullptr;
        size = 0;
        }
        ~Graph() { eliminateGraph(); };
        bool createGraph(unsigned int nSize);
        void eliminateGraph();
        bool insertEdge(unsigned int vertex, unsigned int edge);
        bool eliminateEdge(unsigned int vertex, unsigned int edge);
        bool loadFile(const string& filename);
        bool saveFile(const string& filename);

    private:
        ListaLigada<int> *table;
        unsigned int size;
};

bool Graph::createGraph(unsigned int nSize) {
    if(nSize == 0 || table != nullptr)
        return false;
    table = new(std::nothrow) ListaLigada<int>[nSize];
    if(!table)
        return false;
    size = nSize;
    return true;
}

void Graph::eliminateGraph() {
    if(table) {
        delete [] table;
        table = nullptr;
        size = 0;
    }
}

bool Graph::insertEdge(unsigned int vertex, unsigned int edge) {
    if (vertex < size) {
        if (table[vertex].insertar(edge))
            return true;
    } 
    return false;
}

bool Graph::eliminateEdge(unsigned int vertex, unsigned int edge) {
    if (vertex < size) {
        if (table[vertex].destruirNodo(edge))
            return true;
    } 
    return false;
}

bool Graph::loadFile(const string& filename) {
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
                insertEdge(counter, stoi(edge));
            }
        }
        counter++;
    }
    file.close();
    return true;
}

bool Graph::saveFile(const string& filename) {
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
        NodoListaLigada<int> *temp = nullptr;

        if (!table[counter].head)
            return false;
        
        temp = table[counter].head;

        while (temp){
            file << temp->dato << " ";
            temp = temp->next;
        }
        file << endl;
        counter++;
    }
    file.close();
    return true;

}