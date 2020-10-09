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
public class C_juez extends Casilla{
    
    private static int carcel;
    
    C_juez(int numCasillaCarcel, String nombre){       // juez
        super(nombre);
        carcel = numCasillaCarcel;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual, todos)){
            informe(actual, todos);
            todos.get(actual).encarcelar(carcel);
        }
    }
    
    @Override
    public String toString() {
        String e = "\n-> Casilla ("+ super.getNombre() + ")";
        return e;
    }
}
