#include <iostream>
#include <unistd.h>
using namespace std;
//#include <ctime>
#include <cstdlib>
#include <cassert>
#include <list>
#include <vector>
//genera un arbol aleatorio con un numero (numnodes) de nodos y un maximo (maxh) de hijos de cada nodo

list<int> cola;

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}
  
int totalNiveles(int **v, int numnodes)
{
  int cont = 0, nivel = 0, indice = 0, hijos = 1;
  int i=0;

  while (cont != 0 || hijos != 0){
    for(i=indice; i<indice+hijos;i++){
      for(int j=0; j<numnodes; j++)
        if(v[i][j] == 1){
          cont++;
        }
    }
    indice = i;
    nivel++;
    hijos = cont;
    cont = 0;
  }

  return nivel;
}

int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_nodes>" <<  " <num_hijos_max>" << endl;
      return -1;
    }

  int numnodes = atoi(argv[1]);
  int maxh=atoi(argv[2]);


  srand(time(NULL));
  int **v;
  v =  new int * [numnodes];
  assert(v);
  
  for (int i = 0; i < numnodes; i++)
      v[i]= new int [numnodes];
  int n=1; //cuenta el n�mero de nodos generados hasta ahora
  int i=0; //etiqueta del nodo
  cola.push_back(i); //es una cola FIFO
  while (n < numnodes) {
    i=cola.front();
    cola.pop_front();
    double u=uniforme();
    int ch=1+(int)(maxh*u); //entero aleatorio entre 1 y maxh
    if ((ch+n) > numnodes) ch=numnodes-n; //para no generar m�s de numnodes nodos
    for (int j=n; j<ch+n; j++) {
       v[i][j]=1; //v es la matriz de adyacencia del �rbol
       cola.push_back(j);
    }
    n=n+ch;
  }
  while (!cola.empty()) cola.pop_front();

  for (int i=0; i<numnodes; i++) {
     for (int j=0; j<numnodes; j++)
      cout << v[i][j] << " ";
    cout << " " << endl;
  }
  
  //ALGORITMO
  int cont = 0, nivel = 0, indice = 0, hijos = 1;
  
  i=0;
  
  vector<int> impares;
  vector<int> pares;
  vector<int> solucion;

  while (cont != 0 || hijos != 0){
    for(i=indice; i<indice+hijos;i++){
      for(int j=0; j<numnodes; j++)
        if(v[i][j] == 1){
          cont++;
        }
        if (nivel % 2 == 0)
          pares.push_back(i);
        else
          impares.push_back(i);
    }
    indice = i;
    nivel++;
    
    hijos = cont;
    cont = 0;
  }
  
  if (pares.size() < impares.size())
      solucion = pares;
  else
      solucion = impares;
  //FIN ALGORITMO
  cout << "Los nodos que recubren son: " << endl;
  for (int t=0; t<solucion.size();t++)
      cout << solucion[t] << "  ";
  cout << endl;
  
}
