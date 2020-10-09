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
public class S_pagarCobrar extends Sorpresa{
    
    private int valor;
    
    S_pagarCobrar(int valor, String texto){
        super(texto);
        this.valor = valor;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).modificarSaldo(valor);
        }
    }
    
    @Override
    public String toString() {
       return super.toString();
    }
    
}
