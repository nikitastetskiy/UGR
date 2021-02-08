#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado {
  int fila;
  int columna;
  int orientacion;
  bool bikini = false;
  bool zapatillas = false;
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      bateria.fila = -1;
      bateria.columna = -1;
      bateria.orientacion = -1;
      bateria2.fila = -1;
      bateria2.columna = -1;
      bateria2.orientacion = -1;
      hayplan=false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      bateria.fila = -1;
      bateria.columna = -1;
      bateria.orientacion = -1;
      bateria2.fila = -1;
      bateria2.columna = -1;
      bateria2.orientacion = -1;
      hayplan=false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    int cont=0, contAux=0;
    int numAux=0;
    estado actual, destino, bateria, bateria2;
    list<Action> plan;
    bool hayplan, zapatillas=false, bikini=false, cargandoBateria=false, rutaBateria=false;

    Action ultimaAccion;
    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Uniforme(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Reto(const estado &origen, const estado &destino, list<Action> &plan);
    int rutaCoste(const estado &origen, const estado &destino);
    int rutaCosteG(const estado &origen, const estado &destino);

    int DistanciaAbsoluta(const estado &st1, const estado &st2);
    void guardarVisitado(Sensores sensores);
    int CalcularCoste(estado st, bool zapatillas, bool bikini);
    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);
    void ponerMuro(Sensores sensores);

};

#endif
