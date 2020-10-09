/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package JuegoTexto;

import civitas.CivitasJuego;
import civitas.GestionesInmobiliarias;
import civitas.OperacionesJuego;
import civitas.Respuestas;
import civitas.OperacionInmobiliaria;
import civitas.SalidasCarcel;

/**
 *
 * @author nikitastetskiy
 */
public class Controlador {
    private CivitasJuego juego;
    private VistaTextual vista;
    
    Controlador(CivitasJuego juego, VistaTextual vista){
        this.juego = juego;
        this.vista = vista;
    }
    
    void juega(){
        vista.setCivitasJuego(juego);
        vista.mostrarEventos();
        while(!juego.finalDelJuego(0)){
            vista.actualizarVista();
            vista.pausa();
            OperacionesJuego operacion = juego.siguientePaso();
            vista.mostrarSiguienteOperacion(operacion);
            if(operacion != OperacionesJuego.PASAR_TURNO)
                vista.mostrarEventos();
            if(!juego.finalDelJuego(0)){
                if(operacion == OperacionesJuego.COMPRAR){
                    if(vista.comprar() == Respuestas.SI){
                        juego.comprar();
                    }
                    juego.siguientePasoCompletado(operacion);
                }
                else if(operacion == OperacionesJuego.GESTIONAR){
                    vista.gestionar();
                    //System.out.println(vista.getGestion());
                    //System.out.println(vista.getPropiedad());
                    OperacionInmobiliaria op_inmobiliaria = new OperacionInmobiliaria(GestionesInmobiliarias.values()[vista.getGestion()], vista.getPropiedad());
                    //vista.gestionar(); este metodo tiene que llamar a otra cosa correspondiente a op_inmobiliaria
                    juego.siguientePasoCompletado(operacion);
                }
                else if(operacion == OperacionesJuego.SALIR_CARCEL){
                    SalidasCarcel salirCarcel = vista.salirCarcel();
                    if(salirCarcel == SalidasCarcel.PAGANDO)
                        juego.salirCarcelPagando();
                    else if(salirCarcel == SalidasCarcel.TIRANDO)
                        juego.salirCarcelTirando();
                    juego.siguientePasoCompletado(operacion);
                }
            }
        }
        System.out.println(juego.ranking());
    }
}
