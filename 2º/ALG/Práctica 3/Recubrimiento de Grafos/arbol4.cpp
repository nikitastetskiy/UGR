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

vector<int> recubrimientoGreedy(int **v, int numnodes){
  int cont = 0, hijos = 1, indice = 0, cont_ant, totales = numnodes, i=0;
  bool escogidos[numnodes];
  for (int a=0; a<numnodes; a++)
      escogidos[a] = false;
  vector<int> res;      //Conjunto de candiadtos solucion, inicialmente vacío.
  //Los candidatos son los nodos del arbol
  while(totales > 1){   //Repasa enl arbol hasta que se hayan borrado todos los nodos excepto la raíz. Es tambien funcion solucion
      indice = 0;
      hijos = 1;
      while (cont != 0 || hijos != 0){  //Bucle que recorre arbol por niveles
        for(i=indice; i<indice+hijos;i++){  //Bucle que recorre filas de la matriz de adyacencia
          cont_ant = cont;
          for(int j=0; j<numnodes; j++)     //Bucle que recorre columnas de la matriz de adyacencia
            if(v[i][j] == 1){
              cont++;
            }
          if(cont_ant == cont)         //Si es hoja (es decir, no hay ninugn 1 en la fila). Esto tambien es función de seleccion.
            for (int t=0; t<i; t++)
                if (v[t][i] == 1){     //, escojo al padre
                    v[t][i] = 0;        //Borro al nodo de la fila del padre
                    totales--;
                    for (int b=0; b<t; b++)
                        if(v[b][t] == 1){       //Borro al padre de la fila del abuelo
                            v[b][t] = 0;
                            totales--;
                        }
                    
                    if(!escogidos[t]) {    //Vigilo que el padre no este metido
                        res.push_back(t);
                        escogidos[t] = true;    //Lo marco como escogido
                    }
                    
                }
        }
        //Se actualizan los indicadores necesarios para el siguiente nivel del arbol
        indice = i;

        hijos = cont;
        cont = 0;
      }
  }
  //Creo que no hace falte funcion de factibilidad (siempre encuentra la solucion optima, creo)
  return res;
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
  
  vector<int> resultado = recubrimientoGreedy(v, numnodes);
  
  cout << "Los nodos que recubren son: " << endl;
  for (int t=0; t<resultado.size();t++)
      cout << resultado[t] << "  ";
  cout << endl;
  
  for(int i=0; i<numnodes; i++)
      delete []v[i];
      
  delete []v;
}
