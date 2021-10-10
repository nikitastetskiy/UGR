#include <fstream>
#include <cmath>
#include <list>
#include <vector>
#include <queue>
#include "Mapa.h"

using namespace std;

struct Nodo {
   vector<int> sol;
   int pos;
   int costo;
   int estimacion;

   Nodo(const vector<int> & s, int k, int c) {
      sol = s;
      pos = k;
      costo = c;
      estimacion = costo;
   }
};

struct ComparaNodos {
	bool operator()(const Nodo &a, const Nodo &n) const{
		return n.estimacion < a.estimacion;
	}
};

void Mapa::GreedyCiudadProxima() {
   const int N = GetNCiudades();
   solucion = vector<int>(N, -1);
   solucion[0] = 0;

   int d;
   double d_min;
	for (int i = 1; i < N; i++) {
      d_min = -1;
      for (int j = 1; j < N; j++) {
         if (!presenteEnSolucion(solucion, j)) {
            d = calcularDistancia(solucion[i - 1], j);
            if (d < d_min || d_min == -1) {
               solucion[i] = j;
               d_min = d;
            }
         }
      }
   }
}

void Mapa::BranchBround() {
   const int N = GetNCiudades();
   priority_queue<Nodo, vector<Nodo>, ComparaNodos > apo;
   bool fin=false;
   //Inicializamos el vector de distancias mínimas para las cotas
   vector<vector<double> > distanciasminimas;
   DistanciasMinimas(distanciasminimas);
   //Inicializamos la solución con sólo el nodo 0
   solucion = vector<int>(N, -1);
   solucion[0] = 0;
   Nodo nodo(solucion, 0, 0);
   apo.push(nodo);
   

   //Inicializamos la cota global lanzando un algoritmo greedy
   GreedyCiudadProxima();
   int cota_global = CostoSolucion(solucion);

   int k = 0;
   do {
      nodo = apo.top();
      apo.pop();
      if (EsFactible(nodo, cota_global, distanciasminimas)) {
            NNodosExp++;
            nodo.pos++;
            int costoinicial = nodo.costo;
            for (int i = 0; i < N; i++) {
               if (!presenteEnSolucion(nodo.sol, i)) {
                  nodo.sol[nodo.pos] = i;
                  nodo.costo = costoinicial + calcularDistancia(nodo.sol[nodo.pos - 1], nodo.sol[nodo.pos]);
                  if (nodo.pos == N - 1)
                     nodo.costo += calcularDistancia(nodo.sol[N - 1], nodo.sol[0]);
                  if (EsFactible(nodo, cota_global, distanciasminimas))
                     if (nodo.pos == N - 1) {
                           cota_global = nodo.costo;
                           solucion = nodo.sol;
                     }
                     else{
                        apo.push(nodo);
                        NPoda++;
                     }
                        
               }
            }
      }
      else
         fin=true;

      if(NMaxNodos < apo.size()){
         NMaxNodos = apo.size();
      }
      /*
      int memory = (apo.size()*sizeof(Nodo))/1048576;
      if (k == 10000) {
         cout << "la cola contiene " << apo.size() << " nodos de " << sizeof(Nodo) << " B Memoria total: " << memory << " MB" << endl;
         k = 0;
      }
      else
         k++;
      */


   } while ( (!apo.empty()) && (!fin));
}

bool Mapa::EsFactible(Nodo & n, int cota_global, vector<vector<double> > & distanciasminimas) const{

   double cota_local = n.costo;

   if (n.pos < GetNCiudades() - 1) {
      if (n.pos >= 1 && calcularDistancia(n.sol[0], n.sol[1]) == distanciasminimas[0][n.sol[0]])
         cota_local += distanciasminimas[1][n.sol[0]]/2;
      else
         cota_local += distanciasminimas[0][n.sol[0]]/2;

      if (n.pos >= 1 && calcularDistancia(n.sol[n.pos], n.sol[n.pos - 1]) == distanciasminimas[0][n.sol[n.pos]])
         cota_local += distanciasminimas[1][n.sol[n.pos]]/2;
      else
         cota_local += distanciasminimas[0][n.sol[n.pos]]/2;

      for(int i = 0; i<GetNCiudades(); i++){
   		if (!presenteEnSolucion(n.sol, i)){
            cota_local += distanciasminimas[0][i]/2;
            cota_local += distanciasminimas[1][i]/2;
   		}
      }
   }
   n.estimacion = cota_local;


   return cota_local < cota_global;
}


int Mapa::GetNCiudades() const {
   return ciudades.size();
}

int Mapa::CostoSolucion(vector<int> & v) const {
   int N = GetNCiudades();
   int ciudadanterior, nuevaciudad, costo = 0;
   bool continuar = true;
   ciudadanterior = 0;
   for (int i = 1; i < N && continuar; i++) {
      nuevaciudad = v[i];
      if (nuevaciudad == -1) {
         continuar = false;
      }
      else {
         costo += calcularDistancia(ciudadanterior, nuevaciudad);
         ciudadanterior = nuevaciudad;
      }
   }
   if (continuar)
      costo += calcularDistancia(v[N - 1], 0);

   return costo;
}


int Mapa::calcularDistancia(int a, int b) const {
    pair<double,double> ciudada = ciudades[a], ciudadb = ciudades[b];
    double dist = sqrt((ciudadb.first-ciudada.first)*(ciudadb.first-ciudada.first) + (ciudadb.second-ciudada.second)*(ciudadb.second-ciudada.second));
    return round(dist);
    //return (int) dist;
}

bool Mapa::presenteEnSolucion(const vector<int> & v, int x) const{
    bool presente = false;

    for (int i=0; i < GetNCiudades() && !presente && v[i] != -1; i++)
        if(v[i] == x)
            presente = true;

    return presente;
}

void Mapa::DistanciasMinimas(vector<vector<double> > & distanciasminimas) const {
   const int N = GetNCiudades();
   distanciasminimas = vector<vector<double> > (2);
   distanciasminimas[0] = vector<double>(N, -1);
   distanciasminimas[1] = vector<double>(N, -1);
   vector <int> escogidos(N);
   int d;

   for (int i = 0; i < N; i++)
      for (int j = 1; j < N; j++)
         if (i != j) {
            d = calcularDistancia(i, j);
            if (distanciasminimas[0][i] == -1 || d < distanciasminimas[0][i]) {
               distanciasminimas[0][i] = d;
               escogidos[i] = j;
            }
         }

   for (int i = 0; i < N; i++)
      for (int j = 1; j < N; j++)
         if (i != j && j != escogidos[i]) {
            d = calcularDistancia(i, j);
            if ((distanciasminimas[1][i] == -1 || d < distanciasminimas[1][i])) {
               distanciasminimas[1][i] = d;
            }
         }
}

void Mapa::mostrarSolucion(){
    cout << "DIMENSION: " << solucion.size() << endl;
    for (int i=0; i<solucion.size(); i++)
        cout << solucion[i]+1 << "\n";
    cout << endl;
}

void Mapa::mostrarCoste(){
    cout << "Costo: " << CostoSolucion(solucion) << endl;
}

bool Mapa::cargarDeFichero(const char *fichero){
   NMaxNodos = 0;
   NNodosExp = 0;
   NPoda = 0;
    bool b = true;
    int num, basura;
    pair<double, double> aux;

    ifstream fentrada;

    fentrada.open(fichero);

    if (fentrada){
        fentrada.ignore(100, ':');
        fentrada >> num;

        for(int i=0; i<num; i++){
            fentrada >> basura;
            fentrada >> aux.first;
            fentrada >> aux.second;
            ciudades.push_back(aux);
        }

        if (!fentrada){
            cerr << "\nError en la lectura del fichero"<< endl;
            b = false;
        }
        fentrada.close();
    }else{
        cerr << "\nError de apertura de fichero" <<endl;
        b = false;
    }

    return b;
}

bool Mapa::guardarSolucion(const char *fichero){
    bool b = true;
    int num, basura;
    pair<double, double> aux;

    ofstream fsalida;

    fsalida.open(fichero);

    if (fsalida){

      fsalida << "DIMENSION: " << solucion.size() << endl;
      for (int i=0; i<solucion.size(); i++)
          fsalida << solucion[i]+1 << "\n";
      fsalida << endl;

        fsalida.close();
    }else{
        cerr << "\nError de apertura de fichero" <<endl;
        b = false;
    }

    return b;
}
