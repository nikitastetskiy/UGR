#include<iostream>
#include<string>
#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

using namespace std;

void mejorTrayecto(int m[][100],int ci,int tam, int v[], int v2[]);
int costeTrayecto(int v[], int tam);
int vecinoMasCercano(int matriz[][100],int n_ciudades,int vector[],int vector2[]);
string trayectoToString(int v[], int tam);

#endif
