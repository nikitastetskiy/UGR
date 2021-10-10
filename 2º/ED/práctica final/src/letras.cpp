/*#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
#include<ctime>
#include<cstdlib>

using namespace std;

int main(int argc, char * argvπ[]){
	if(argc != 5){
		cout<<"Error en el numero de parametros"<<endl;
		return 1;
	}
	
	// ...INICIALIZAMOS...
	ifstream diccionario (argv[1]);
	ifstream letras (argv[2]);
	int num = atoi(argv[3])
	char modalidad;
	BolsaLetras bolsa_o;
	ConjuntoLetras conjunto_o;
	Diccionario diccionario_o;
	diccionario>> diccionario_o;
	letras>> conjunto_o;
	conjunto_o>> bolsa_o;

	while (tolower(modalidad)!='n'){
		vector<Letra> vector;
		Letra aux;
		int aleatorio;
		string auxiliar;
		srand(time(0));

		for(int i=0;i<num;i++){
			aleatorio = rand() % bolsa_o.size();	// num aleatorio
			aux = bolsa_o[aleatorio];
			vector.push_back(aux);
			cout <<*aux<< '\t';
		}
		
		Letra x;
		for (int i=0; i<vector.size(); i++){
			x = vector[i];
			auxiliar.push_back(tolower(*l));
		}

		string palabra_introducida;
		cin>>palabra_introducida;
		cout << "Dime tu solucion: ";
		bool no_verdad = true;
		while(palabra_introducida.size()<num or no_verdad){
			no_verdad = false;
			for(int i=0; !no_verdad && i<palabra_introducida.size(); i++){
				char letra = palabra_introducida[i];
				if(auxiliar.find(letra) == string::npos){
					no_verdad = true;
				}
			}
			if(no_verdad){
				cout << "Dime tu solucion: ";
				cin>>palabra_introducida;
			}
		}

		if(diccionario_o.Esta(palabra_introducida)){
			cout<< palabra_introducida << "\tPuntuacion: " << conjunto.puntuacion(palabra_introducida)<<endl;
		}
		else{
			cout<<"Palabra inventada"<<endl;
		}

		vector<Resultado> lista;

		cout <"Mis soluciones son: "<<endl;
		for(int i=0; i<num; i++){
			vector<string> longo = diccionario.PalabrasLongitud(i);
			for(vector<string>::iterator iter = longo.begin(); iter!=longo.end(); ++it){
				string palabra = *iter;
				vector<bool> p_usado(vector.size(), false);
				int c_usadas = 0;
				for(int l1=0; l1<palabra.size(); l1++){
					bool flag = false;
					char l1 = palabra[l1];
					for (int l2=0; !flag && l2<auxiliar.size(); l2++){
						if (!p_usado[l2] && auxiliar[l2] == l1){
							p_usado[l2] = true;
							flag = true;
							c_usadas++;
						}
					}
				}
				if(c_usadas == palabra.size()){
					lista.push_back(Resultado(palabra,conjunto.puntuacion(palabra) ));
				}
			}
		}

		if (lista.empty())
			cout << RED <<"No se han encontrado palabras"<< endl;
		else
		{
			if (strcmp(argv[4], "P")== 0){
				sort(lista.begin(), lista.end(), Resultado::cmp_pts());
			}
			else if (strcmp(argv[4], "L")== 0){
				sort(lista.begin(), lista.end(), Resultado::cmp_pal());
			}
			else{
				cout<<"L o P mal introducido"<< endl;
				return 0;
			}
			for (vector<Resultado>::iterator iter = lista.begin(); iter!=lista.end(); ++iter)
				cout << *iter << endl;
		}

		cout << "¿Quieres seguir jugando[S/N]?"<<endl;
		cin >> modalidad;
	}
	return 0;
}*/

/******************************************************************************
 *
 * ED - Estructura de Datos
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Este programa construye palabras de longitud mayor (o puntuacion mayor ) a
 *  partir de una serie de letras seleccionadas de forma aleatoria.
 *
 ******************************************************************************/

#include <fstream>
#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <ctime>    // Recursos para medir tiempos

#include <cstring>

#include <vector>
#include <string>


#include <algorithm> // Utilizado para el sort

#include "Diccionario.h"
#include "ConjuntoLetras.h"
#include "BolsaLetras.h"
#include "Color.h" // definiciones de colores ansi
#include "Resultado.h"


using namespace std;


/**
 * @brief Punto de entrada al programa
 */
int main(int argc, char * argv[])
{
	if (argc!=5)
	{
		cout<<".-Dime el nombre del diccionario "<<endl;
		cout<<".-Dime el nombre de fichero de letras "<<endl;
		cout<<".-Numero de letras a generar "<<endl;
		cout<<".-Modo de juego (L: palabras mas larga, P: mayor puntuacion)"<<endl;
		return 1;
	}

	ifstream f_dicccionario (argv[1]);
	if (!f_dicccionario)
	{
		cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
		return 0;
	}

	ifstream f_letras (argv[2]);
	if (!f_letras)
	{
		cout<<"No puedo abrir el fichero "<<argv[2]<<endl;
		return 0;
	}


	// Cargamos las palabras en el diccionario
	Diccionario diccionario;
	f_dicccionario >> diccionario;

	// Cargamos las letras en memoria
	ConjuntoLetras conjunto;
	f_letras >> conjunto;

	// Llenamos la bolsa de letras en base a las veces que se tiene que repetir cada letra
	BolsaLetras bolsa;
	conjunto >> bolsa;

	// Obtenemos el numero de letras con las que jugaremos:
	int numero_letras = atoi(argv[3]);

	char type;
	do
	{
		cout << "Las letras son:\t" << MAGENTA << BOLD;
		srand(time(0));            // Inicialización del generador de números pseudoaleatorios
		vector<Letra> letras;

		for (int i=0; i<numero_letras; i++)
		{
			int rnd = rand() % bolsa.size();      // Generar aleatorio [0,size]

			Letra l = bolsa[rnd];

			cout << *l << '\t';

			letras.push_back(l);
		}
		cout << BLACK << endl;

		string palabra;
		for (int i=0; i<letras.size(); i++)
		{
			Letra l = letras[i];
			palabra.push_back(tolower(*l));
		}

		bool ilegal = false; // Variable para cuando el usuario haga trampas
		string solucion_usuario;
		do
		{
			ilegal = false;

			cout << "Dime tu solucion:";
			cin >> solucion_usuario;
			if (solucion_usuario.size() > numero_letras)
			{
				cout << RED <<"TRAMPOSO!! La palabra introducida es mayor a la cantidad de letras proporcionadas" << BLACK << endl;
				ilegal = true;
			}
			else
			{
				for (int i=0; !ilegal && i<solucion_usuario.size(); i++)
				{
					char letra = solucion_usuario[i];
					// Comprobamos si la letra no está
					if (palabra.find(letra) == string::npos)
					{
						cout << RED <<"TRAMPOSO!! Has usado letras fuera de la secuencia" << BLACK << endl;
						ilegal = true;
					}
				}
			}

		} while (ilegal);

		// Comprobamos si la palabra introducida existe
		if (!diccionario.Esta(solucion_usuario))
			cout << RED <<"Esa palabra no existe" << BLACK << endl;
		else
			cout << BLUE << solucion_usuario << "\tPuntuacion: " << conjunto.puntuacion(solucion_usuario) << BLACK << endl;


		// BUSCAMOS LAS LETRAS
		vector<Resultado> encontradas;

		cout << "Mis soluciones son:" << endl;

		for (int i=numero_letras; i>0; i--)
		{
			// Obtenemos la lista de palabras de la longitud actual
			vector<string> v = diccionario.PalabrasLongitud(i);

			for (vector<string>::iterator it = v.begin(); it!=v.end(); ++it)
			{
				string palabra_vector = *it;

				// Creamos un vector de letras usadas inicializado a false (c++11)
				vector<bool> letras_usadas(letras.size(), false);

				int cont_usadas = 0;
				for (int l_actual =0; l_actual<palabra_vector.size(); l_actual++)
				{
					bool salir = false;
					char letra_actual = palabra_vector[l_actual];

					for (int l_orig=0; !salir && l_orig<palabra.size(); l_orig++)
					{
						if (!letras_usadas[l_orig] && palabra[l_orig] == letra_actual)
						{
							// La letra no está usada, asi que...
							letras_usadas[l_orig] = true; // ...la marcamos como usada y
							cont_usadas++; // ...incrementamos el contador de utilizadas y
							salir = true;  // ...marcamos el flag de salir (para optimizar)
						}

					}

				}
				// Si el tamaño de la palabra del vector con el del contador de usadas es igual...
				if (cont_usadas == palabra_vector.size())
					// ...hemos encontrado una palabra!!
					encontradas.push_back(Resultado(palabra_vector,conjunto.puntuacion(palabra_vector) ));
			}
		}

		if (encontradas.empty())
			cout << RED <<"No se encontró ninguna palabra con esas letras" << BLACK << endl;
		else
		{
			if (strcmp(argv[4], "L") == 0)
			{
				// Modo longitud
				sort(encontradas.begin(), encontradas.end(), Resultado::cmp_pal());
			}
			else if (strcmp(argv[4], "P") == 0)
			{
				// Modo puntos
				sort(encontradas.begin(), encontradas.end(), Resultado::cmp_pts());
			}
			else
			{
				// Modo incorrecto
				cout<<"Error: El modo es incorrecto, debe ser L o P"<<endl;
				return 0; // Como el modo es incorrecto salimos del programa
			}

			// Pintamos las palabras encontradas
			for (vector<Resultado>::iterator it = encontradas.begin(); it!=encontradas.end(); ++it)
				cout << GREEN << *it << BLACK << endl;


		}
		// FIN DE LA BUSQUEDA DE LETRAS



		cout << "¿Quieres seguir jugando[S/N]?";
		cin >> type;
		cout << endl; // metemos un salto

	} while (tolower(type)!='n');



	return 0;

}