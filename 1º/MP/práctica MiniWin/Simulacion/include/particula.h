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

	int izq, arr, der, aba, dt;

	public:

		Particula();

		Particula(float dy_);
		Particula(int izq_,int arr_,int der_,int aba_);
		void pinta_pelota();
		void pinta_bala();
		void pinta_avion();
		float getX()const;
		float getY()const;
		Color getColor()const;
		void mueve_pelota(int ancho, int alto);
		void mueve_bala();
		void mueve_avion(int ancho, int alto, int t);
		bool umbral(Particula p_)const;
		void colision(Particula &po);
		void setY(Particula avioneta);
		void setX(Particula avioneta);
		void setDY();
		float getDX()const;
		float getDY()const;
};

#endif
