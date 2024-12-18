#include "catalogo.h"

using namespace std;

void Catalogo::imprimir() {
    tablaColores.imprimirTabla();
}

bool Catalogo::loadFromCSV(const string& filename) {
    ifstream    file(filename);
    string      line;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return false;
    }

    if(!tablaColores.createTable(TABLE_SIZE, hashFunc)) {
        file.close();
        cerr << "No se pudo crear la hash table." <<  endl;
        return false;
    }

    cout << "Cargando archivo..." << endl;

    while (getline(file, line)) {
        Color           color;
        stringstream    ss(line);
        string          cell;
        int             campo = 0, errores = 0;

        while (getline(ss, cell, ',')) {
            if(!cell.length())
                errores ++;
            
            switch(campo) {
                case 0:
                    color.setID(cell);
                    break;
                case 1:
                    color.setName(cell);
                    break;
                case 2:
                    color.setHex(cell);
                    break;
                case 3:
                    if(isValidNumeric(cell))
                        color.setR(stoi(cell));
                    else 
                        errores ++;
                    break;
                case 4:
                    if(isValidNumeric(cell))
                        color.setG(stoi(cell));
                    else 
                        errores ++;
                    break;
                case 5:
                    if(isValidNumeric(cell))
                        color.setB(stoi(cell));
                    else 
                        errores ++;
                    break;
                default:
                    errores ++;
                    break;
            }
            campo ++;
        }

        if(errores || campo != 6) {
            cerr << "Error en la linea: " << endl << line << endl;
            file.close();
            return false;
        }
        
        if(!tablaColores.insertar(color)) {
            cerr << "No se pudo agregar el color a la tabla hash." << endl;
            file.close();
            return false;
        }
        size ++;
    }

    file.close();
    
    return true;
}

Color *Catalogo::buscar(unsigned int r, unsigned int g, unsigned int b) {
    Color busca(r, g, b);

    return(tablaColores.buscar(busca));
}

bool Catalogo::isValidNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
