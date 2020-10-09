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
public class Casilla {
    
    private String nombre;
    
    Casilla(String nombre){                             // descanso
        this.nombre = nombre;
    }

    public String getNombre() {
        return nombre;
    }
    
    void informe (int actual, ArrayList<Jugador> todos){
        String e="El jugador "+todos.get(actual).getNombre()+" esta en la casilla "+toString();
        Diario.getInstance().ocurreEvento(e);
    }
  
    
    public boolean jugadorCorrecto (int actual, ArrayList<Jugador> todos){
        return actual<todos.size() && actual>=0;
    }
    
    void recibeJugador (int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
    }
    
    @Override
    public String toString() {
        String e = "\n-> Casilla (" + nombre + ")";
        return e;
    }
    
}
