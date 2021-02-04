#include<iostream>
#include <cmath>
#include "miniwin.h"
#include "definiciones.h"
#include "particula.h"
#include <stdlib.h>
#ifndef _NUBEPARTICULA_H_
#define _NUBEPARTICULA_H_

using namespace miniwin;

class NubeParticulas{

	private:
		Particula *nube; 	// array de particulas
		int capacidad;		// capacidad del array
		int utiles;		// posiciones ocupadas

	public:

		NubeParticulas();
		NubeParticulas(int cap);
		NubeParticulas(const NubeParticulas &p);
		void AgregaParticula(Particula p_);
		void BorraParticula(Particula *&vector, int contador);
		Particula ObtieneParticula(int contador)const;
		int GetCapacidad()const;
		int GetCardinal()const;
		void Mover1(int ancho, int alto);
		~NubeParticulas();
		NubeParticulas& operator=(const NubeParticulas &p);

};
#endif
