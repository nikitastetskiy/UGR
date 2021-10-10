#ifndef __Diccionario_h__
#define __Diccionario_h__

#include <string>
#include <vector>
#include <set>
#include <string>

using namespace std;

/**
 * @brief TDA Diccionario
 * @details Almacena las palabras de un fichero de texto e itera sobre ellas
 *
 */
class Diccionario
{

private:

    /**
     * La representación de los datos del diccionario es un ArbolGeneral de elementos
     * de tipo info (que a su vez son un char y un booleano que indica si es final de palabra)
     *
     * Dicha representación hace que las palabras ocupen menos en memoria, la cual
     * es la única ventaja real a utilizar otros sistemas menos complejos como podrian ser
     * vectores de cadenas
     *
     */
    set<string> datos;

public:

    typedef set<string>::iterator iterator;

    iterator begin();
    iterator end();

    /**
    @brief Construye un diccionario vacio.
    **/
    Diccionario();

    void insertar(string p);

    /**
    @brief Devuelve el numero de palabras en el diccionario
    **/
    int size() const ;

    /**
    @brief Obtiene todas las palabras en el diccionario de un longitud dada
    @param longitud: la longitud de las palabras de salida
    @return un vector con las palabras de longitud especifica en el parametro de entrada
    **/
    vector<string> PalabrasLongitud(int longitud);

    /**
    @brief Indica si una palabra esta en el diccionario o no
    @param palabra: la palabra que se quiere buscar
    @return true si la palabra esta en el diccionario. False en caso contrario
    **/
    bool Esta(string palabra);


    int getApariciones(const char c);

    
    friend istream & operator>>(istream & is,Diccionario &D);
    friend ostream & operator<<(ostream & os, const Diccionario &D);

};

#include "Diccionario.cpp"

#endif