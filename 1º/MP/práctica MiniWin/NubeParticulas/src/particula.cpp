#include <cmath>
#include "particula.h"
#include "miniwin.h"
#include "definiciones.h"
#include <iostream>

using namespace miniwin;

Particula::Particula(){
			int randoms=rand();
			Color colores[7]={AZUL, BLANCO, MAGENTA, CYAN, ROJO, VERDE, AMARILLO};
			x = randoms%(MIN_X + 1);
			y = randoms%(MIN_Y + 1);
			c = colores[rand()%7];
			dx = randoms%5 + 1;		
			dy = randoms%5 + 1;
		}

		void Particula::pinta_pelota() {
			color(c);
			circulo_lleno(x, y, RADIO);
		}

		float Particula::getX()const{
			return x;
		}

		float Particula::getY()const{
			return y;
		}

		Color Particula::getColor()const{
			return c;
		}

		Color Particula::setColor(Color color_){
			c= color_;
		}

		float Particula::getDX()const{
			return dx;
		}

		float Particula::getDY()const{
			return dy;
		}

		void Particula::mueve_pelota(int ancho, int alto) {
			float pum=0.20;
			const float factor = 0.97;
			x += dx;
			y += dy;
			if (x > ancho - RADIO){
				dx = -dx * factor;
				x= ancho - RADIO;
				pum=-0.15;
			}
			else if (x < RADIO){
				dx = -dx * factor;
				x= RADIO;
				pum=-0.15;
			}
			else if (y > alto - RADIO){
				dy= -dy * factor;
				y = alto - RADIO;
				pum=-0.25;
			}
			else if (y < RADIO){
				dy= -dy * factor;
				y = RADIO;
				pum=-0.25;
			}
			
		}

		bool Particula::umbral(const Particula &p_){
			float distancia;
			distancia= sqrt((x-p_.x)*(x-p_.x)+(y-p_.y)*(y-p_.y));		//Calcula la distancia entre dos particulas
			return(distancia<UMBRAL);
		}

		void Particula::colision(Particula &po) {
			float v_aux=dx;
			
			dx=po.dx;
			po.dx=v_aux;
		}

