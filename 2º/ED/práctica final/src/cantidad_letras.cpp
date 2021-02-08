/******************************************************************************
 *
 * ED - Estructura de Datos
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Este programa obtiene la cantidad de instancias de cada letra
 *
 ******************************************************************************/

#include <fstream>
#include <iostream>

#include "Diccionario.h"
#include "ConjuntoLetras.h"

using namespace std;

/**
 * @brief Punto de entrada al programa
 */
int main(int argc, char * argv[])
{
    if (argc!=4)
    {
        cout<<".-Dime el nombre del diccionario "<<endl;
        cout<<".-Dime el nombre de fichero de letras "<<endl;
        cout<<".-Dime el nombre de fichero de salida "<<endl;
        return 1;
    }

    ifstream f_dicccionario (argv[1]);
    if (!f_dicccionario)
    {
        cout << "No puedo abrir el fichero " << argv[1]<<endl;
        return 0;
    }

    ifstream f_letras (argv[2]);
    if (!f_letras)
    {
        cout << "No puedo abrir el fichero " << argv[2]<<endl;
        return 0;
    }

    ofstream f_salida (argv[3]);
    if (!f_salida)
    {
        cout << "No puedo crear el fichero " << argv[3]<<endl;
        return 0;
    }

    // Pintamos la cabecera del archivo
    f_salida << "#Letra\tCantidad\tPuntos" << endl;

    // Cargamos el diccionario
    Diccionario diccionario;
    f_dicccionario >> diccionario;

    // Cargamos las letras en memoria.
    ConjuntoLetras conjunto;
    f_letras >> conjunto;

    // Para cada letra en el conjunto...
    for (int i=0; i<conjunto.size(); i++)
    {
        Letra l = conjunto[i];

        // Obtenemos las veces que aparece y el numero de puntos
        int apariciones = diccionario.getApariciones(*l);
        int puntos = l.getPuntos();

        // Pintamos la salida
        f_salida << *l << '\t' << apariciones << '\t' << puntos << endl;
    }

    // Cerramos el archivo
    f_salida.close();

    return 0;

}