/**
  * @file Termino.h
  * @brief Fichero cabecera del TDA Termino
  *
  * Gestiona una secuencia de elementos pair con facilidades para la inserccion y
  * borrado de elementos en un extremo
  */

#ifndef _TERMINO_H_
#define _TERMINO_H_

#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout
#include <vector>

using namespace std;

/**
 *  @brief T.D.A. Termino
 * 
 * 
 *	Esta clase junta un par de valores, 
 *	que pueden ser de diferentes tipos (T1 y T2). 
 *	Se puede acceder a los valores individuales a 
 *	través de sus miembros públicos primero y segundo.
 * 
 * Estos valores se componen con un string y un vector 
 * de string. Está formado por una palabra y un conjunto 
 * de definiciones asociadas a esa palabra.
 * 
 * @author Nikita Stetskiy
 * @date 9 / 12 / 2018
 * 
*/

class Termino{

	private:
		pair <string,vector<string> > termino;	///< Tipo de miembro primero, con alias como first_type. Tipo de miembro segundo, con alias como second_type.

	public:
		typedef vector<string>::iterator iterator; ///< iterator se empleará para acceder y recorrer elementos del contenedor permitiendo su modificación
		typedef vector<string>::const_iterator const_iterator; ///< const_iterator no permitirá la modificación de los elementos del contenedor

		iterator begin();	///< devuelve el iterator por el metodo begin
		const_iterator begin() const;	///< devuelve el const_iterator por el metodo begin
		iterator end();		///< devuelve el iterator por el metodo end
		const_iterator end() const;		///< devuelve el const_iterator por el metodo end

		// ---------------  Constructores ----------------
    	/**
     	* @brief Constructor por defecto
     	*/
		Termino();
		/**
     	* @brief Constructor por parametro
    	* @param s1 que se guardara en first
		* @param v1 de strings que se guardara en el second
     	*/
		Termino(const string & s1, const vector<string> &v1);
		/**
     	* @brief Constructor por copia
     	* @param ter pair original que se le hara copia
    	*/
		Termino(const pair <string,vector<string> > & ter);

		// --------------- Otras funciones ---------------
    	/**
     	* @brief Obtener la palabra 
     	*/
		string GetPalabra()const;
		/**
     	* @brief Obtener las definiciones asociadas a la palabra
     	*/
		vector<string> GetDefiniciones()const;
		/**
     	* @brief Obtener el número de definiciones asociadas a la palabra
     	*/
		int GetNumero()const;
		/**
     	* @brief Establecer la palabra
		* @param palabra Elemento que se va a añadir.
     	*/
		void SetPalabra(string palabra);
		/**
     	* @brief Añadir nuevas definiciones asociadas a la palabra
		* @param v Definiciones que se va a añadir.
     	*/
		void SetDefiniciones(const vector<string> &v);
		/**
     	* @brief Encontrar la palabra que se busca en las definiciones
		* @param palabra la palabra clave que se busca, en este caso "color"
     	*/
		vector<string> EncontrarPalabra(string palabra);
		/**
     	* @brief Sobrecarga del operador <<
		* @param os flujo del cout
     	* @param t Termino que se va a hacer el flujo cout.
     	*/
		friend ostream& operator<< (ostream & os, const Termino & t);
		/**
     	* @brief Sobrecarga del operador >>
		* @param flujo flujo del cin
     	* @param otro Termino que se va a hacer el flujo cin.
     	*/
		friend istream& operator>> (istream &flujo, Termino &otro);
		/**
     	* @brief Sobrecarga del operador <
		* @param otro Termino que se ve a realizar la comparación
     	*/
		bool operator< (const Termino &otro) const;
		
};

#endif
