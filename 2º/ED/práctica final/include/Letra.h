/******************************************************************************
 *
 * ED - Estructura de Datos
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  T.D.A Letra
 *
 ******************************************************************************/

#ifndef __Letra_h__
#define __Letra_h__

#include <iostream>

using namespace std;

/**
 * @brief TDA Letra
 * @details almacena un caracter, la cantidad de veces que aparece en la bolsa y su puntuación
 *
 */
class Letra
{

private:

    /**
     * La representación interna de la clase Letra son tres variables
     * c que es el caracter de la letra (tipo char)
     * n que es el numero de veces que debe aparecer en la bolsa (tipo int)
     * p que es el la puntuación asociada a esa letra (tipo int)
     *
     */
	char c;	// El caracter de la propia letra
	int n; 	// La cantidad de veces que puede aparecer.
	int p; 	// La puntuacion de una letra.

public:

    /**
     * @brief Constructor sin parametros
     */
	Letra() : c('\0'), n(0), p(0) {}

    /**
     * @brief Constructor que inicializa una letra con su puntuación
     *
     * @param c char que contiene un caracter
     * @param n enter con el numero de apariciones de la letra en la bolsa
     * @param p puntuación de la letra
     */
    Letra(char c, int n, int p) : c(c), n(n), p(p) {}

    /**
     * @brief Sobrecarga de operador
     * @return devuelve el caracter de la letra
     */
    char operator *()
    {
    	return c;
    }

    /**
     * @brief Sobrecarga de operador
     * @return devuelve el numero de apariciones
     */
    int operator &()
    {
    	return n;
    }

    /**
     * @brief Devuelve el numero de puntos de la letra
     * @details [long description]
     * @return [description]
     */
    int getPuntos() const
    {
    	return p;
    }

	char getC() const
	{
		return c;
	}


	// Funcion para pintar la letra
	friend ostream & operator<<(ostream & os, const Letra &l)
	{
		os << l.c << " " << l.n << " Pts:" << l.p;
		return os;
	}

    // Definimos un functor para la comparación NOTA: No es neceario, pues hemos
    // implementado el operador <
    struct cmp
    {
        bool operator()(const Letra &L1 , const Letra &L2)
        {
            return (L1.c < L2.c) ? true : false;
        }
    };

};


#endif