/**
 * @file BolsaLetras.h
 * @brief Fichero cabecera del TDA BolsaLetras
 * 
 * Este TDA esta formado por un conjunto de
 * letras que se van repetiendo tantas veces
 * cuanto se indique en letras.txt
 **/

#ifndef _BOLSALETRAS_H
#define _BOLSALETRAS_H

#include <set>			// std::set
#include <iostream>		// std::cout
#include "Letra.h"
#include "ConjuntoLetras.h"

using namespace std;

/**
 * @brief T.D.A. BolsaLetras
 * 
 * Se utiliza este TDA para poder ordenar las 
 * palabras adecuadamente teniendo en cuenta
 * su numero de repeticiones a partir de 
 * ConjuntoLetras
 * 
 * Este TDA esta formado por un conjunto de
 * letras que se van repetiendo tantas veces
 * cuanto se indique en letras.txt
 * 
 * 
 * @author Nikita Stetskiy
 * @date 7/1/2019
 * 
 **/


class BolsaLetras{

	private:
 		multiset<Letra, Letra::LetrasStruct> bolsa;		//< Tipo multiset, formado por Letra y el Comparador

	public:

		/**
         * @brief Retorna el size de la bolsa de letras
		 * @return int size o tamaño de la bolsa
        **/

		int size(){
			return bolsa.size();
		}

		/**
         * @brief Escribe en el flujo de entrada un ConjuntoLetras
         * @param flujo: flujo de entrada
         * @param otro: el objeto BolsaLetras que se lee
         * @return el flujo de entrada
        **/

		friend ConjuntoLetras & operator>>(ConjuntoLetras &flujo, BolsaLetras &otro){
			Letra l;
			for (int i=0; i<flujo.size(); i++){
				l = flujo[i];
				for (int j=0; j<&l; j++){
					otro.bolsa.insert(l);
				}
			}
		return flujo;
		}

		/**
         * @brief Sobrecarga del corchete
         * @param i: flujo de la posicion del corchete
         * @return el iterador del corchete
        **/

		const Letra & operator[](int i) const{
			multiset<Letra>::iterator iter;
			iter = bolsa.begin();
			advance(iter, i);
			return *iter;
    	};
};

#endif