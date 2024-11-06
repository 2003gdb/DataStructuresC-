// Crea diferentes objetos que tienen monstruos para simular el juego de Dungeons & Dragons
// Carlos A Galvez Diaz Barriga - A01067590
// 24/10/24

#define NUM_CUARTOS 20
#include "dungeon.h"
#include "catalogo.h"
#include "jugador.h"

int main() {
    Catalogo<Monstruo> miCatalogo;
    Dungeon<Monstruo> miDungeon;

    if(!miCatalogo.loadFromCSV("monsters.csv")) {
        cout << "No se pudo crear el catálogo" << endl;
        return 0;
    }
    
    cout << "Creando Dungeon..." << endl;
    for(int c = 0; c < NUM_CUARTOS; c++) {
        Monstruo Monster = miCatalogo.getRandomMonster();

        if(!miDungeon.createRoom(Monster)) {
            cout << "No se pudo insertar cuarto con monstruo al calabozo" << endl;
            return 0;
        }
    }

    if(!miDungeon.imprimeCuartos()){
        cout << "No se pudo imprimir la dungeon" << endl;
        return 0;
    }
    return 0;
}
