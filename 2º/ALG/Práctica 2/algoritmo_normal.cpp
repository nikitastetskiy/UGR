#include <vector>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <cassert>

using namespace std;

int ranking(int v[], int tam){	//La funcion que cuenta las inversiones
	int cont = 0;
	
	for (int i=0; i<tam; i++){	//Recorro cada elemento del vector
		for (int j=i+1; j<tam; j++){	//Recorro los elementos restantes a partir del seleccionado
			if(v[i] > v[j])
				cont ++;
		}
	}
	
	return cont;
}

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  clock_t tantes, tdespues;
  double t;
  int n = atoi(argv[1]), inversiones;

  int * T = new int[n];
  assert(T);

  srand(time(0));

  for (int j=0; j<n; j++) 
    T[j]=j+1;
  for (int j=n-1; j>0; j--) {
     double u=uniforme();
     int k=(int)(j*u);
     int tmp=T[j];
     T[j]=T[k];
     T[k]=tmp;
  }
  
  /*
  cout << "Vector generado: " << endl;	//Muestra el vector por pantalla
  for (int t=0; t<n; t++)
  	cout << T[t] << endl;
	cout << endl;
	*/
  
  tantes = clock();
  inversiones = ranking(T, n);
  tdespues = clock();

  t = ((double)(tdespues-tantes)/(CLOCKS_PER_SEC));

  //cout << inversiones << " inversiones detectadas" << endl;
	cout << n << " " << t << endl;
}
