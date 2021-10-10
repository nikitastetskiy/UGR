#include <fstream>
#include <cmath>
#include "Mapa.h"

using namespace std;

Mapa::Mapa() {
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
}

void Mapa::calcularSolucion(){
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
    cout << endl;
    for (int i=0; i<solucion.size(); i++)
        cout << solucion[i]+1 << "\n";
    cout << endl;
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
