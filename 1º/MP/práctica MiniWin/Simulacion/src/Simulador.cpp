#include "particula.h"
#include "Nubeparticula.h"
#include "Simulador.h"
#include "miniwin.h"
#include <iostream>

using namespace std;

using namespace miniwin;

		Simulador::Simulador(int n, int a_x, int a_y):mi_nube(n), ancho(a_x), alto(a_y), avion(0,0,10,10){		
			nro_p=n;
			vredimensiona(ancho, alto);
			
		}

		void Simulador::Mover(int const &t_){
				nro_p=mi_nube.GetCapacidad();
				mi_nube.MueveParticulas(ancho, alto, nro_p);			
				avion.mueve_avion(800, 600, t_);
		}

		void Simulador::MoverBala(Particula & balita){
				balita.mueve_bala();
		}

		void Simulador::Pintar(){
			borra();
			Particula p;
			for(int i=0;i<nro_p; i++){
				p = mi_nube.ObtieneParticula(i);
				color(p.getColor());
				circulo_lleno(p.getX(), p.getY(), RADIO);
			}
			avion.pinta_avion();
			refresca();
		}

		void Simulador::PintarBala(Particula balita){
			balita.pinta_bala();
		}

		Particula Simulador::getAvioneta(){
			return avion;
		}
	
		int Simulador::GetCapacity()const{
			return mi_nube.GetCapacidad();
		}

		Particula Simulador::Getit(int contador){
			return mi_nube.ObtieneParticula(contador);
		}

		void Simulador::colisionador(Particula uno, Particula dos, int conti){
				if(uno.umbral(dos)){			// separar
						mi_nube.BorraParticula(conti);
				}
		}

		void Simulador::menu(){
			texto(200, 300, "DALE AL ESPACIO PARA EJECUTAR...");
			texto(200, 400, "TIENES QUE ELIMINAR LAS PELOTAS PULSANDO ESPACIO");
			texto(200, 450, "TE MUEVES CON LAS FLECHAS");
			texto(200, 500, "SI TE CHOCAS EN LOS MUROS TE QUEDAS PEGADO");
		}
		void Simulador::menu2(){
		cout<<"\n░░░░░░░░░▄░░░░░░░░░░░░░░▄░░░░\n░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌░░░\n░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐░░░\n░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐░░░\n░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐░░░\n░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌░░░\n░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌░░\n░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐░░\n░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌░\n░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌░\n▀▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐░\n▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌\n▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐░\n░▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌░\n░▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐░░\n░░▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌░░\n░░░░▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀░░░\n░░░░░░▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀░░░░░\n░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▀▀░░░░░░░░\n";
		}
