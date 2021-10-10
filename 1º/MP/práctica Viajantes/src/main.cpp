#include<iostream>
#include<string>
#include"funciones.h"

using namespace std;

int main(){

	const int TAM=100;
	int n_ciudades, matriz[TAM][TAM], vector[TAM], ci, x, vector2[TAM];

	cin>>n_ciudades;
	
	for(int i = 0; i < n_ciudades; i++){

		for(int j=0; j<n_ciudades; j++){
			cin>>x;
			matriz[i][j]=x;
		}
	}

	cout<<"----------------------------------------"<<endl;
	

	ci=vecinoMasCercano( matriz, n_ciudades, vector, vector2);


	mejorTrayecto(matriz, ci , n_ciudades, vector, vector2);
	cout<<trayectoToString(vector2, n_ciudades)<<endl;
	cout<<"La suma es: "<<costeTrayecto(vector, n_ciudades)<<endl;


}
