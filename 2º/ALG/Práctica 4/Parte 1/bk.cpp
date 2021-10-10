#include <vector>
#include <ctime>
#include<iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <random>

using namespace std;

struct pos{
    int val;
    bool fijo;
};

void mostrarTablero(vector< vector <pos>> tablero){
    for (int i=0; i<tablero.size(); i++){
        for(int j=0; j<tablero.size(); j++)
            cout << tablero[i][j].val << "  ";
        cout << "\n";
    }
    cout << "\n";
}

class CuadradoLatino{
private:
    vector< vector <pos>> sol;

    void sigVal(int k1, int k2){
        if (!sol[k1][k2].fijo)
            if(sol[k1][k2].val != sol.size())
        	   sol[k1][k2].val++;
            else
        	   sol[k1][k2].val = -1;
    }

    bool TodosGenerados(int k1, int k2){
        bool todosGenerados = false;

        if (sol[k1][k2].val == sol.size() || sol[k1][k2].fijo)
            todosGenerados = true;

        return todosGenerados;
    }

    bool Factible(int k1, int k2){
        bool factible = true;

        if(sol[k1][k2].val == -1)   //|| sol[k1][k2].val == sol.size()
        	factible = false;
        else{
        	for(int i=0; i<k1 && factible; i++){
            	if (sol[i][k2].val == sol[k1][k2].val)
            	    factible = false;
        	}

            for(int j=0; j<k2 && factible; j++){
                if (sol[k1][j].val == sol[k1][k2].val)
                    factible = false;
            }
        }

        return factible;
    }
public:
    CuadradoLatino(int n){
        for (int i=0; i<n; i++){
            vector<pos> aux;
            sol.push_back(aux);
            for(int j=0; j<n; j++){
                pos tmp;
                sol[i].push_back(tmp);
                sol[i][j].val = -1;
                sol[i][j].fijo = false;
            }
        }
    }

    bool setPos(int fil, int col, int n){
        bool valido = true;

        if (fil < 0 || col < 0 || n < 0)
            valido = false;

        if (sol[fil][col].fijo)
            valido = false;

        for(int i=0; i<fil && valido; i++){
            for(int j=0; j<col; j++)
                if (sol[i][j].val == sol[fil][col].val)
                    valido = false;
        }

        if (valido){
            sol[fil][col].val = n;
            sol[fil][col].fijo = true;
        }

        return valido;
    }

    vector< vector< vector <pos>>> buscarSol(bool sol_unica){
        vector< vector< vector <pos>>> res;
        bool ok = false;
        int guia1 = 0, guia2 = 0, cont = 0;
        while (guia1 >= 0 && guia1 < sol.size() && !ok){
            while (guia2 >= 0 && guia2 < sol.size() && !ok){
                sigVal(guia1, guia2);
                while (!TodosGenerados(guia1, guia2) && !Factible(guia1, guia2)){
                    sigVal(guia1, guia2);
                }
                if (!TodosGenerados(guia1, guia2) || sol[guia1][guia2].fijo)
                    if ((guia1 == sol.size() - 1) && (guia2 == sol.size() - 1)){
                        if(sol_unica){
                            ok = true;
                        }else{
                            res.push_back(sol);
                        }
                    }else{
                        guia2 = guia2 + 1;
                    }
                else{
                    if(guia2 == sol.size()-1 && guia1 == sol.size()-1)
                        guia1 = 0;
                    guia2 = guia2 - 1;
                }
            }
            guia2 = 0;

            guia1 = guia1 + 1;
        }

        return res;
    }

    void imprimirSol(){
        cout << "SOLUCION: " << endl;
        mostrarTablero(sol);
    }
};

int main(int argc, char * argv[]){
    int tam;
    clock_t tantes, tdespues;
    double t;
    string r1, r2, fila, columna, valor, s_tam;
    bool una_sol = true;
    vector< vector< vector <pos>>> resultados;

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
            cout << "Indica fila: ";
            cin >> fila;
            cout << "\nIndica columna: ";
            cin >> columna;
            cout << "\nIndica valor [-1 para acabar proceso de introduccion]: ";
            cin >> valor;

            if(!cuadrado.setPos(atoi(fila.c_str()), atoi(columna.c_str()), atoi(valor.c_str())))
                cout << "\nParametros introducidos no son validos\n";

        }while (valor != "-1");
    }

    do{
        cout << "\nQuieres una o todas las soluciones? [una/todas] ";
        cin >> r2;
    }while (r2 != "una" && r2 != "todas");
    

    if (r2 == "todas")
        una_sol = false;

    cuadrado.imprimirSol();

    tantes = clock();
    resultados = cuadrado.buscarSol(una_sol);
    tdespues = clock();

    t = ((double)(tdespues-tantes)/(CLOCKS_PER_SEC));

    //cout << util_v << "    " << t << endl;
    if (resultados.size() < 2)
        cuadrado.imprimirSol();
    else
    //cout << "SOLUCIONES: \n";
        for (int i=0; i<resultados.size(); i++)
            mostrarTablero(resultados[i]);
}