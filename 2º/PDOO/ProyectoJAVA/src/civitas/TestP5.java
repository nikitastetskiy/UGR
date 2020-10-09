/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;
import GUI.CivitasView;
import GUI.Dado;
import GUI.CapturaNombres;
import java.util.ArrayList;
import GUI.Controlador;
/**
 *
 * @author Manu
 */
public class TestP5 {
    public static void main(String[] args) {
        CivitasView vista=new CivitasView();
        Dado.createInstance(vista);
        CapturaNombres cap= new CapturaNombres(vista, true);

        ArrayList<String> nombres = new ArrayList<>();
        nombres=cap.getNombres(); 
        System.out.println(nombres);
        CivitasJuego juego = new CivitasJuego(nombres);
        Controlador control = new Controlador(juego, vista);
       
        
        vista.setCivitasJuego(juego);
        vista.actualizarVista();//se le llama en mostrar siguiente operacion
        control.juega();
        
        
    }
}
