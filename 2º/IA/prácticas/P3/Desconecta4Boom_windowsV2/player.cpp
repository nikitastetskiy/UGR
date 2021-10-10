#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

double Player::Heuristica(const Environment &estado ,int fil, int col){

     // 4 FILA
   if ((col<4 && estado.See_Casilla(fil,col)) && (estado.See_Casilla(fil,col+2)) == (estado.See_Casilla(fil,col+3))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil,col+1))
   && (estado.See_Casilla(fil,col+1)) == (estado.See_Casilla(fil,col+2)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -999999.0 : 999999.0);
   }

   // 4 COLUMNA
   if ((fil<4) && (estado.See_Casilla(fil+2,col)) == (estado.See_Casilla(fil+3,col))
   && (estado.See_Casilla(fil+1,col)) == (estado.See_Casilla(fil+2,col))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil+1,col)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -999999.0 : 999999.0);
   }

   // 4 DIAGONAL
   if ((fil<4 && col<4) && (estado.See_Casilla(fil+2,col+2)) == (estado.See_Casilla(fil+3,col+3))
   && (estado.See_Casilla(fil+1,col+1)) == (estado.See_Casilla(fil+2,col+2))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil+1,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -999999.0 : 999999.0);
   }

   if ((fil>2 && col<4) && (estado.See_Casilla(fil-2,col+2)) == (estado.See_Casilla(fil-3,col+3))
   && (estado.See_Casilla(fil-1,col+1)) == (estado.See_Casilla(fil-2,col+2))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil-1,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -999999.0 : 999999.0);
   }

   // 3 FILA
   if ((col<5 && estado.See_Casilla(fil,col) ) && (
   (estado.See_Casilla(fil,col+1)) == (estado.See_Casilla(fil,col+2)) &&
   (estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -99.0 : 99.0);
   }

   // 3 COLUMNA
   if ((fil<5) && (estado.See_Casilla(fil+1,col)) == (estado.See_Casilla(fil+2,col))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil+1,col)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -99.0 : 99.0);
   }

   // 3 DIAGONAL
   if ((fil>1 && col<5) && (estado.See_Casilla(fil-1,col+1)) == (estado.See_Casilla(fil-2,col+2))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil-1,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -99.0 : 99.0);
   }

   if ((fil<5 && col<5) && (estado.See_Casilla(fil+1,col+1)) == (estado.See_Casilla(fil+2,col+2))
   && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil+1,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -99.0 : 99.0);
   }

   // 2 FILA
   if ((col<6 && estado.See_Casilla(fil,col)) &&
   ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -9.0 : 9.0);
   }

   // 2 COLUMNA
   if ((fil<6) && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil+1,col)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -9.0 : 9.0);
   }

   // 2 DIAGONAL
   if ((fil>0 and col<6) && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil-1,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -9.0 : 9.0);
   }

   if ((fil<6 and col<6) && ((estado.See_Casilla(fil,col)) == (estado.See_Casilla(fil+1,col+1)))){

      return((estado.See_Casilla(fil,col) == jugador_) ? -9.0 : 9.0);
   }

   return 0.0;

}

double Player::Poda_AlfaBeta(Environment entorno , int prof ,int &acc, double alpha , double beta ){

   if(prof == 0 || entorno.JuegoTerminado()) {

		if(entorno.JuegoTerminado()){
			return ValoracionTest(entorno,jugador_);
		}
		return ValoracionTest2(entorno,jugador_);

	}

   Environment e_n ;
	double bestNodo;
	int aux = -1;
	e_n = entorno.GenerateNextMove(aux);

   if(entorno.JugadorActivo() != jugador_ ){

		bestNodo = beta;

		while(aux<8){
			int otra = aux;

			double nodoHijo = Poda_AlfaBeta(e_n , prof -1 ,otra, alpha , bestNodo);

			if(nodoHijo < bestNodo && aux != -1 && prof == 8){
				acc = aux;
			}

			bestNodo = min( bestNodo , nodoHijo);
            if (bestNodo <= alpha) {
                break;
            }
			e_n = entorno.GenerateNextMove(aux);

		}

	}else{

		bestNodo = alpha;

		while(aux<8){
			int otra = aux;

			double nodoHijo = Poda_AlfaBeta(e_n , prof -1 ,otra, bestNodo , beta);

			if(nodoHijo > bestNodo && aux != -1 && prof == 8){
				acc = aux;
			}

			bestNodo = max( bestNodo , nodoHijo);

			if (beta <= bestNodo) {
                break;
            }
			e_n = entorno.GenerateNextMove(aux);
		}
	}
   return bestNodo;
}



double Player::ValoracionTest2(const Environment &estado, int jugador){

int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else{

		double suma = Heuristica(estado,0,0);
		int j = 0;

		for (int i=0; i<7; i++)
	      for (int j=0; j<7; j++){

	      	if(jugador != jugador_){
                if (estado.See_Casilla(i,j)!=0 && suma < Heuristica(estado,i,j) )
	             suma = Heuristica(estado,i,j);

	      	}else{
                if (estado.See_Casilla(i,j)!=0 && suma > Heuristica(estado,i,j) )
                 suma = Heuristica(estado,i,j);
	      	}
	      }

    	return suma;
    }


}

// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
   return Puntuacion(jugador, estado);
}


// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}

// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8];


    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = -10000000000000.0, beta= 10000000000000.0; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;

    int accionAuxiliar = -1;
    valor = Poda_AlfaBeta(actual_, 8, accionAuxiliar, menosinf, masinf);

   cout << accionAuxiliar;

	switch (accionAuxiliar)
	{
	case 0: return Environment::PUT1;
	case 1: return Environment::PUT2;
	case 2: return Environment::PUT3;
	case 3: return Environment::PUT4;
	case 4: return Environment::PUT5;
	case 5: return Environment::PUT6;
	case 6: return Environment::PUT7;
	case 7: return Environment::BOOM;

	}

    return accion;
}

