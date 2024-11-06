// Crea un monstruo para insertar en diferentes estructuras de datos y que funciones correctamente.
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#include <iostream>
#include <string>
using namespace std;

class Monstruo {
    private:
        string name;
        double cr;
        string type;
        string size;
        int ac;
        int hp;
        string align;

    public:
        // Constructor que inicializa los miembros 'name', 'cr', 'type', 'size', 'ac', 'hp' y 'align'.
        Monstruo() : name("Juan"), cr(0.0), type(""), size(""), ac(0), hp(0), align("") {}

        // Destructor de la clase Monstruo.
        ~Monstruo(){}

        // Getters: Regresan el valor de los atributos cuando son llamadas.
        string getName(){ return name; }
        double getCr(){ return cr; }
        string getType(){ return type; }
        string getSize(){ return size; }
        int getAc(){ return ac; }
        int getHp(){ return hp; }
        string getAlign(){ return align; }

        // Setters: Introducen el valor de los atributos al objeto Mosntruo cuando son llamadas.
        void setName(string newName) { name = newName; }
        void setCr(double newCr) { cr = newCr; }
        void setType(string newType) { type = newType; }
        void setSize(string newSize) { size = newSize; }
        void setAc(int newAc) { ac = newAc; }
        void setHp(int newHp) { hp = newHp; }
        void setAlign(string newAlign) { align = newAlign; }

        // Sobrecarga del operador '<' para comparar monstruos por nombre.
        // Parámetros:
        //   os - el stream de salida.
        //   monstruo - Monstruo que será comparado
        // Retorno:
        //   true si se compara correctamente por nombre, false de lo contrario
        bool operator<(const Monstruo& monstruo) const {
            return this->name < monstruo.name;  
        }

        // Sobrecarga del operador '>' para comparar monstruos por nombre.
        // Parámetros:
        //   os - el stream de salida.
        //   monstruo - Monstruo que será comparado
        // Retorno:
        //   true si se compara correctamente por nombre, false de lo contrario
        bool operator>(const Monstruo& monstruo) const {
            return this->name > monstruo.name;  
        }

        // Sobrecarga del operador << para imprimir el nombre de Monstruo.
        // Parámetros:
        //   os - el stream de salida.
        //   monstruo - la instancia de monstruo que será impresa.
        // Retorno:
        //   El stream de salida con el nombre del monstruo.
        friend ostream& operator<<(ostream& os, const Monstruo& monstruo){
            os << monstruo.name;
            return os; 
        }

};

