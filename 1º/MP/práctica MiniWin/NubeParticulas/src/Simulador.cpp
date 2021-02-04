#include "particula.h"
#include "Nubeparticula.h"
#include "Simulador.h"
#include "miniwin.h"

using namespace miniwin;

		Simulador::Simulador(int n, int a_x, int a_y):mi_nube(n){
			nro_p=n;
			ancho=a_x;
			alto=a_y;
			vredimensiona(ancho, alto);
		}

		void Simulador::Mover(){
			
				mi_nube.Mover1(ancho, alto);

		}

		void Simulador::Pintar(){
			borra();
			Particula p;
			for(int i=0;i<nro_p; i++){
				p = mi_nube.ObtieneParticula(i);
				color(p.getColor());
				circulo_lleno(p.getX(), p.getY(), RADIO);
			}
			refresca();
		}

		Simulador::~Simulador(){
			vcierra();
		}
