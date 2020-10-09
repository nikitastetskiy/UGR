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
public class S_salirCarcel extends Sorpresa{
 
    private MazoSorpresas mazo;
    
    S_salirCarcel(MazoSorpresas mazo, String texto){
        super(texto);
        this.mazo = mazo;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if(jugadorCorrecto(actual, todos)){
            informe(actual, todos);
            boolean nlt = true;
            for(int i=0; i<todos.size(); i++){
                if(todos.get(i).tieneSalvoconducto())
                    nlt = false;
            }
            if(nlt)
                todos.get(actual).obtenerSalvoconducto(this);
            salirDelMazo();
        }
    }
    
    void salirDelMazo() {
        mazo.inhabilitarCartaEspecial(this);
    }
    
    void usada() {
        mazo.habilitarCartaEspecial(this);
    }
    
    @Override
    public String toString() {
       return super.toString();
    }
}
