#include<iostream>
#include <cmath>
#include "miniwin.h"
#include "definiciones.h"
#include "particula.h"
#include "Nubeparticula.h"
#include <stdlib.h>
#ifndef _SIMULADOR_H_
#define _SIMULADOR_H_

using namespace miniwin;

class Simulador{

	private:
		NubeParticulas mi_nube;				// un conjunto de particulas
		int nro_p;						// capacidad
		int ancho, alto;					// la ventana
		
	public:
		Simulador(int n, int a_x, int a_y);
		void Mover();	
		void Pintar();
		~Simulador();

};
#endif
