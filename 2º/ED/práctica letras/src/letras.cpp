#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "Letra.h"
#include "Diccionario.h"
#include "ConjuntoLetras.h"
#include "BolsaLetras.h"
#include "Puntuacion.h"

using namespace std;

int main(int argc, char * argv[]){
	if (argc!=5){
		cout<<"\n...Error en el numero de parametros...\n";
		return 1;
	}

	ifstream flujo_d (argv[1]);
	ifstream flujo_l (argv[2]);

	if (!flujo_d or !flujo_l){
		cout<<"\n...Error en el argumento de los parametros...\n";
		return 0;
	}

	// ... INICIALIZAMOS ...
	int longitud = atoi(argv[3]);
	char car;
	Diccionario diccionario;
	BolsaLetras bolsa;
	ConjuntoLetras conjunto;
	flujo_d >> diccionario;
	flujo_l >> conjunto;
	conjunto >> bolsa;

	
	while (tolower(car)!='n'){
		cout << "Las letras son:\t\t";
		vector<Letra> letras;
		Letra l;
		int aleatorio;
		string palabra;
		srand(time(0));

		const int TAM = 94;
		int ocupadas[TAM];
		for(int i=0; i<TAM;i++){
			ocupadas[i]=0;
		}

		for (int i=0; i<longitud; i++){
			aleatorio = rand() % bolsa.size();
			while(ocupadas[aleatorio]>=bolsa[aleatorio].getNum()){
				aleatorio = rand() % bolsa.size();
			}
			ocupadas[aleatorio]++;
			l = bolsa[aleatorio];
			letras.push_back(l);
			cout << *l << '\t';
		}

		for (int i=0; i<letras.size(); i++){
			l = letras[i];
			palabra.push_back(tolower(*l));
		}
		cout<<endl;
		bool error = false;
		string palabra_introducida;
		cout << "Dime tu solucion: ";
		cin >> palabra_introducida;
		while (!error){
			error = true;
			string auxiliarr = palabra;
			for (int i=0; error && i<palabra_introducida.size(); i++){
				char letra = palabra_introducida[i];
				if (palabra.find(letra) == string::npos or auxiliarr.find(letra)== string::npos){
					error = false;
				}
				else{
					int found = auxiliarr.find(letra);
					auxiliarr.erase(auxiliarr.begin()+found);
				}
			}
			if(palabra_introducida.size()>longitud or !error){
				cout << "Secuencia introducida de manera erronea. Dime tu solucion de nuevo:";
				cin >> palabra_introducida;
			}
		}

		vector<Puntuacion> solucion;

		if (diccionario.Esta(palabra_introducida)){
			cout<<endl<<endl;
			cout << palabra_introducida << "\t\tPuntos: " << conjunto.resultado(palabra_introducida)<<endl;
		}
		else{
			cout <<"Esta palabra no se encuentra en el diccionario"<<endl<<endl;
		}
		cout<<"-----------------------------------------"<<endl;
		cout << "Mis soluciones son: " << endl<<endl;
		vector<string> v;
		int cont = 0;
		while(cont<longitud){
			v = diccionario.PalabrasLongitud(cont);
			for (vector<string>::iterator it = v.begin(); it!=v.end(); ++it){
				string p_conjunto = *it;
				vector<bool> letras_usadas(letras.size(), false);
				int c = 0;
				for (int segundo =0; segundo<p_conjunto.size(); segundo++){
					char letra_actual = p_conjunto[segundo];
					int primero=0;
					while (primero<palabra.size()){
						if (palabra[primero] == letra_actual && !letras_usadas[primero]){
							letras_usadas[primero] = true;
							c++;
						}
						primero++;
					}
				}
				if (c == p_conjunto.size()){
					solucion.push_back(Puntuacion(p_conjunto,conjunto.resultado(p_conjunto) ));
				}
			}
			cont++;
		}

		bool vera = false;
		if(strcmp(argv[4], "P") == 0 or strcmp(argv[4], "L")==0){
			vera=true;
		}

		if (!solucion.empty()){
			if(vera){
				if (strcmp(argv[4], "P") == 0){
					sort(solucion.begin(), solucion.end(), Puntuacion::StructPuntos());
				}
				else if (strcmp(argv[4], "L") == 0){
					sort(solucion.begin(), solucion.end(), Puntuacion::StructPalabra());
				}
			}
			else{
				cout<<"L o P mal introducido"<<endl;
				return 0;
			}
			vector<Puntuacion>::iterator it = solucion.begin();
			Puntuacion iterador = *it;
			Puntuacion iterador_siguiente = *it;
			int contador=0;
			int cont=0;
			for (; it!=solucion.end(); ++it){
				cout << *it << endl;
				contador++;
				iterador_siguiente = *it;
				if(iterador.getResul()<iterador_siguiente.getResul()){
					iterador=iterador_siguiente;
				}
				if(contador == 4){
					cout <<endl<< "¿Ver todas las respuestas posibles[S/N]?";
					cin >> car;
					if(car == 'N' or car == 'n'){
						it=solucion.end();
						it--;
					}
				}
			}
			cout<< endl;
			cout<<"-----------------------------------------"<<endl;
			cout<<"Mi Mejor Solucion:"<<endl<<iterador<<endl<<endl;
		}
		else{
			cout <<"No existen definiciones con esa palabra" << endl;	
		}
	
		cout << "¿Quieres seguir jugando[S/N]?\n";
		cin >> car;
	}

	return 0;

}