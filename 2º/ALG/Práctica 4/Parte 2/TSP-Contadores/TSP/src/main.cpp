#include <cstdlib>
#include <ctime>
#include "Mapa.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(NULL));
    Mapa mapa;

    if (argc < 2){
        cout << "Se necesita el nombre del fichero de ciudades como argumento\n";
        return 1;
    }

    if(mapa.cargarDeFichero(argv[1])) {
      unsigned t0, t1;

      t0=clock();
      mapa.BranchBround();
      t1 = clock();

      mapa.mostrarSolucion();
      mapa.mostrarCoste();

      double time = (double(t1-t0)/CLOCKS_PER_SEC);
      cout << "Tiempo utilizado en calcular la ruta: " << time << " seg"<< endl;
      cout << "Numero maximo de nodos almacenados: " << mapa.NMaxNodos << endl;
      cout << "Numero de nodos explorados: " << mapa.NNodosExp << endl;
      cout << "Numero de podas realizadas: " << mapa.NPoda << endl;

      if (argc > 2) {
        mapa.guardarSolucion(argv[2]);
      }
    }

    return 0;
}
