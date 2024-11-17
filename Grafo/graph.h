#include <iostream>
#include <sstream>
#include <fstream>
#include "ll.h"
using namespace std;

template <typename t>
class Graph{
    public:
        Graph() {
        table = nullptr;
        size = 0;
        }
        ~Graph() { eliminateGraph(); };
        bool createGraph(unsigned int nSize);
        void eliminateGraph();
        bool insertEdge(unsigned int vertex, int edge);
        bool eliminateEdge(unsigned int vertex, int edge);
        bool loadFile(const string& filename);
        bool saveFile(const string& filename);

        class Vertex {
            private:
                t dato;
                int index;
            
            public:
                Vertex(): dato(t()), index(0) {}
                Vertex(int index_): dato(t()), index(index_) {}
                ~Vertex(){}

                bool operator==(unsigned int edge) const {
                    return index == edge;
                }

                bool operator!=(unsigned int edge) const {
                    return index != edge;
                }

                bool operator==(const Vertex& other) const {
                    return index == other.index;
                }

                bool operator!=(const Vertex& other) const {
                    return index != other.index; 
                }

                int getIndex(){return index;}
        };

    private:
        ListaLigada< Vertex > *table;
        unsigned int size;
};

template <typename t>
bool Graph<t>::createGraph(unsigned int nSize) {
    if(nSize == 0 || table)
        return false;
    table = new(std::nothrow) ListaLigada< Vertex >[nSize];
    if(!table)
        return false;
    size = nSize;
    return true;
}

template <typename t>
void Graph<t>::eliminateGraph() {
    if(table) {
        delete [] table;
        table = nullptr;
        size = 0;
    }
}

template <typename t>
bool Graph<t>::insertEdge(unsigned int vertex, int edge) {
    if (vertex < size) {
        Vertex v(edge);
        if (table[vertex].insertar(v))
            return true;
    } 
    return false;
}

template <typename t>
bool Graph<t>::eliminateEdge(unsigned int vertex, int edge) {
    if (vertex < size) {
        Vertex v(edge);
        if (table[vertex].destruirNodo(v))
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
                insertEdge(counter, stoi(edge));
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
        
        for (typename ListaLigada< Vertex >:: iterator j(table[counter].begin()); j != table[counter].end(); ++j) {
            file << (*j).getIndex() << ' ';
        }
        file << endl;
        counter++;
    }
    file.close();
    return true;

}