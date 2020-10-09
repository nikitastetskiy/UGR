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
public class S_irCarcel extends Sorpresa{
    
    private Tablero tablero;
    
    S_irCarcel(Tablero tablero, String texto){
        super(texto);
        this.tablero = tablero;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).encarcelar(tablero.getCarcel());
        }
    }
    
    @Override
    public String toString() {
       return super.toString();
    }
}
