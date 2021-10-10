#ifndef CUADRADOLATINO_H
#define CUADRADOLATINO_H

#include <vector>

using namespace std;

class CuadradoLatino {
private:
   vector<vector<int> > sol;

   vector<vector<bool> > Filas;
   vector<vector<bool> > Columnas;

   void Inicializar(int tam);

public:
   CuadradoLatino(int tam);

   CuadradoLatino(const CuadradoLatino & t);

   int getTam() const;

   bool setPos(int fil, int col, int n);

   bool Factible(vector<vector<int> > & cuadrado, int i, int j, bool constante = true);

   bool FactibleConstante(vector<vector<int> > & cuadrado, int i, int j);

   bool FactibleLineal(vector<vector<int> > & cuadrado, int i, int j);

   void LimpiarPosiciones(vector<vector<int> > & cuadrado, int k, int l);

   bool BuscarSolucion(bool sol_unica, bool orden = true);

   bool BuscarSolucion(vector<vector<int> > & cuadrado, bool sol_unica, int k, int l, bool orden = true);

   void imprimirSol();

   void mostrarTablero(vector< vector <int>> tablero);
};

#endif
