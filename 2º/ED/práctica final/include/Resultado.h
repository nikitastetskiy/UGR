/******************************************************************************
 *
 * ED - Estructura de Datos
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  T.D.A Resultado simplemente guarda una palabra con su puntuacion
 *
 * Se utiliza así porque luego podremos ordenar conjuntos de resultados usando los
 * functores definidos en esta clase, tanto por longitud de palabra como por
 * puntuación, haciendo mas sencilla la implementación.
 *
 ******************************************************************************/

#ifndef __Resultado_h__
#define __Resultado_h__

#include <string>

using namespace std;

/**
 * @brief TDA Resultado
 * @details simplemente guarda una palabra con su puntuacion
 *
 */
class Resultado
{

private:

    /**
     * La representación del conjunto resultado simplemente almacena
     * una cadena con la palabra y su puntuación asociada, que es la suma
     * de las puntuaciones de la palabra.
     *
     * Se utiliza así porque luego podremos ordenar conjuntos de resultados usando los
     * functores definidos en esta clase, tanto por longitud de palabra como por
     * puntuación, haciendo mas sencilla la implementación.
     */
	string palabra;	// La palabra en si
	int puntuacion; // La puntuacion.

public:

    /**
     * @brief Constructor sin parametros
     */
	Resultado() : palabra(""), puntuacion(0) {}

    /**
     * @brief Constructor que inicializa una palabra con su puntuación
     *
     * @param pal string que contiene una palabra
     * @param p puntuación de la palabra (es la suma de la puntuación de todas sus letras)
     */
	Resultado(string pal, int p) : palabra(pal), puntuacion(p) {}

    /**
     * @brief Sobrecarga del operador de salida
     * @details Pinta la palabra y su puntuación en un flujo de salida
     *
     * @param os ostream de salida
     * @param r Instancia de Resultado
     */
	friend ostream & operator<<(ostream & os, const Resultado &r)
	{
		os << r.palabra << "\t\tPuntuacion:" << r.puntuacion;
		return os;
	}

    /**
     * @brief Functor de comparación por longitud
     *
     * @param L1 Resultado a ordenar 1
     * @param L2 Resultado a ordenar 2
     *
     * @return Devuelve quien tiene la longitud mayor
     */
    struct cmp_pal
    {
        bool operator()(const Resultado &L1 , const Resultado &L2)
        {
            return (L1.palabra.size() > L2.palabra.size()) ? true : false;
        }
    };

    /**
     * @brief Functor de comparación por puntuación
     *
     * @param L1 Resultado a ordenar 1
     * @param L2 Resultado a ordenar 2
     *
     * @return Devuelve quien tiene la puntuación mayor
     */
    struct cmp_pts
    {
        bool operator()(const Resultado &L1 , const Resultado &L2)
        {
            return (L1.puntuacion > L2.puntuacion) ? true : false;
        }
    };


    };



#endif