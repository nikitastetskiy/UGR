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
public class S_porJugador extends Sorpresa{
    
    private int valor;
    
    S_porJugador(int valor, String texto){
        super(texto);
        this.valor = valor;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            Sorpresa s1 = new S_pagarCobrar(valor * -1, "PagarTodos");
            Sorpresa s2 = new S_pagarCobrar(valor * (todos.size() - 1), "PagarActual");
            for (int i = 0; i < todos.size(); i++) {
                if (i != actual) {
                    s1.aplicarAJugador(i, todos);
                }
            }
            s2.aplicarAJugador(actual, todos);
        }
    }
    
    @Override
    public String toString() {
       return super.toString();
    }
}
