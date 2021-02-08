/**
 * @file Puntuacion.h
 * @brief Fichero cabecera del TDA Puntuacion
 * 
 * Este TDA esta formado por un conjunto de
 * palabras que son las definciones con sus
 * respectivas puntuaciones
 **/

#ifndef _PUNTUACION_H_
#define _PUNTUACION_H_
#include<iostream>          // std::cout
#include<string>            // std::string

using namespace std;

/**
 * @brief T.D.A. Puntuacion
 * 
 * Se utiliza este TDA para poder ordenar las 
 * palabras adecuadamente para que posteriormente
 * sea mas facil su implementacion
 * 
 * Este TDA esta formado por un conjunto de
 * palabras que son las definciones con sus
 * respectivas puntuaciones
 * 
 * 
 * @author Nikita Stetskiy
 * @date 7/1/2019
 * 
 **/

class Puntuacion{

    private:

	    string definicion;      //< Tipo string, la palabra
	    int puntos;             //< Tipo int, la puntuacion de la definicion

    public:

        /**
         * @brief Constructor, crea una Puntuacion vacia
        **/
	    Puntuacion() :definicion(""), puntos(0)
        {}

        /**
         * @brief Constructor por parametros, crea una Puntuacion vacia
         * @param p String de la definicion
         * @param n Int puntuacion de la definicion
        **/

	    Puntuacion(string p, int n) : definicion(p), puntos(n)
        {}

        /**
         * @brief Retorna la puntuacion
         * @return los puntos
        **/

        int getResul()const{
            return puntos;
        }

        /**
         * @brief Comparador de size
         * @param Resul1 Resultado1
         * @param Resul2 Resultado2
         * @return bool de size entre los dos Resultados
        **/

        struct StructPalabra{
            bool operator()(const Puntuacion &Resul1 , const Puntuacion &Resul2){
                return (Resul1.definicion.size() > Resul2.definicion.size());
            }
        };

        /**
         * @brief Retorna la defincion
         * @return definicion
        **/

        string getPalabra()const{
            return definicion;
        }

        /**
         * @brief Comparador de puntos
         * @param Resul1 Resultado1
         * @param Resul2 Resultado2
         * @return bool de puntos entre los dos Resultados
        **/

        struct StructPuntos{
            bool operator()(const Puntuacion &Resul1 , const Puntuacion &Resul2){
                return (Resul1.puntos > Resul2.puntos);
            }
        };

        /**
         * @brief Escribe en el flujo de salida una Puntuacion
         * @param flujo: flujo de salida
         * @param otro: el objeto Puntuacion que se escribe
         * @return el flujo de salida
        **/

        friend ostream & operator<<(ostream & flujo, const Puntuacion &otro){
		    flujo << otro.definicion <<"\t\tPuntos:"<< otro.puntos;
		    return flujo;
	    }
};



#endif