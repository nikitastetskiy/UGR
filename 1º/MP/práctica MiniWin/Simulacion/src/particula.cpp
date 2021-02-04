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
			dx = randoms%8 + 1;		
			dy = randoms%8 + 1;
		}

		Particula::Particula(float dy_){
			c= BLANCO;
			x = 0;
			y = 0;
			dx = 0;		
			dy = dy_;
		}

		Particula::Particula(int izq_,int arr_,int der_,int aba_){
			c= CYAN;
			izq=izq_;
			arr=arr_;
			der=der_;
			aba=aba_;
			x=400;
			y=300;
			dx=5;
			dy=5;
		}

		void Particula::pinta_pelota() {
			color(c);
			circulo_lleno(x, y, RADIO);
		}

		void Particula::pinta_bala() {
			color(BLANCO);
			circulo_lleno(x, y, 5);
		}

		void Particula::pinta_avion() {
			color(BLANCO);
			rectangulo(x-izq, y-arr, x+der, y+aba);
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

		void Particula::mueve_pelota(int ancho, int alto) {
			float pum=0.2;
			const float factor = 0.97;
			x += dx;
			y += dy;
			if (x > ancho - RADIO){
				dx = -dx * factor;
				x= ancho - RADIO;
				pum=-0.2;
			}
			else if (x < RADIO){
				dx = -dx * factor;
				x= RADIO;
				pum=-0.2;
			}
			else if (y > alto - RADIO){
				dy= -dy * factor;
				y = alto - RADIO;
				pum=-0.4;
			}
			else if (y < RADIO){
				dy= -dy * factor;
				y = RADIO;
				pum=-0.4;
			}
			dy= dy + pum;
		}

		void Particula::mueve_bala(){
			y -= dy;
		}

		void Particula::mueve_avion(int ancho, int alto, int t){
		if(((x>0 and x<ancho-11) and (y>0 and y<alto-11))){
			if(t == NINGUNA){
				t=dt;
			}

			if(t == IZQUIERDA){
				x -= dx;
				dt=t;
			}
			if(t == DERECHA){
				x += dx;
				dt=t;
			}
			if(t == ARRIBA){
				y -= dy;
				dt=t;
			}
			if(t == ABAJO){
				y += dy;
				dt=t;
			}
		}
		}

		bool Particula::umbral(Particula p_)const{
			float distancia;
			distancia= sqrt((x-p_.x)*(x-p_.x)+(y-p_.y)*(y-p_.y));		//Calcula la distancia entre dos particulas
			return(distancia<UMBRAL);
		}

		void Particula::colision(Particula &po){
			float v_aux=dx;
			
			dx=po.dx;
			po.dx=v_aux;
		}

		void Particula::setY(Particula avioneta){
			y=avioneta.getY();
		}

		void Particula::setX(Particula avioneta){
			x=avioneta.getX() + 5;
		}

		void Particula::setDY(){
			dy=10;
		}

		float Particula::getDX()const{
			return dx;
		}

		float Particula::getDY()const{
			return dy;
		}
