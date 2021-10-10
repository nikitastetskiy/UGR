#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Mapa {
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();

    //Funcion para cargar el contenido del fichero en memoria
    bool cargarDeFichero(const char *fichero);
    //Funcion para guardar la solución en memoria
    bool guardarSolucion(const char *fichero);
    //Funcion para mostrar la solucion por pantalla
    void mostrarSolucion();
    //Funcion para mostrar el coste de la solucion
    void mostrarCoste();

    //Funcion para calcular la solución por inserción
    void Insercion();
    //Funcion para calcular la solución por colonia de hormigas
    void ColoniaHormigas(int n_iteraciones, int n_hormigas);

private:
    typedef pair<double, double> ciudad;
    vector<pair<double, double>> ciudades;
    vector<int> solucion;

    //Funcion para comprobar si una ciudad se encuentra ya en la solucion
    bool presenteEnSolucion(int x);
    //Funcion para calcular la mejor posicion de una ciudad en el vector de soluciones y devolver la longitud de camino minima que forma
    int calcularLongitud(int pos, int lugar);
    //Funcion para calcular distancia entre 2 ciudades a y b
    int calcularDistancia(int a, int b);
    //Funcion para calcular la distancia de la solucion
    int CostoSolucion();
};

#endif /* MAPA_H */
