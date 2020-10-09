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
public class C_calle extends Casilla{
    
    private TituloPropiedad tituloPropiedad;
    private float importe;
    
    C_calle(TituloPropiedad titulo) {                    // calle
        super(titulo.getNombre());
        tituloPropiedad = titulo;
        importe = titulo.getPrecioCompra();
    }
    
    @Override
    void recibeJugador (int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual, todos)){
            super.informe(actual, todos);
            Jugador jugador = todos.get(actual);
            if(!tituloPropiedad.tienePropietario())
                jugador.puedeComprarCasilla();
            else
                tituloPropiedad.tramitarAlquiler(jugador);
        }
    }
    
    TituloPropiedad getTituloPropiedad(){
        return tituloPropiedad;
    }
    
    @Override
    public String toString() {
        String e = "\n-> Casilla ("+ super.getNombre() + ") " + importe + "$";
        return e;
    }
    
}
