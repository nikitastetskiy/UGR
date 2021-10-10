#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <cassert>

using namespace std;

/*
  Esta función une las dos partes del vector, ordenadas individualmente y calcula
  el número de inversiones que se producen entre las dos partes.
*/
int unir(int * vector, int mitad, int final, int * temp) {
  int izq = 0, der = mitad, i = 0;
  int inversiones = 0;

  while (izq < mitad || der < final) {
    //Si se ha llegado al final del vector derecho, o el elemento de la izquierda
    //es menor, añadimos el elemento de la izquierda
    if (der == final || (izq < mitad && vector[izq] <= vector[der])) {
      temp[i] = vector[izq];
      i++;
      izq++;
    }
    //Si se ha llegado al final del vector izquiedo, o el elemento de la derecha
    //es menor, añadimos el elemento de la derecha.
    else {
      temp[i] = vector[der];
      i++;
      der++;
      //Calculamos el número de inversiones (el elemento recién insertado con
      // todos los elementos restantes en la izquierda)
      inversiones += mitad - izq;
    }
  }

    for (int j = 0; j < final; j++)
      vector[j] = temp[j];

    return inversiones;
}

/*
  Función que calcula las inversiones de un vector. El vector es ordenado en el
  proceso. Argumentos: puntero al vector, números de componentes de este y un
  puntero a un vector auxiliar que se utilizará en el proceso. El vector auxiliar
  se proporciona para no incluir en el algoritmo los costes de sobrecarga.
*/
int ranking(int * vector, int n, int * temp) {
  //Caso base, un elemento, 0 inversiones
  int inversiones = 0;

  //El resto se calcula como la suma de las inversiones de la derecha con las de
  // la izquierda y con las generadas en la unión.
  if (n > 1) {
    int mitad = n/2;
    inversiones += ranking(vector, mitad, temp);
    inversiones += ranking(vector + mitad, n - mitad, temp + mitad);

    inversiones += unir(vector, mitad, n, temp);
  }

  return inversiones;
}

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int main(int argc, char * argv[]) {
  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  clock_t tantes, tdespues;
  double t;
  int n = atoi(argv[1]), inversiones;

  int * T = new int[n];
  int * temp = new int[n];
  assert(T);
  assert(temp);

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
  inversiones = ranking(T, n, temp);
  tdespues = clock();

  t = ((double)(tdespues-tantes)/(CLOCKS_PER_SEC));

  //cout << inversiones << " inversiones detectadas" << endl;
  cout << n << " " << t << endl;

  delete [] T;
  delete [] temp;
}
