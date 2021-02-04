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
		int utiles;			// posiciones ocupadas
		

	public:
		NubeParticulas(int cap);
		void BorraParticula(int contador);
		Particula ObtieneParticula(int contador)const;
		void MueveParticulas(int ancho, int alto, int cap);
		~NubeParticulas();
		int GetCapacidad()const;
};
#endif
