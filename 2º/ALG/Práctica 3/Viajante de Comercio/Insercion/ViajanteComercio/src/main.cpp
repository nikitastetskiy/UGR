#include <cstdlib>
#include "Mapa.h"

using namespace std;

int main(int argc, char** argv) {
    Mapa mapa;
    
    if (argc < 2){
        cout << "Se necesita el nombre del fichero de ciudades como argumento\n";
        return 1;
    }
    
    if(mapa.cargarDeFichero(argv[1]))
        mapa.calcularSolucion();
    
    mapa.mostrarSolucion();
        
    return 0;
}

