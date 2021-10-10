#include <iostream>
#include "miniwin.h"
#include "particula.h"
#include "Nubeparticula.h"

using namespace miniwin;

using namespace std;


ostream& operator<<(ostream & flujo, const NubeParticulas & p){
			for(int i=0; i<p.GetCapacidad();i++){
				flujo << endl << " X: " <<p.ObtieneParticula(i).getX();
				flujo << endl << " Y: " <<p.ObtieneParticula(i).getY();
				flujo << endl << " Velocidad X: " << p.ObtieneParticula(i).getDX();
				flujo << endl << " Velocidad Y: " << p.ObtieneParticula(i).getDY();
				flujo << endl << " Color: " << p.ObtieneParticula(i).getColor();
			}
			flujo << endl;
			return flujo;
}
	
int main(){

	int ancho=800, alto=600;
	vredimensiona(ancho, alto);
	Color v[7]={AZUL, BLANCO, MAGENTA, CYAN, ROJO, AMARILLO, VERDE};

	srand(time(0));
	NubeParticulas base(3);

	// constructor de copia
	NubeParticulas nuevo(base);
	nuevo.Mover1(ancho, alto);

	// constructor por defecto
	NubeParticulas otro;

	// sobrecarga de asignacion
	otro = nuevo;
	otro.Mover1(ancho, alto);

	// mostrar
	cout << "\n Conjunto Inicial" << endl;
	cout << base;
	cout << "\n Conjunto Movido 1" << endl;
	cout << nuevo;
	cout << "\n Conjunto Movido 2" << endl;
	cout << otro;
	cout << endl;

	// probaremos el redimensionamiento
	int N;
	Particula p;
	while (tecla() != ESCAPE){
		otro.Mover1(ancho, alto);
		borra();
		for(int i=0; i<otro.GetCardinal();i++){
			p = otro.ObtieneParticula(i);
			color(p.getColor());
			circulo_lleno(p.getX(), p.getY(), RADIO);
		}
	refresca();
	// agrego 1 particula al conjunto
	Particula nueva;
	nueva.setColor(v[rand()%7]);
	otro.AgregaParticula(nueva);
	espera(20);
	}

	vcierra();
	return 0;
	}

