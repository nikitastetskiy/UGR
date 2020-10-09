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
public class C_impuesto extends Casilla{
    private float importe;
    
    C_impuesto(float cantidad, String nombre){
        super(nombre);
        importe = cantidad;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).pagaImpuesto(importe);
        }
    }
    
    @Override
    public String toString() {
        String e = "\n-> Casilla ("+ super.getNombre() + ") " + importe + "$";
        return e;
    }
}
