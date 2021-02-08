/*
APELLIDOS Y NOMBRE:	Nikita Stetskiy
GRUPO DE PRACTICAS: JUEVES

*/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

struct Robot{
	string nombre;
	float x,y;
};

void imprimirVector(Robot v[], int n)  {
	for (int i=0; i<n; i++)
		cout << v[i].nombre << "->(" << v[i].x << "," << v[i].y << ")," << endl;
	
}

	// agregar aqui las funciones solicitadas

bool afectado(Robot posicion, int posx, int posy, float rango){

	//indica si un robot esta afectado, 1 no lo esta, 0 si lo esta	
	bool verdadero;
	float distancia;
	distancia=sqrt(((posicion.x-posx)*(posicion.x-posx))+((posicion.y-posy)*(posicion.y-posy)));
	verdadero=(distancia>rango);
	return verdadero;
}

void supervivientes(Robot *todos, int pos_x, int pos_y, int num1, float rango, Robot * & super, int & num2){
	num2=0;
	//comprueba si el robot esta fuera de la zona o el rango
	for(int i=0;i<num1;i++){
		if(afectado(todos[i], pos_x, pos_y, rango)){
			num2++;
		}
	}
	//se crea un nuevo vector y se rellena con los robots activos
	super= new Robot[num2];
	
	num2=0;
	for(int j=0;j<num1;j++){
		if(afectado(todos[j], pos_x, pos_y, rango)){
			super[num2]=todos[j];
			num2++;
		}
	}

} 

int main()  {
	Robot *A=0;
	Robot *B=0;
	int elemA, elemB;
	string nombre;
	float variable;
	
	// leer los datos

	cin>>elemA;

	A= new Robot[elemA];

	for(int i=0;i<elemA;i++){
		cin>>nombre;
		A[i].nombre=nombre;
		cin>>variable;
		A[i].x=variable;
		cin>>variable;
		A[i].y=variable;
	}

	cout << "Robots leidos " << endl;
	imprimirVector(A,elemA);

	// fijamos posicion del inhibidor
	int x = 10.0; 
	int y = 10.0;
	float rango = 7.0;
	
	//detectar supervivientes
	
	supervivientes(A, x, y, elemA, rango, B, elemB);
	
	// mostrar robots supervivientes

	cout << "\n\n\nRobots activos " << endl;
	imprimirVector(B, elemB);

	if(A!=0){
		delete []A;
	}
	if(B!=0){
		delete []B;
	}
	
	return 0;
}

// ejemplo de datos
/*
10
rbt1 9.1 9.1
rbt2 10.5 10.5
rbt3 11.0 11.0
rbt4 3.5 1.2
rbt5 2.7 10.3
rbt6 4.5 6.7
rbt7 19.9 10.10
rbt8 1.1 4.4
rbt9 10.0 9.0
rbt10 0.0 0.0

*/

