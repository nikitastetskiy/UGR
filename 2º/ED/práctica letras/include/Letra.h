/**
 * @file Letra.h
 * @brief Fichero cabecera del TDA Letra
 * 
 * El T.D.A Letra esta formado por una letra, 
 * su caracter, numero de apariciones y
 * su puntuacion
 **/

#ifndef _LETRA_H_
#define _LETRA_H_
#include <iostream>     // std::cout

using namespace std;

/**
 * @brief T.D.A. Letra
 * 
 * El T.D.A Letra almacena una letra. 
 * Una letra se especifica con tres valores:
 * El carácter de la propia letra
 * La cantidad de veces que puede aparecer.
 * La puntuación de una letra
 * 
 * Este TDA esta formado por una letra, 
 * su caracter, numero de apariciones y
 * su puntuacion
 * 
 * @author Nikita Stetskiy
 * @date 7/1/2019
 * 
 **/

class Letra{

private:

    int num, puntos;        //< Tipo int, numeros y puntuacion
	char caracter;          //< Tipo char, caracter de la letra
	

public:
    // ... CONSTRUCTORES ...

    /**
     * @brief Constructor, crea una Letra vacia
    **/

	Letra() :caracter('\0'), num(0), puntos(0)
    {}

    /**
     * @brief Constructor por parametros, crea una Letra vacia
     * @param n Int de la cantidad que puede aparecer
     * @param p Int de la cantidad de puntos
     * @param c Char del caracter de una letra
    **/

    Letra(int n, int p, char c) :num(n), puntos(p), caracter(c)
    {}

    // ... GETTERS ...

    /**
     * @brief Retorna la puntuacion
     * @return los puntos
    **/

    int getPuntos()const{
    	return puntos;
    }

    /**
     * @brief Retorna la cantidad de apariciones
     * @return los numeros
    **/

    int getNum()const{
    	return num;
    }

    /**
     * @brief Set de contador --
    **/

    void setPuntos(){
        puntos--;
    }

    // ... OPERATORS ...

    /**
     * @brief Comparador de caracteres
     * @param Letra1 primera Letra
     * @param Letra2 segunda Letra
     * @return bool de puntos entre las dos Letras
    **/

    struct LetrasStruct{
        bool operator()(const Letra &Letra1 , const Letra &Letra2){
            return (Letra1.caracter < Letra2.caracter);
        }
    };

    /**
     * @brief Sobrecarga de *()
     * @return retorna el caracter
    **/

    char operator *(){
    	return caracter;
    }

    /**
     * @brief Sobrecarga de &()
     * @return retorna el numero
    **/

    int operator &(){
    	return num;
    }

    /**
     * @brief Escribe en el flujo de salida una Letra
     * @param flujo: flujo de salida
     * @param otro: el objeto Letra que se escribe
     * @return el flujo de salida
     **/

	friend ostream & operator<<(ostream &flujo, const Letra &otro){
		flujo<<otro.caracter<< " " <<otro.num<< " Puntos: "<< otro.puntos;
		return flujo;
	}

};
#endif