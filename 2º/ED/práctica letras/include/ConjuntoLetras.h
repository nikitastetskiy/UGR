/**
 * @file ConjuntoLetras.h
 * @brief Fichero cabecera del TDA ConjuntoLetras
 * 
 * El T.D.A ConjuntoLetras permitirá tener 
 * en memoria un fichero Letras. Este T.D.A 
 * se define como una colección de letras, 
 * en las que no hay letras repetidas.
 **/


#ifndef _CONJUNTOLETRAS_H_
#define _CONJUNTOLETRAS_H_
#include <iostream>			// std::cout
#include <string>			// std::string
#include <set>				// std::set
#include "Letra.h"

using namespace std;

/**
 * @brief T.D.A. ConjuntoLetras
 * 
 * Se utiliza este TDA como un set
 * de Letras y la Ordenacion de este
 * como un conjunto
 * 
 * El T.D.A ConjuntoLetras permitirá tener 
 * en memoria un fichero Letras. Este T.D.A 
 * se define como una colección de letras, 
 * en las que no hay letras repetidas.
 * 
 * 
 * @author Nikita Stetskiy
 * @date 7/1/2019
 * 
 **/

class ConjuntoLetras{

	private:
 		set<Letra, Letra::LetrasStruct> conjunto;		//< Tipo set, formado por Letra y el Comparador

	public:
		// ... METODOS ...

		/**
         * @brief Retorna los puntos de una definicion
		 * @param palabra String, la definicion
		 * @return puntos Int la puntuacion
        **/

    	int resultado(string palabra){
    		int puntos = 0;
			bool verdadero = false;
			Letra l;
    		for (int i=0;i<palabra.size(); i++){
    			verdadero = false;
    			for (set<Letra>::iterator iter = conjunto.begin(); !verdadero && iter!=conjunto.end(); ++iter ){
	    			l = *iter;
    				if (tolower(palabra[i]) == tolower(*l)){
						verdadero = true;
						puntos  +=  iter->getPuntos();
	    			}
    			}
    		}
			return puntos;
    	}

		/**
         * @brief Retorna el size del conjunto
		 * @return int size o tamaño del set
        **/

		int size(){
			return conjunto.size();
		}

		// ... OPERATORS ...

		/**
         * @brief Escribe en el flujo de entrada un ConjuntoLetras
         * @param flujo: flujo de entrada
         * @param otro: el objeto ConjuntoLetras que se lee
         * @return el flujo de entrada
        **/
		friend istream & operator>>(istream & flujo, ConjuntoLetras &otro){
			string linea;
			char car;
			int pal, nom;
			getline(flujo, linea);
			while (flujo){
				flujo >> car >> nom >> pal;
				Letra let(nom, pal, car);
				otro.conjunto.insert(let);
			}
			return flujo;
		}

		/**
         * @brief Escribe en el flujo de Salida un ConjuntoLetras
         * @param flujo: flujo de salida
         * @param otro: el objeto BolsaLetras que se escribe
         * @return el flujo de salida
        **/

		friend ostream & operator<<(ostream & flujo, const ConjuntoLetras &otro){
			for (set<Letra>::iterator iter = otro.conjunto.begin(); iter!=otro.conjunto.end(); ++iter){
				flujo << *iter << endl;
			}
			return flujo;
		}

		/**
         * @brief Sobrecarga del corchete
         * @param i: flujo de la posicion del corchete
         * @return el iterador del corchete
        **/

		const Letra & operator[](int i) const{
			set<Letra>::iterator iter;
			iter = conjunto.begin();
			advance(iter, i);
			return *iter;
    	};
};

#endif
