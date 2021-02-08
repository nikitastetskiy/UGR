#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>

// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	// Estoy en el nivel 1

    //unsigned char contenidoCasilla;

    // Mirar si se ha cambiado el destino

    if (destino.fila != sensores.destinoF or destino.columna != sensores.destinoC){
        hayplan = false;
    }

    // Calcular camino hasta el destino

    //auto start = chrono::steady_clock::now();

    if(sensores.nivel != 4){
        if(!hayplan){
            actual.fila = sensores.posF;
            actual.columna = sensores.posC;
            actual.orientacion = sensores.sentido;
            destino.fila = sensores.destinoF;
            destino.columna = sensores.destinoC;
            hayplan = pathFinding(sensores.nivel, actual, destino, plan);
        }
    }


    //auto end = chrono::steady_clock::now();

    //cout << "Elapsed time in milliseconds : "
	//	<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
	//	<< " ms" << endl;

    Action sigAccion;

    if(sensores.nivel == 4){
        guardarVisitado(sensores);

        actual.fila = sensores.posF;
        actual.columna = sensores.posC;
        actual.orientacion = sensores.sentido;

        if (hayplan and plan.size()>0 and (sensores.terreno[2]=='P' or
            sensores.terreno[2]=='M') and plan.front() == actFORWARD){
            hayplan = false;
            rutaBateria == false;
        }

        if(hayplan and plan.size()>0 && (sensores.terreno[2] == 'A' and plan.front() == actFORWARD) && (sensores.terreno[0] != 'A' || sensores.terreno[1] != 'A' || sensores.terreno[3] != 'A' || sensores.terreno[5] != 'A' || sensores.terreno[6] != 'A' || sensores.terreno[7] != 'A')){
            if(rutaBateria)
                rutaBateria = false;
            else
                hayplan = false;
           }

        if(hayplan and plan.size()>0 && (sensores.terreno[2] == 'B' and plan.front() == actFORWARD) && (sensores.terreno[0] != 'B' || sensores.terreno[1] != 'B' || sensores.terreno[3] != 'B' || sensores.terreno[5] != 'B' || sensores.terreno[6] != 'B' || sensores.terreno[7] != 'B')){
            if(rutaBateria)
                rutaBateria = false;
            else
                hayplan = false;
           }
        else
            contAux++;

        if(cont%4==0 && rutaBateria==false && DistanciaAbsoluta(actual, bateria)<20 && sensores.bateria < (3000-cont) && bateria.columna != -1 &&
        sensores.bateria>rutaCosteG(actual, bateria)+50 && (DistanciaAbsoluta(actual, bateria)<4 || rutaCoste(bateria,destino) < rutaCoste(actual,destino))
           ){
            hayplan = pathFinding(sensores.nivel, actual, bateria, plan);
            cargandoBateria = true;
            rutaBateria = true;
        }

        if(cont%4==0 && bateria2.columna != -1 && rutaBateria==false && DistanciaAbsoluta(actual, bateria2)<20 && sensores.bateria < (3000-cont) &&
        sensores.bateria>rutaCosteG(actual, bateria2)+50 && (DistanciaAbsoluta(actual, bateria2)<4 || rutaCoste(bateria2,destino) < rutaCoste(actual,destino)) && rutaCoste(actual, bateria2)<= rutaCoste(actual, bateria)
           ){
            hayplan = pathFinding(sensores.nivel, actual, bateria2, plan);
            cargandoBateria = true;
            rutaBateria = true;
        }
        //else if(cargandoBateria) { hayplan=false; cargandoBateria=false; }

        if(cont%4==0 && rutaBateria==false && bateria.columna != -1 && sensores.bateria < (3000-cont-50) && sensores.bateria<rutaCosteG(actual, bateria)+rutaCosteG(bateria, destino)//rutaCosteG(bateria, destino) //
           ){
            hayplan = pathFinding(sensores.nivel, actual, bateria, plan);
            cargandoBateria = true;
            rutaBateria = true;
        }

        if(cont%4==0 && bateria2.columna != -1 && rutaBateria==false && sensores.bateria < (3000-cont-50) && sensores.bateria<rutaCosteG(actual, bateria2)+rutaCosteG(bateria2, destino)//rutaCosteG(bateria2, destino) //     && sensores.bateria<rutaCosteG(actual, bateria2)+100
           ){
            if(rutaCoste(actual, bateria2)<= rutaCoste(actual, bateria)){
                hayplan = pathFinding(sensores.nivel, actual, bateria2, plan);
                cargandoBateria = true;
                rutaBateria = true;
            }
        }

        if(!bikini && sensores.terreno[0]=='K')
            bikini = true;

        if(!zapatillas && sensores.terreno[0]=='D')
            zapatillas = true;

        if(!hayplan){
            destino.fila = sensores.destinoF;
            destino.columna = sensores.destinoC;
            hayplan = pathFinding(sensores.nivel, actual, destino, plan);
        }

        if(cont<3){
            sigAccion = actTURN_R;
            hayplan = false;
        }

        numAux = (3000-cont+(3000-cont)*3/4);
        if(numAux>2990)
            numAux=2990;

        if (hayplan and plan.size()>0 && sensores.superficie[2]=='a' and plan.front() == actFORWARD){
            if(cont%2==0){
                ponerMuro(sensores);
                if(rutaBateria){
                    if(bateria.columna != -1)
                        hayplan = pathFinding(sensores.nivel, actual, bateria, plan);
                    if(bateria2.columna != -1 && rutaCoste(actual, bateria2)<= rutaCoste(actual, bateria))
                        hayplan = pathFinding(sensores.nivel, actual, bateria2, plan);
                }
                else
                    hayplan = pathFinding(sensores.nivel, actual, destino, plan);
                guardarVisitado(sensores);
            }
            else
                sigAccion = actIDLE;
        }

        if(sensores.bateria <= numAux && cargandoBateria && ((sensores.posC == bateria.columna && sensores.posF == bateria.fila) || (sensores.posC == bateria2.columna && sensores.posF == bateria2.fila))){
            sigAccion = actIDLE;
            //hayplan = false;
        }
        if(sensores.bateria >= numAux && cargandoBateria && ((sensores.posC == bateria.columna && sensores.posF == bateria.fila) || (sensores.posC == bateria2.columna && sensores.posF == bateria2.fila))){
            hayplan = false;
            cargandoBateria = false;
            rutaBateria = false;
        }
    }

    if(hayplan and plan.size()>0){ // Hay un plan no vacio
        sigAccion = plan.front(); // tomamos la siguiente accion del hayplan
        plan.erase(plan.begin()); // eliminamos la accion de la lista de acciones
    }

	cont++;

    return sigAccion;
}


// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
						return pathFinding_Uniforme(origen,destino,plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
                        //return pathFinding_Uniforme(origen,destino,plan);
						return pathFinding_Reto(origen,destino,plan);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}

struct nodo0{
	estado st;
	list<Action> secuencia;
};

struct nodo1{
	estado st;
	list<Action> secuencia;
};

struct nodo2{
	estado st;
	int coste;
	bool zapatillas;
	bool bikini;
	list<Action> secuencia;
};

struct nodo3{
	estado st;
	int costeG, costeH, costeF;
	bool zapatillas;
	bool bikini;
	list<Action> secuencia;
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};

struct ComparaEstadosAbsoluto{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion) or
        (a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion && a.bikini > n.bikini) or
      (a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion && a.bikini == n.bikini && a.zapatillas > n.zapatillas))
			return true;
		else
			return false;
	}
};


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo0> pila;											// Lista de Abiertos

  nodo0 current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo0 hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo0 hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo0 hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue<nodo1> cola;											// Lista de Abiertos

  nodo1 current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo1 hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo1 hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo1 hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.front();
            while(generados.find(current.st) != generados.end()  && !cola.empty()){
                cola.pop();
                current = cola.front();
            }
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

struct CompararCoste{
    bool operator()(const nodo2& lhs, const nodo2& rhs){
        return lhs.coste>rhs.coste;
    }
};

int ComportamientoJugador::CalcularCoste(estado st, bool zapatillass, bool bikinii){
    int cos = 1, z=0, b=0, zx=2, bx=2;

    if(zapatillass){
        z=45;
        zx=0;
    }
    if(bikinii){
        b=90;
        bx=0;
    }

    switch (mapaResultado[st.fila][st.columna]){
        case 'A' : cos = 100-b; break;
        case 'B' : cos = 50-z; break;
        case 'T' : cos = 2; break;
        case '?' : cos = 4; break;
        case 'K' : cos = 1-bx; break;
        case 'D' : cos = 1-zx; break;
        case 'X' :
            if(bateria.fila == -1){
                bateria.bikini = bikini;
                bateria.zapatillas = zapatillas;
                bateria.columna = st.columna;
                bateria.fila = st.fila;
                bateria.orientacion = st.orientacion;
            }
            if(bateria2.fila == -1 && bateria.fila != st.fila){
                bateria2.bikini = bikini;
                bateria2.zapatillas = zapatillas;
                bateria2.columna = st.columna;
                bateria2.fila = st.fila;
                bateria2.orientacion = st.orientacion;
            }
            cos = 0;
            break;
    }
    return cos;
}

bool ComportamientoJugador::pathFinding_Uniforme(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstadosAbsoluto> generados; // Lista de Cerrados
	priority_queue<nodo2, vector<nodo2>, CompararCoste> cola;											// Lista de Abiertos

  nodo2 current;
	current.st = origen;
	current.secuencia.empty();
	current.coste = 0;
	current.bikini = bikini;
	current.zapatillas = zapatillas;

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();

        if(mapaResultado[current.st.fila][current.st.columna] == 'K'){
            current.bikini = true;
            current.st.bikini = true;
        }

        if(mapaResultado[current.st.fila][current.st.columna] == 'D'){
            current.zapatillas = true;
            current.st.zapatillas = true;
        }

		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo2 hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
            hijoTurnR.coste+=CalcularCoste(current.st, current.zapatillas, current.bikini);
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);
		}

		// Generar descendiente de girar a la izquierda
		nodo2 hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.coste+=CalcularCoste(current.st, current.zapatillas, current.bikini);
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo2 hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
                hijoForward.coste+=CalcularCoste(current.st, current.zapatillas, current.bikini);
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
            while(generados.find(current.st) != generados.end() && !cola.empty()){
                cola.pop();
                current = cola.top();
            }
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		cout << "Coste del plan: " << current.coste << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

struct CompararCosteAbsoluto{
    bool operator()(const nodo3& lhs, const nodo3& rhs){
        return (lhs.costeF > rhs.costeF) || (lhs.costeF == rhs.costeF && lhs.costeH > rhs.costeH);
    }
};

int ComportamientoJugador::DistanciaAbsoluta(const estado &st1, const estado &st2){
    int distancia = abs(st1.fila - st2.fila) + abs(st1.columna - st2.columna);
    return distancia;
}

// Voy a utilizar el algoritmo A * (estrella)
bool ComportamientoJugador::pathFinding_Reto(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstadosAbsoluto> generados; // Lista de Cerrados
	priority_queue<nodo3, vector<nodo3>, CompararCosteAbsoluto> cola;											// Lista de Abiertos

	int costeG, costeH;

  nodo3 current;
	current.st = origen;
	current.secuencia.empty();
	current.costeG = 0;
	current.costeH = 0;
	current.costeF = 0;
	current.bikini = bikini;
	current.zapatillas = zapatillas;

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();

        if(mapaResultado[current.st.fila][current.st.columna] == 'K'){
            current.bikini = true;
            current.st.bikini = true;
        }

        if(mapaResultado[current.st.fila][current.st.columna] == 'D'){
            current.zapatillas = true;
            current.st.zapatillas = true;
        }

		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo3 hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
            hijoTurnR.costeH+=DistanciaAbsoluta(hijoTurnR.st, current.st);
            hijoTurnR.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
            hijoTurnR.costeF+=hijoTurnR.costeH + hijoTurnR.costeG;
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);
		}

		// Generar descendiente de girar a la izquierda
		nodo3 hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.costeH+=DistanciaAbsoluta(hijoTurnL.st, current.st);
            hijoTurnL.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
            hijoTurnL.costeF+=hijoTurnL.costeH + hijoTurnL.costeG;
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo3 hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
                hijoForward.costeH+=DistanciaAbsoluta(hijoForward.st, current.st);
                hijoForward.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
                hijoForward.costeF+=hijoForward.costeH + hijoForward.costeG;
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
            while(generados.find(current.st) != generados.end() && !cola.empty()){
                cola.pop();
                current = cola.top();
            }
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		//cout << "Coste del plan (G): " << current.costeG << endl;
		//cout << "Coste del plan (H): " << current.costeH << endl;
		//cout << "Coste del plan (F): " << current.costeF << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

int ComportamientoJugador::rutaCoste(const estado &origen, const estado &destino) {
	set<estado,ComparaEstadosAbsoluto> generados; // Lista de Cerrados
	priority_queue<nodo3, vector<nodo3>, CompararCosteAbsoluto> cola;											// Lista de Abiertos

	int costeG, costeH;

  nodo3 current;
	current.st = origen;
	current.secuencia.empty();
	current.costeG = 0;
	current.costeH = 0;
	current.costeF = 0;
	current.bikini = bikini;
	current.zapatillas = zapatillas;

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();

        if(mapaResultado[current.st.fila][current.st.columna] == 'K'){
            current.bikini = true;
            current.st.bikini = true;
        }

        if(mapaResultado[current.st.fila][current.st.columna] == 'D'){
            current.zapatillas = true;
            current.st.zapatillas = true;
        }

		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo3 hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
            hijoTurnR.costeH+=DistanciaAbsoluta(hijoTurnR.st, current.st);
            hijoTurnR.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
            hijoTurnR.costeF+=hijoTurnR.costeH + hijoTurnR.costeG;
			cola.push(hijoTurnR);
		}

		// Generar descendiente de girar a la izquierda
		nodo3 hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.costeH+=DistanciaAbsoluta(hijoTurnL.st, current.st);
            hijoTurnL.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
            hijoTurnL.costeF+=hijoTurnL.costeH + hijoTurnL.costeG;
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo3 hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
                hijoForward.costeH+=DistanciaAbsoluta(hijoForward.st, current.st);
                hijoForward.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
                hijoForward.costeF+=hijoForward.costeH + hijoForward.costeG;
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
            while(generados.find(current.st) != generados.end() && !cola.empty()){
                cola.pop();
                current = cola.top();
            }
		}
	}

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		return current.costeF;
	}

	return 1000000000000;
}

int ComportamientoJugador::rutaCosteG(const estado &origen, const estado &destino) {
	set<estado,ComparaEstadosAbsoluto> generados; // Lista de Cerrados
	priority_queue<nodo3, vector<nodo3>, CompararCosteAbsoluto> cola;											// Lista de Abiertos

	int costeG, costeH;

  nodo3 current;
	current.st = origen;
	current.secuencia.empty();
	current.costeG = 0;
	current.costeH = 0;
	current.costeF = 0;
	current.bikini = bikini;
	current.zapatillas = zapatillas;

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();

        if(mapaResultado[current.st.fila][current.st.columna] == 'K'){
            current.bikini = true;
            current.st.bikini = true;
        }

        if(mapaResultado[current.st.fila][current.st.columna] == 'D'){
            current.zapatillas = true;
            current.st.zapatillas = true;
        }

		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo3 hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
            hijoTurnR.costeH+=DistanciaAbsoluta(hijoTurnR.st, current.st);
            hijoTurnR.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
            hijoTurnR.costeF+=hijoTurnR.costeH + hijoTurnR.costeG;
			cola.push(hijoTurnR);
		}

		// Generar descendiente de girar a la izquierda
		nodo3 hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.costeH+=DistanciaAbsoluta(hijoTurnL.st, current.st);
            hijoTurnL.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
            hijoTurnL.costeF+=hijoTurnL.costeH + hijoTurnL.costeG;
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo3 hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
                hijoForward.costeH+=DistanciaAbsoluta(hijoForward.st, current.st);
                hijoForward.costeG+=CalcularCoste(current.st, current.zapatillas, current.bikini);
                hijoForward.costeF+=hijoForward.costeH + hijoForward.costeG;
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
            while(generados.find(current.st) != generados.end() && !cola.empty()){
                cola.pop();
                current = cola.top();
            }
		}
	}

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		return current.costeG;
	}

	return 1000000000000;
}

// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

void ComportamientoJugador::ponerMuro(Sensores sensores)
{
    int fil=sensores.posF, col=sensores.posC;

    mapaResultado[fil][col] = sensores.terreno[0];

    switch (sensores.sentido)
    {
    case norte :
        mapaResultado[fil-1][col] = 'M';
        break;
    case este :
        mapaResultado[fil][col+1] = 'M';
        break;

    case sur :
        mapaResultado[fil+1][col] = 'M';
        break;
    case oeste :
        mapaResultado[fil][col-1] = 'M';
        break;
    }
}

void ComportamientoJugador::guardarVisitado(Sensores sensores)
{
    int fil=sensores.posF, col=sensores.posC;

    mapaResultado[fil][col] = sensores.terreno[0];

    switch (sensores.sentido)
    {
    case norte :
        mapaResultado[fil-1][col-1] = sensores.terreno[1];
        mapaResultado[fil-1][col] = sensores.terreno[2];
        mapaResultado[fil-1][col+1] = sensores.terreno[3];

        mapaResultado[fil-2][col-2] = sensores.terreno[4];
        mapaResultado[fil-2][col-1] = sensores.terreno[5];
        mapaResultado[fil-2][col] = sensores.terreno[6];
        mapaResultado[fil-2][col+1] = sensores.terreno[7];
        mapaResultado[fil-2][col+2] = sensores.terreno[8];

        mapaResultado[fil-3][col-3] = sensores.terreno[9];
        mapaResultado[fil-3][col-2] = sensores.terreno[10];
        mapaResultado[fil-3][col-1] = sensores.terreno[11];
        mapaResultado[fil-3][col] = sensores.terreno[12];
        mapaResultado[fil-3][col+1] = sensores.terreno[13];
        mapaResultado[fil-3][col+2] = sensores.terreno[14];
        mapaResultado[fil-3][col+3] = sensores.terreno[15];
        break;
    case este :
        mapaResultado[fil-1][col+1] = sensores.terreno[1];
        mapaResultado[fil][col+1] = sensores.terreno[2];
        mapaResultado[fil+1][col+1] = sensores.terreno[3];

        mapaResultado[fil-2][col+2] = sensores.terreno[4];
        mapaResultado[fil-1][col+2] = sensores.terreno[5];
        mapaResultado[fil][col+2] = sensores.terreno[6];
        mapaResultado[fil+1][col+2] = sensores.terreno[7];
        mapaResultado[fil+2][col+2] = sensores.terreno[8];

        mapaResultado[fil-3][col+3] = sensores.terreno[9];
        mapaResultado[fil-2][col+3] = sensores.terreno[10];
        mapaResultado[fil-1][col+3] = sensores.terreno[11];
        mapaResultado[fil][col+3] = sensores.terreno[12];
        mapaResultado[fil+1][col+3] = sensores.terreno[13];
        mapaResultado[fil+2][col+3] = sensores.terreno[14];
        mapaResultado[fil+3][col+3] = sensores.terreno[15];
        break;

    case sur :
        mapaResultado[fil+1][col+1] = sensores.terreno[1];
        mapaResultado[fil+1][col] = sensores.terreno[2];
        mapaResultado[fil+1][col-1] = sensores.terreno[3];

        mapaResultado[fil+2][col+2] = sensores.terreno[4];
        mapaResultado[fil+2][col+1] = sensores.terreno[5];
        mapaResultado[fil+2][col] = sensores.terreno[6];
        mapaResultado[fil+2][col-1] = sensores.terreno[7];
        mapaResultado[fil+2][col-2] = sensores.terreno[8];

        mapaResultado[fil+3][col+3] = sensores.terreno[9];
        mapaResultado[fil+3][col+2] = sensores.terreno[10];
        mapaResultado[fil+3][col+1] = sensores.terreno[11];
        mapaResultado[fil+3][col] = sensores.terreno[12];
        mapaResultado[fil+3][col-1] = sensores.terreno[13];
        mapaResultado[fil+3][col-2] = sensores.terreno[14];
        mapaResultado[fil+3][col-3] = sensores.terreno[15];
        break;
    case oeste :
        mapaResultado[fil+1][col-1] = sensores.terreno[1];
        mapaResultado[fil][col-1] = sensores.terreno[2];
        mapaResultado[fil-1][col-1] = sensores.terreno[3];

        mapaResultado[fil+2][col-2] = sensores.terreno[4];
        mapaResultado[fil+1][col-2] = sensores.terreno[5];
        mapaResultado[fil][col-2] = sensores.terreno[6];
        mapaResultado[fil-1][col-2] = sensores.terreno[7];
        mapaResultado[fil-2][col-2] = sensores.terreno[8];

        mapaResultado[fil+3][col-3] = sensores.terreno[9];
        mapaResultado[fil+2][col-3] = sensores.terreno[10];
        mapaResultado[fil+1][col-3] = sensores.terreno[11];
        mapaResultado[fil][col-3] = sensores.terreno[12];
        mapaResultado[fil-1][col-3] = sensores.terreno[13];
        mapaResultado[fil-2][col-3] = sensores.terreno[14];
        mapaResultado[fil-3][col-3] = sensores.terreno[15];
        break;
    }
}
