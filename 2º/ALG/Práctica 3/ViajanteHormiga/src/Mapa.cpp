#include <fstream>
#include <cmath>
#include <list>
#include "Mapa.h"

using namespace std;

void Mapa::Insercion() {
    vector<int> tmp, vacio;
    int max_norte = ciudades[0].second, max_este = ciudades[0].first, max_oeste = ciudades[0].first, pos_este, pos_oeste, pos_norte;
    int dist_min, dist_act, min_pos, lugar_min, lugar_aux, c; //min_pos es la posicion de la solucion en el vector de ciudades y lugar_min la posicion en el vector de soluciones que ocuapara el nuevo minimo.
    bool stop;
    //Busco e inserto la ciudad mas al este, mas al oeste y mas al norte
    for (int j=0; j<ciudades.size(); j++){
        if(ciudades[j].first > max_este){
            pos_este = j;
            max_este = ciudades[j].first;
        }if(ciudades[j].first < max_oeste){
            pos_oeste = j;
            max_oeste = ciudades[j].second;
        }if(ciudades[j].second > max_norte){
            pos_norte = j;
            max_norte = ciudades[j].second;
        }
    }

    solucion.push_back(pos_este);
    solucion.push_back(pos_oeste);
    solucion.push_back(pos_norte);
    //Recorro el resto de ciudades
    while(solucion.size() < ciudades.size()){
        stop = false;
        for(int a=0; a<ciudades.size() && !stop; a++){       //Inicializo dist_min y min_pos con la primera ciudad que no este incluida ya en solucion
            if(!presenteEnSolucion(a)){
                dist_min = calcularLongitud(a, lugar_min);
                min_pos = a;
                stop = true;
            }
        }

        for(int i=0; i<ciudades.size(); i++){		     //Recorro el resto de ciudades
            if(!presenteEnSolucion(i)){
                dist_act = calcularLongitud(i, lugar_aux);   //Para cada una de ellas calculo la longitud de camino que resultaria
                if(dist_act < dist_min){
                    dist_min = dist_act;
                    min_pos = i;
                    lugar_min = lugar_aux;
                }
            }
        }
        for(c=0; c<lugar_min; c++)			     //Inserto la ciudad mas conveniente en la posicion mas conveniente
            tmp.push_back(solucion[c]);
        tmp.push_back(min_pos);
        for(int d=c; d<solucion.size(); d++)
            tmp.push_back(solucion[d]);
        solucion = tmp;
        tmp = vacio;
    }
}

void Mapa::ColoniaHormigas(int n_iteraciones, int n_hormigas) {
   solucion.clear();
   int nciudades = ciudades.size();
   double * * feromonas = new double * [nciudades];
   for (int i = 0; i < nciudades; i++) {
      feromonas[i] = new double[nciudades];
      for (int j = 0; j < nciudades; j++)
         feromonas[i][j] = 1;
   }
   bool * ciudadesVisitadas = new bool[nciudades];
   list<int> mejorsolucion;
   int mejorcoste = 1e6;

   for (int l = 0; l < n_iteraciones; l++) {
      list<int> * camino = new list<int>[n_hormigas];

      for (int i = 0; i < n_hormigas; i++) {
         int costecamino = 0;
         for (int j = 0; j < nciudades; j++)
            ciudadesVisitadas[j] = false;

         int ciudadanterior = rand()%nciudades;
         camino[i].push_back(ciudadanterior);
         ciudadesVisitadas[ciudadanterior] = true;

         /*
         //Empiezan todas en la ciudad 0
         camino[i].push_back(0);
         ciudadesVisitadas[0] = true;
         int ciudadanterior = 0;
         */

         for (int j = 1; j < nciudades; j++) {
            int proximaciudad;
            //////////////////////////////////////////
            //Escoger la ciudad en base a las feromonas.

            //Primero vamos a crear un monto de posibilidades
            double probabilidades = 0;
            for (int k = 0; k < nciudades; k++) {
               if (!ciudadesVisitadas[k])
                  probabilidades += feromonas[ciudadanterior] [k];
            }
            //Generamos un double al azar
            double f = (double)rand() / RAND_MAX;
            f = f * probabilidades;

            //Comprobamos de que ciudad es
            for (int k = 0; k < nciudades && f > 0; k++) {
               if (!ciudadesVisitadas[k])
                  f -= feromonas[ciudadanterior][k];
               if (f <= 0)
                  proximaciudad = k;
            }
            //////////////////////////////////////////

            ciudadesVisitadas[proximaciudad] = true;
            int distanciarecorrida = calcularDistancia(ciudadanterior, proximaciudad);

            camino[i].push_back(proximaciudad);
            costecamino += distanciarecorrida;
            ciudadanterior = proximaciudad;
         }
         costecamino += calcularDistancia(camino[i].front(), camino[i].back());
         if (costecamino < mejorcoste) {
            mejorcoste = costecamino;
            mejorsolucion = camino[i];
         }
      }

      //Colocar feromonas en la matriz
      for (int i = 0; i < n_hormigas; i++) {
         list<int>::iterator j = camino[i].begin();
         int ciudadanterior = *j;
         int proximaciudad, distanciarecorrida;
         j++;
         while (j != camino[i].end()) {
            proximaciudad = *j;
            distanciarecorrida = calcularDistancia(ciudadanterior, proximaciudad);
            if (distanciarecorrida > 0)
               feromonas[ciudadanterior][proximaciudad] += 1.0 / distanciarecorrida;
            else
               feromonas[ciudadanterior][proximaciudad] += 1.0;
            ciudadanterior = proximaciudad;
            j++;
         }
      }

      delete [] camino;
   }



   //Al final copiamos el mejor camino encontrado
   for (list<int>::iterator i = mejorsolucion.begin(); i != mejorsolucion.end(); i++) {
      solucion.push_back(*i);
   }

   for (int i = 0; i < nciudades; i++)
      delete [] feromonas[i];
   delete [] feromonas;
   delete [] ciudadesVisitadas;
}

int Mapa::CostoSolucion() {
   int ciudadanterior, nuevaciudad, costo = 0;
   ciudadanterior = 0;
   for (int i = 1; i < solucion.size(); i++) {
      nuevaciudad = solucion[i];
      costo += calcularDistancia(ciudadanterior, nuevaciudad);
      ciudadanterior = nuevaciudad;
   }

   return costo;
}

Mapa::Mapa() {
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
}

int Mapa::calcularLongitud(int pos, int lugar){
    int aux = 0, min = 0;
    //Inicializo min insertando el elemento en la primera posicion posible, 0:
    min += calcularDistancia(pos, solucion[0]);
    for (int t=0; t<solucion.size() - 1; t++){
        min += calcularDistancia(solucion[t], solucion[t+1]);
    }
    min += calcularDistancia(solucion[solucion.size()-1], pos);
    //Busco la mejor posicion en la sucesion de ciudades solucion en la que puedo insertar la ciudad pos
    for(int i=0; i<solucion.size() - 1; i++){
        aux = 0;
        for(int j=0; j<i; j++)
            aux += calcularDistancia(solucion[j], solucion[j+1]);
        aux += calcularDistancia(solucion[i], pos) + calcularDistancia(pos, solucion[i + 1]);
        for(int k=i + 1; k<solucion.size() - 1; k++)
            aux += calcularDistancia(solucion[k], solucion[k+1]);
        aux += calcularDistancia(solucion[solucion.size()-1], solucion[0]);
        if(aux < min){
            min = aux;
            lugar = i+1;
        }
    }

    return min;
}

int Mapa::calcularDistancia(int a, int b){
    pair<double,double> ciudada = ciudades[a], ciudadb = ciudades[b];
    int dist = sqrt((ciudadb.first-ciudada.first)*(ciudadb.first-ciudada.first) + (ciudadb.second-ciudada.second)*(ciudadb.second-ciudada.second));
    return dist;
}

bool Mapa::presenteEnSolucion(int x){
    bool presente = false;

    for (int i=0; i<solucion.size() && !presente; i++)
        if(solucion[i] == x)
            presente = true;

    return presente;
}

void Mapa::mostrarSolucion(){
    cout << "DIMENSION: " << solucion.size() << endl;
    for (int i=0; i<solucion.size(); i++)
        cout << solucion[i]+1 << "\n";
    cout << endl;
}
void Mapa::mostrarCoste(){
    cout << "Costo: " << CostoSolucion() << endl;
}

bool Mapa::cargarDeFichero(const char *fichero){
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
