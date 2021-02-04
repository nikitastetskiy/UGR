#include <iostream>
#include "miniwin.h"
#include "particula.h"
#include "Nubeparticula.h"
#include "Simulador.h"

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
	
	int ancho=800, alto=600, particulas=23, i=0, t = tecla(), capp=0, tamano=20;
	bool tr=0;

	Particula p;
	
		Particula balas[tamano];
		for(int i=0;i<tamano; i++){
			balas[i].setDY();
		}
		srand(time(0));

		Simulador gestor(particulas, ancho, alto);

		while(t != ESPACIO){
			gestor.menu();
			t = tecla();
			espera(100);
		}
		
		borra();
		refresca();
		t = tecla();
		while(gestor.GetCapacity()!=0){
			
			gestor.Mover(t);
			gestor.Pintar();

			if(t == ESPACIO){
					tr=1;
					balas[capp].setY(gestor.getAvioneta());
					balas[capp].setX(gestor.getAvioneta());
					capp++;
			}

			if(tr){
				for(int i=0; i<capp; i++){
					gestor.MoverBala(balas[i]);
					gestor.PintarBala(balas[i]);
					for(int j=0; j<gestor.GetCapacity();j++){
						p=gestor.Getit(j);
						gestor.colisionador(balas[i], p, j);
					}
				}
			}
			espera(20);
			if(capp==tamano){
				capp=0;
			}
			t = tecla();
		}
		borra();
		texto(200, 300, "FELICIDADES HAS GANADO  !! :D !!");
		refresca();
		gestor.menu2();
		espera(10000);
		vcierra();
		return 0;
}
