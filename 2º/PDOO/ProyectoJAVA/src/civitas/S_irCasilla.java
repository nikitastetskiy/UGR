/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author nikitastetskiy
 */
public class S_irCasilla extends Sorpresa{
    
    private Tablero tablero;
    private int valor;
    
    S_irCasilla(Tablero tablero, int valor, String texto){
        super(texto);
        this.tablero = tablero;
        this.valor = valor;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            int casillaActual = todos.get(actual).getNumCasillaActual();
            int tirada = tablero.calcularTirada(casillaActual, valor);
            int nuevaPosicion = tablero.nuevaPosicion(casillaActual, tirada);
            todos.get(actual).moverACasilla(nuevaPosicion);
            Casilla c = tablero.getCasilla(nuevaPosicion);
            c.recibeJugador(actual, todos);
        }
    }
    
    @Override
    public String toString() {
       return super.toString();
    }
    
}
