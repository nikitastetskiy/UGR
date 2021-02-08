/**
 * @file Diccionario.h
 * @brief Fichero cabecera del TDA Diccionario
 * 
 * Un objeto del T.D.A. Diccionario almacena 
 * palabras de un lenguaje. El T.D.A 
 * Diccionario será representado como un set
 * instanciado a string 
 * 
 **/

#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

#include <string>		// std::cout
#include <vector>		// std::vector
#include <set>			// std::set
#include <string>		// std::string

using namespace std;

/**
 * @brief T.D.A. Diccionario
 * 
 * El T.D.A Diccionario almacena un set. 
 * Un Diccionario incorpara tambien iteradores
 * para poder recorrer de manera ordenada
 * todas las palabras del diccionario
 * 
 * Un objeto del T.D.A. Diccionario almacena 
 * palabras de un lenguaje. El T.D.A 
 * Diccionario será representado como un set
 * instanciado a string 
 * 
 * @author Nikita Stetskiy
 * @date 7/1/2019
 * 
 **/

class Diccionario{

private:

	set<string> datos;							//< Tipo set<string>, datos

public:

	typedef set<string>::iterator iterator;		//< Tipo iterator de set<string>

	iterator begin();							//< Tipo iterator para begin()

	iterator end();								//< Tipo iterator para end()

	/**
	 * @brief Construye un diccionario vacío.
    **/ 

	Diccionario();

	/** 
	 * @brief Insertar una palabra al diccionario
	 * @param p: String de la palabra que se quiere insertar
    **/

	void insertar(string p);

	/** 
	 * @brief Devuelve el numero de palabras en el diccionario
	 * @return int size
    **/ 

	int size() const ;

	/** 
	 * @brief Obtiene todas las palabras en el diccionario de un longitud dada
	 * @param longitud: la longitud de las palabras de salida
	 * @return un vector con las palabras de  longitud especifica en el parametro de entrada
    **/ 

	vector<string> PalabrasLongitud(int longitud);

	/** 
	 * @brief Indica si una palabra está en el diccionario o no
	 * @param palabra: la palabra que se quiere buscar
	 * @return true si la palabra esta en el diccionario. False en caso contrario
    **/ 

	bool Esta(string palabra);



	int getNumero(const char c);

	/** 
	 * @brief Lee de un flujo de entrada un diccionario
	 * @param is:flujo de entrada
	 * @param D: el objeto donde se realiza la lectura.
	 * @return el flujo de entrada
    **/    

	friend istream & operator>>(istream & is,Diccionario &D);

	/** 
	 * @brief Escribe en un flujo de salida un diccionario
	 * @param os:flujo de salida
	 * @param D: el objeto diccionario que se escribe
	 * @return el flujo de salida
    **/            

	friend ostream & operator<<(ostream & os, const Diccionario &D);
};

#include "Diccionario.cpp"

#endif
