#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Nodo;

class Mapa {
private:
    typedef pair<double, double> ciudad;
    vector<pair<double, double>> ciudades;
    vector<int> solucion;

    //Función para obtener el número de ciudades
    int GetNCiudades() const;
    //Función para comprobar si una ciudad se encuentra ya en la solucion
    bool presenteEnSolucion(const vector<int> & v, int x) const;
    //Función para calcular distancia entre 2 ciudades a y b
    int calcularDistancia(int a, int b) const;
    //Función para calcular la distancia de una solucion
    int CostoSolucion(vector<int> & v) const;
    //Función para comprobar la factibilidad de un nodo
    bool EsFactible(Nodo & n, int cota_global, vector<vector<double> > & distanciasminimas) const;
    //Función que almacena las distancias mínimas a cada ciudad
    void DistanciasMinimas(vector<vector<double> > & distanciasminimas) const;

public:
    int NPoda;
    int NNodosExp;
    int NMaxNodos;
     //Función para cargar el contenido del fichero en memoria
     bool cargarDeFichero(const char *fichero);
     //Función para guardar la solución en memoria
     bool guardarSolucion(const char *fichero);
     //Función para mostrar la solucion por pantalla
     void mostrarSolucion();
     //Función para mostrar el coste de la solucion
     void mostrarCoste();
     //Función para calcular la solución por Branch and Bround
     void BranchBround();
     //Función para calcular la solución con un algoritmo greedy
     void GreedyCiudadProxima();
};

#endif /* MAPA_H */
