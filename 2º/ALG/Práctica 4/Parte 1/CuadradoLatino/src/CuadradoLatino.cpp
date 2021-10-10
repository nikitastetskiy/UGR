#include <iostream>
#include <stdlib.h>
#include <vector>
#include "CuadradoLatino.h"

using namespace std;

//Inicializar la matriz con el tamaño
void CuadradoLatino::Inicializar(int tam) {
   sol.resize(tam);
   Filas.resize(tam);
   Columnas.resize(tam);
   for (int i = 0; i < tam; i++) {
      sol[i].resize(tam, -1);
      Filas[i].resize(tam, false);
      Columnas[i].resize(tam, false);
   }
}

//Constructor
CuadradoLatino::CuadradoLatino(int tam) {
   Inicializar(tam);
}

//Constructor de copia
CuadradoLatino::CuadradoLatino(const CuadradoLatino & t) {
   int tam = t.getTam();
   Inicializar(tam);
   for (int i = 0; i < tam; i++) {
      for (int j = 0; j < tam; j++) {
         sol[i][j] = t.sol[i][j];
         Filas[i][j] = t.Filas[i][j];
         Columnas[i][j] = t.Columnas[i][j];
      }
   }
}

//Consulta de tamaño
int CuadradoLatino::getTam() const {
   return sol.size();
}

//Coloca un valor en una posición del cuadrado
bool CuadradoLatino::setPos(int fil, int col, int n){
    bool valido = true;
    int tam = getTam();

    if (fil < 0 || fil >= tam || col < 0 || col >= tam || n < 0 || n >= tam || sol[fil][col] != -1)
        valido = false;
    else {
      sol[fil][col] = n;
      if (!FactibleConstante(sol, fil, col)) {
         valido = false;
         sol[fil][col] = -1;
      }
   }

    return valido;
}

//Comprueba si el elemento colocado en una posición es factible
bool CuadradoLatino::Factible(vector<vector<int> > & cuadrado, int i, int j, bool constante) {
   if (constante)
      return FactibleConstante(cuadrado, i, j);
   else
      return FactibleLineal(cuadrado, i, j);
}

//Comprueba si el elemento colocado en una posición es factible con orden constante.
bool CuadradoLatino::FactibleConstante(vector<vector<int> > & cuadrado, int i, int j) {
   int valor = cuadrado[i][j];
   bool factible = true;
   if (Filas[i][valor] || Columnas[j][valor])
      factible = false;
   else {
      Filas[i][valor] = true;
      Columnas[j][valor] = true;
   }
   return factible;
}

//Comprueba si el elemento colocado en una posición es factible con orden lineal.
bool CuadradoLatino::FactibleLineal(vector<vector<int> > & cuadrado, int i, int j) {
   int valor = cuadrado[i][j];
   bool factible = true;
   for (int k = 0; k < j && factible; k++)
      factible = valor != cuadrado[i][k];

   for (int k = 0; k < i && factible; k++)
      factible = valor != cuadrado[k][j];

   return factible;
}

//Borra un elemento de la matriz
void CuadradoLatino::LimpiarPosiciones(vector<vector<int> > & cuadrado, int k, int l) {
   int val = cuadrado[k][l];
   cuadrado[k][l] = -1;
   Filas[k][val] = false;
   Columnas[l][val] = false;

}

//Busca el cuadrado latino que concuerde con la matriz actual
bool CuadradoLatino::BuscarSolucion(bool sol_unica, bool orden) {
   vector<vector<int> > cuadrado = sol;
   return BuscarSolucion(cuadrado, sol_unica, 0, 0, orden);
}

//Función backtracking recursiva
bool CuadradoLatino::BuscarSolucion(vector<vector<int> > & cuadrado, bool sol_unica, int k, int l, bool orden) {
   bool resuelto = false;
   int tam = getTam();

   if (k == tam) {
      sol = cuadrado;
      resuelto = true;
      imprimirSol();
   }
   else {
      int nuevol = (l + 1)%tam;
      int nuevok = k;
      if (nuevol == 0)
         nuevok++;

      if (cuadrado[k][l] != -1) {
         resuelto = BuscarSolucion(cuadrado, sol_unica, nuevok, nuevol);
      }
      else {
         bool terminar = resuelto && sol_unica;
         for (int i = 0; i < getTam() && !terminar; i++) {
            cuadrado[k][l] = i;
            if (Factible(cuadrado, k, l, orden)) {
               resuelto = BuscarSolucion(cuadrado, sol_unica, nuevok, nuevol, orden);
               LimpiarPosiciones(cuadrado, k, l);
               terminar = resuelto && sol_unica;
            }
            else
               cuadrado[k][l] = -1;
         }

      }

   }

   return resuelto;
}

//Imprime la solución actual
void CuadradoLatino::imprimirSol(){
    cout << "SOLUCION: " << endl;
    mostrarTablero(sol);
}

//Imprime un tablero
void CuadradoLatino::mostrarTablero(vector< vector <int>> tablero){
    for (int i=0; i<tablero.size(); i++){
        for(int j=0; j<tablero.size(); j++)
            cout << tablero[i][j] << "  ";
        cout << "\n";
    }
    cout << "\n";
}
