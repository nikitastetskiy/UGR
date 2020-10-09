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
public class TestP4 {
    
    public static void main(String[] args) {
    
    Jugador uno = new Jugador("uno");
    S_especulador sorpresa = new S_especulador(8500, "Sorpresa espculante");
    ArrayList<Jugador> lista = new ArrayList<>();
    lista.add(uno);
    
    TituloPropiedad propiedad = new TituloPropiedad("Praga", 7600, (float) 1.5, 750, 1750, 550);
    
    lista.get(0).comprar(propiedad);
    
    System.out.println(lista.get(0).toString());
    
    sorpresa.aplicarAJugador(0, lista);
    
    System.out.println(lista.get(0).toString());
    
    lista.get(0).debeSerEncarcelado();
    lista.get(0).encarcelar(1);
    System.out.println(lista.get(0).toString());
    
    }
    
}