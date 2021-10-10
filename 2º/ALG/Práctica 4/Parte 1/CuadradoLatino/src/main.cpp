#include <iostream>
#include <ctime>
#include <vector>
#include "CuadradoLatino.h"

using namespace std;

int main(int argc, char * argv[]){
    int tam;
    clock_t tantes, tdespues;
    double t;
    string r1, r2, fila, columna, valor, s_tam;
    bool una_sol = true;
    vector< vector< vector <int>>> resultados;

    do{
        cout << "Introduce ancho/largo del cuadrado: ";
        cin >> s_tam;

        tam = atoi(s_tam.c_str());
    }while(tam <= 0);


    CuadradoLatino cuadrado(tam);

    cout << "\nQuieres fijar el valor de alguna casilla? ";
    cin >> r1;

    if (r1 == "si"){
        do{
            cout << "Indica fila[-1 para acabar proceso de introduccion]: ";
            cin >> fila;
            if  (fila != "-1") {
               cout << "\nIndica columna: ";
               cin >> columna;
               cout << "\nIndica valor: ";
               cin >> valor;

               if(!cuadrado.setPos(atoi(fila.c_str()), atoi(columna.c_str()), atoi(valor.c_str())))
                   cout << "\nParametros introducidos no son validos\n";
            }

        }while (fila != "-1");
    }

    do{
        cout << "\nQuieres una o todas las soluciones? [una/todas] ";
        cin >> r2;
    }while (r2 != "una" && r2 != "todas");


    if (r2 == "todas")
        una_sol = false;

    tantes = clock();
    cuadrado.BuscarSolucion(una_sol, true);
    tdespues = clock();

    t = ((double)(tdespues-tantes)/(CLOCKS_PER_SEC));

    cout << "Tiempo:" << endl;
    cout << tam << "    " << t << endl;
}
