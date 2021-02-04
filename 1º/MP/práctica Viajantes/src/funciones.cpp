#include<iostream>
#include<string>
#include"funciones.h"

void mejorTrayecto(int m[][100],int ci,int tam, int v[], int v2[]){

	int k, ci_aux, ci_inicial;					//precio menor
	bool v_comprobar[tam], comprobador=0;			//comprobar ciudades
	for(int i=0;i<tam;i++){
		v_comprobar[i]=0;		//comprobar ciudades, todas falsas (sin visitar)
	}

	ci_inicial=ci;
	v_comprobar[ci]=1;			//ciudad inicial, es verdadera
	
	if(ci == 0){
		k=m[ci][1];
	}					//mira si la ciudad es 0
	else{
		k=m[ci][0];
	}
	
	v2[0]=ci;
	for(int i=0; i<tam;i++){		// comprueba si la k es menor

		for(int j=0;j<tam;j++){

			if(m[ci][j]<k && ci != j && v_comprobar[j]==0 || comprobador==0 && v_comprobar[j]==0 && ci != j){
				k=m[ci][j];
				ci_aux=j;
				comprobador=1;
			}
		

		}
		v_comprobar[ci]=1;
		ci=ci_aux;
		v[i]=k;
		v2[i+1]=ci_aux;
		comprobador=0;
		if(i==tam-2){
			v_comprobar[ci_inicial]=0;
		}


	}

	v2[tam]=ci_inicial;

}

int costeTrayecto(int v[], int tam){

	int suma=0;
	for(int i=0;i<tam;i++){
		suma+=v[i];
	}
return suma;
}


int vecinoMasCercano(int matriz[][100],int n_ciudades,int vector[],int vector2[]){

	int suma, k, ci;
	ci=0;
	mejorTrayecto(matriz, ci , n_ciudades, vector, vector2);
	k=costeTrayecto(vector, n_ciudades);
	
	for(int i=0;i<n_ciudades;i++){
		mejorTrayecto(matriz, i , n_ciudades, vector, vector2);
		suma=costeTrayecto(vector, n_ciudades);
		if(k>suma){
			k=suma;
			ci=i;
		}
	}
	
	return ci;

}

string trayectoToString(int v[], int tam){

	string rta="";

	for(int i=0;i<=tam;i++){
		rta = rta + to_string(v[i]);
		if(i<tam){
			rta+="-->";
		}
	}

	return rta;

}
