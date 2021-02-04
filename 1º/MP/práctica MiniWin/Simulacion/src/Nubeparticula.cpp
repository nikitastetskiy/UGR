#include "particula.h"
#include "Nubeparticula.h"
#include "miniwin.h"

using namespace miniwin;

		NubeParticulas::NubeParticulas(int cap){
			nube=new Particula[cap];
			capacidad=cap;
		}

		void NubeParticulas::BorraParticula(int contador){
			Particula *v_ampliado;
			capacidad--;
			//v_ampliado = new Particula [capacidad];

			for(int i=contador; i<capacidad;i++){
				nube[i] = nube[i+1];
			}
			//delete []nube;
			//nube=v_ampliado;
		}

		Particula NubeParticulas::ObtieneParticula(int contador)const{
			return nube[contador];
		}

		void NubeParticulas::MueveParticulas(int ancho, int alto, int cap){
			for(int i=0;i<cap;i++){
				nube[i].mueve_pelota(ancho, alto);
				for(int j=0;j<cap;j++){
					if(nube[i].umbral(nube[j]) and i != j){			// separar
						nube[i].colision(nube[j]);
					}
				}
			}		
		}

		NubeParticulas::~NubeParticulas(){
			if(nube != 0){
				delete [] nube;
			}
		}

		int NubeParticulas::GetCapacidad()const{
			return capacidad;
		}
