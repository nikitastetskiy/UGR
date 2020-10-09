/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author nikitastetskiy
 */
public class MazoSorpresas {
    
    private boolean barajada, debug;
    private int usadas;
    private Sorpresa ultimaSorpresa;
    
    private ArrayList<Sorpresa> sorpresas, cartasEspeciales; // cartasEspeciales como SALIRCARCEL
    
    void alMazo(Sorpresa s){
        if(!barajada){
            sorpresas.add(s);
        }
    }

    Sorpresa getUltimaSorpresa(){
        return ultimaSorpresa;
    }
    
    void habilitarCartaEspecial(Sorpresa sorpresa){
        if(cartasEspeciales.contains(sorpresa)){
            cartasEspeciales.remove(sorpresa);
            sorpresas.add(sorpresa);
            String e = "CartaEspecial removida y añadida a sorpresas";
            Diario.getInstance().ocurreEvento(e);
        }
    }
        
    void inhabilitarCartaEspecial(Sorpresa sorpresa){
        if(sorpresas.contains(sorpresa)){
            sorpresas.remove(sorpresa);
            cartasEspeciales.add(sorpresa);
            String e = "Carta sorpresa removida y añadida a cartasEspeciales";
            Diario.getInstance().ocurreEvento(e);
        }
    }
    
    private void init (){
        cartasEspeciales = new ArrayList<Sorpresa>();
        sorpresas = new ArrayList<Sorpresa>();
        ultimaSorpresa = null;                              // ?
        barajada = false;
        usadas = 0;
    }
    
    public MazoSorpresas(){
        init();
        debug = false;
    }
    
    public MazoSorpresas(boolean d){
        init();
        debug = d;
        if(debug){
            String e = "Debug-> true";
            Diario.getInstance().ocurreEvento(e);
        }
    }

    Sorpresa siguiente(){
        if((!barajada || usadas == sorpresas.size()) && !debug){
            usadas = 0;
            barajada = true;
            Collections.shuffle(sorpresas);
        }
        usadas ++;
        Sorpresa s = sorpresas.get(0);
        sorpresas.remove(0);
        sorpresas.add(s);
        ultimaSorpresa = s;
        return s;
    }

}
