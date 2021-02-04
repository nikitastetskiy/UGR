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
		int nro_p;							// capacidad
		int ancho, alto;					// la ventanacapac
		Particula avion;
		
	public:
		Simulador(int n, int a_x, int a_y);
		void Mover(int const &t_);
		void MoverBala(Particula & balita);
		void Pintar();
		void PintarBala(Particula balita);
		Particula getAvioneta();
		int GetCapacity()const;
		Particula Getit(int contador);
		void colisionador(Particula uno, Particula dos, int conti);
		void menu();
		void menu2();

};
#endif
