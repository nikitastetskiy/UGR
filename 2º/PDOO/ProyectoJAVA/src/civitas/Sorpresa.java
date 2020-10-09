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
public abstract class Sorpresa {
    
    private String texto;
    
    abstract void aplicarAJugador(int actual, ArrayList<Jugador> todos);
    
    void informe(int actual, ArrayList<Jugador> todos){
        String e="El jugador "+todos.get(actual).getNombre()+" utiliza sorpresa: "+toString();
        Diario.getInstance().ocurreEvento(e);
    }
    
    public boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos){
        return actual<todos.size() && actual>=0;
    }
   
    Sorpresa(String texto){
        this.texto = texto;
    }
    
    @Override
    public String toString() {
        return "<<" + texto + ">>";
    }
}