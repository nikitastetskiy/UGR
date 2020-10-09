/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;
import java.util.*;     // para los arrays

/**
 *
 * @author nikitastetskiy
 */
public class Tablero {
    private int numCasillaCarcel, porSalida;
    private ArrayList<Casilla> casillas;
    private boolean tieneJuez;
    
    void añadeCasilla(Casilla casilla){
        if(casillas.size() == numCasillaCarcel){
            Casilla c = new Casilla ("Cárcel");
            casillas.add(c);
        }
        casillas.add(casilla);
        if(casillas.size() == numCasillaCarcel){
            Casilla c = new Casilla ("Cárcel");
            casillas.add(c);
        }
    }
    
    void añadeJuez(){
        C_juez c = new C_juez (1,"Juez");
        casillas.add(c);
        tieneJuez = true;
    }
        
    int calcularTirada(int origen, int destino){
        int suma = destino - origen;
        if(suma < 0){
            suma= suma+casillas.size();
        }
        return suma;
    }
        
    private boolean correcto(){              
        if (casillas.size() > numCasillaCarcel && tieneJuez == true 
        && numCasillaCarcel >= 1)
            return true;
        else
            return false;
    }
    
    boolean correcto(int numCasilla){
        if(correcto() == true && numCasilla < casillas.size())
            return true;
        else
            return false;
    }
    
    int getCarcel(){
        return numCasillaCarcel;
    }
    
    Casilla getCasilla (int numCasilla){
        if(numCasilla < casillas.size()){
            return casillas.get(numCasilla);
        }
        else return null;
    }
        
    int getPorSalida(){
        if(porSalida>0){
            int por = porSalida;
            porSalida--;
            return por;
        }
        else{
            return porSalida;
        }
    }
    
    int nuevaPosicion(int actual, int tirada){
        if(!correcto()){
            return -1;
        }
        else{
            int suma = (actual + tirada)%casillas.size();
            if(suma != actual+tirada){
                porSalida++;
            }
        return suma;
        }
    }

    public Tablero (int indice){
        numCasillaCarcel = indice >= 1 ? indice : 1;
        casillas = new ArrayList<Casilla>();
        Casilla c = new Casilla ("Salida");
        casillas.add(c);
        porSalida = 0;
        tieneJuez = false;
        
    }

}
