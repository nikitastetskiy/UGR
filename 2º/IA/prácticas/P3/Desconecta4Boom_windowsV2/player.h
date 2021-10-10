#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player{
    public:
      	Player(int jug);
     	Environment::ActionType Think();
     	void Perceive(const Environment &env);


	  	double Valoracion(const Environment &estado, int jugador);

	  	//Metodos propios de la practica ->

	 	double Poda_AlfaBeta(Environment entorno , int profundidad ,int &accion, double alpha , double beta );
		double ValoracionTest2(const Environment &estado, int jugador);
		double Heuristica(const Environment &estado ,int fila, int columna);

    private:
      int jugador_;
      Environment actual_;
};
#endif
