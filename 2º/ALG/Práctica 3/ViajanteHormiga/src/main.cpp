#include <cstdlib>
#include "Mapa.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(NULL));
    Mapa mapa;
    const int NITERACIONES = 1000;
    const int NHORMIGAS = 1000;

    if (argc < 2){
        cout << "Se necesita el nombre del fichero de ciudades como argumento\n";
        return 1;
    }

    if(mapa.cargarDeFichero(argv[1]))
      mapa.ColoniaHormigas(NITERACIONES, NHORMIGAS);

    mapa.mostrarSolucion();
    mapa.mostrarCoste();

    if (argc > 2) {
      mapa.guardarSolucion(argv[2]);
    }

    return 0;
}
