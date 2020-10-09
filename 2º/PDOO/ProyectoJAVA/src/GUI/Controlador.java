/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import civitas.CivitasJuego;
import civitas.GestionesInmobiliarias;
import civitas.OperacionesJuego;
import civitas.OperacionInmobiliaria;
import civitas.SalidasCarcel;
import civitas.GestionesInmobiliarias;

/**
 *
 * @author nikitastetskiy
 */
public class Controlador {
    private CivitasJuego juego;
    private CivitasView vista;
    
    public Controlador(CivitasJuego juego, CivitasView vista){
        this.juego = juego;
        this.vista = vista;
    }
    
    public void juega(){
        vista.setCivitasJuego(juego);
        while(!juego.finalDelJuego(0)){
            vista.actualizarVista();
           // vista.pausa();
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
                }else if(operacion == OperacionesJuego.GESTIONAR){
                    vista.gestionar();
                    /*OperacionInmobiliaria op_inmobiliaria = new OperacionInmobiliaria(GestionesInmobiliarias.values()[vista.getGestion()], vista.getPropiedad());
                    juego.siguientePasoCompletado(operacion);*/
                    GestionesInmobiliarias gest = GestionesInmobiliarias.values()[vista.getGestion()];
                    int ip = vista.getPropiedad();
                    OperacionInmobiliaria op = new OperacionInmobiliaria(gest, ip);
                    if(op.getGestion()==GestionesInmobiliarias.VENDER){
                        juego.vender(vista.getPropiedad());
                    }else if(op.getGestion()==GestionesInmobiliarias.HIPOTECAR){
                        juego.hipotecar(vista.getPropiedad());
                    }else if(op.getGestion()==GestionesInmobiliarias.CANCELAR_HIPOTECA){
                        juego.cancelarHipoteca(vista.getPropiedad());
                    }else if(op.getGestion()==GestionesInmobiliarias.CONSTRUIR_CASA){
                        juego.construirCasa(vista.getPropiedad());
                    }else if(op.getGestion()==GestionesInmobiliarias.CONSTRUIR_HOTEL){
                        juego.construirHotel(vista.getPropiedad());
                    }else if(op.getGestion()==GestionesInmobiliarias.TERMINAR){
                        juego.siguientePasoCompletado(operacion);
                    }
                }else if(operacion == OperacionesJuego.SALIR_CARCEL){
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
