#include "particula.h"
#include "Nubeparticula.h"
#include "miniwin.h"

using namespace miniwin;

		NubeParticulas::NubeParticulas(){
			capacidad=5;
			utiles=5;
			nube=new Particula[capacidad];
		}		

		NubeParticulas::NubeParticulas(int cap){
			nube=new Particula[cap];
			capacidad=cap;
			utiles=cap;
		}

		NubeParticulas::NubeParticulas(const NubeParticulas &p){
			capacidad=p.GetCapacidad();			
			utiles=p.GetCardinal();				
			nube= new Particula[p.GetCapacidad()];

			for(int i=0; i<capacidad;i++){
				nube[i]=p.nube[i];
			}
		}

		void NubeParticulas::AgregaParticula(Particula p_){
			if(capacidad==utiles){
				Particula *v_ampliado=0;
				capacidad++;
				v_ampliado = new Particula [capacidad];
				for(int i=0; i<utiles;i++){
					v_ampliado[i] = nube[i];
				}
				delete [] nube;
				nube=v_ampliado;
			}
			nube[utiles]=p_;
			utiles++;
		}

		void NubeParticulas::BorraParticula(Particula *&vector, int contador){
			capacidad--;
			for(int i=contador; i<capacidad;i++){
				nube[i] = nube[i+1];
			}
		}

		Particula NubeParticulas::ObtieneParticula(int contador)const{
			return nube[contador];
		}

		int NubeParticulas::GetCapacidad()const{
			return capacidad;
		}

		int NubeParticulas::GetCardinal()const{
			return utiles;
		}

		void NubeParticulas::Mover1(int ancho, int alto){
			for(int i=0;i<utiles;i++){			
				nube[i].mueve_pelota(ancho, alto);
			}
		}

		NubeParticulas::~NubeParticulas(){
			if(nube != 0){
				delete [] nube;
			}
		}

		NubeParticulas& NubeParticulas::operator=(const NubeParticulas &p){
			if(&p!=this){				
				delete []  this->nube;
				this->capacidad=p.GetCapacidad();
				this->utiles=p.GetCardinal();
				this->nube=new Particula[this->capacidad];
				for(int i=0; i<utiles;i++){
					this->nube[i]=p.ObtieneParticula(i);
				}
			}
			return *this;
		}
