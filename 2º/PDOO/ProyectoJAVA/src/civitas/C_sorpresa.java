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
public class C_sorpresa extends Casilla{
    
    private Sorpresa sorpresa;
    private MazoSorpresas mazo;
    
    C_sorpresa(MazoSorpresas mazo, String nombre) {         // sorpresa
        super(nombre);
        this.mazo = mazo;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual, todos)){
            Sorpresa sorpresa = mazo.siguiente();
            informe(actual, todos);
            sorpresa.aplicarAJugador(actual, todos);
        }
    }
    
    @Override
    public String toString() {
        String e = "\n-> Casilla ("+ super.getNombre() + ")";
        return e;
    }
}
