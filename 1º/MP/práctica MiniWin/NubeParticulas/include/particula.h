#include<iostream>
#include <cmath>
#include "miniwin.h"
#include "definiciones.h"
#include <stdlib.h>
#ifndef _PARTICULA_H_
#define _PARTICULA_H_

using namespace miniwin;

class Particula{

	private:
	float x, y;
	float dx, dy;
	Color c;

	public:

		Particula();
		void pinta_pelota();
		float getX()const;
		float getY()const;
		Color getColor()const;
		Color setColor(Color color_);
		float getDX()const;
		float getDY()const;
		void mueve_pelota(int ancho, int alto);
		bool umbral(const Particula &p_);
		void colision(Particula &po);

};

#endif
