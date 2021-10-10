
#include <fstream>
#include <iostream>

#include "Diccionario.h"
#include "ConjuntoLetras.h"

using namespace std;

int main(int argc, char * argv[]){
    
	if (argc!=4){
        cout<<"\n...Error en el numero de parametros...\n";
        return 1;
    }

    ifstream flujo_d (argv[1]);
	ifstream flujo_l (argv[2]);
	ofstream flujo_s (argv[3]);

    if (!flujo_d or !flujo_l or !flujo_s){
        cout<<"\n...Error en el argumento de parametros...\n";
        return 0;
    }

    flujo_s << "#Letra\tFrecuencia Absoluta\tFrecuencia Relativa" << endl;

    Diccionario diccionario;
    ConjuntoLetras conjunto;
    flujo_d >> diccionario;
    flujo_l >> conjunto;

	float suma=0;
    Letra l;
	for (int i=0; i<conjunto.size(); i++){
        l = conjunto[i];
        int apariciones = diccionario.getNumero(*l);
		suma += apariciones;
    }


    for (int i=0; i<conjunto.size(); i++){
        l = conjunto[i];
        int apariciones = diccionario.getNumero(*l);
        float puntos = (apariciones/suma)*100;
        flujo_s << *l << "\t\t" << apariciones << "\t\t\t" << puntos << endl;
    }

    flujo_s.close();
    return 0;
}
