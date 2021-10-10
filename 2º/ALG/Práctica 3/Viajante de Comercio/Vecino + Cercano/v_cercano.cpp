#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

// Struct Ciudad
// Representa una ciudad mediante:
// 1) Índice
// 2) Coordenadas x e y (posición en el plano)
struct Ciudad{
	int indice;
	double x; //Coordenadas
	double y;
};

// Función leerCiudades
// Lee las ciudades desde un fichero
void leerCiudades(vector<Ciudad> &ciudades, const char fichero[]){

	ifstream f(fichero);
	double valor_leido = 0.0;
	int num_ciudades = 0;

	if(f){
		f.ignore(11);  // Ignoramos "DIMENSION: "
		f >> num_ciudades;  // Dimension
		
		for(int i = 0; i < num_ciudades; i++){ // Cargamos el vector de ciudades con el índice
			f >> valor_leido;
			ciudad.indice = valor_leido;
			f >> valor_leido;
			ciudad.x = valor_leido;
			f >> valor_leido;
			ciudad.y = valor_leido;

			ciudades.push_back(ciudad);
		}
	}

	f.close();
}

// Función calcularDistanciaTotal
// Calcula la distancia total de un conjunto de ciudades
double calcularDistanciaTotal(vector<Ciudad> ciudades){

	double distancia = 0.0, x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;

	for(int i = 1; i < ciudades.size(); i++){
		x1 = ciudades[i-1].x;
		y1 = ciudades[i-1].y;
		x2 = ciudades[i].x;
		y2 = ciudades[i].y;

		distancia += sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
	}

	return distancia;
}

// Función seleccionarCiudad
// Selecciona la siguiente ciudad solución
void seleccionarCiudad(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	Ciudad ciudad_actual;
	vector<Ciudad> v_aux;
	double min_distancia = 99999999999;
	int indice_ciudad = 0, indice_posicion_insertar = 0;
	//vector<Ciudad >::iterator it;
	
	//Vamos cogiendo cada vez la ciudad más cercana dentro del conjunto de ciudades
	for(int i = 0; i < ciudades.size(); i++){
		ciudad_actual = ciudades[i];
		v_aux = ciudades_solucion;
		v_aux.push_back(ciudad_actual);
		double d = calcularDistanciaTotal(v_aux);
		if(d < min_distancia){
			min_distancia = d;
			indice_ciudad = i;
			
		}
		v_aux.clear();
	
		
	}

	ciudades_solucion.push_back(ciudades[indice_ciudad]);
	ciudades.erase(ciudades.begin() + indice_ciudad);
}

//Algoritmo Greedy para calcular una ruta

void calcularRuta(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	ciudades_solucion.push_back(ciudades.at(0));
	ciudades.erase(ciudades.begin());
	while(ciudades.size()){

		//Vamos seleccionando las ciudades, dentro de la función también se va eliminando
		seleccionarCiudad(ciudades,ciudades_solucion);
	}

}

//MAIN

int main(int argc, char* argv[]){

	vector<Ciudad> ciudades, ciudades_solucion;
	leerCiudades(ciudades, argv[1]);
	calcularRuta(ciudades, ciudades_solucion);

	for(int i = 0; i < ciudades_solucion.size(); i++)
		cout << ciudades_solucion[i].indice << " " << ciudades_solucion[i].x << " " << ciudades_solucion[i].y << endl;

	//ciudades_solucion.erase(ciudades_solucion.end() - 1);
	cout << endl << calcularDistanciaTotal(ciudades_solucion) << endl;

	return 0;
}
