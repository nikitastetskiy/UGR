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
public class S_especulador extends Sorpresa{
    
    private float valor;
    
    S_especulador(float valor, String texto){
        super(texto);
        this.valor = valor;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            J_especulador jugadorEsp = new J_especulador(todos.get(actual), valor);
            todos.set(actual, jugadorEsp);
        }
    }
    
}
