/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
import java.util.Collections;
import GUI.Dado;
/**
 *
 * @author nikitastetskiy
 */
public class CivitasJuego {
    
    private int indiceJugadorActual;
    
    private ArrayList<Jugador> jugadores = new ArrayList<>();
    private GestorEstados gestorEstados = new GestorEstados();
    private EstadosJuego estado = gestorEstados.estadoInicial();
    private MazoSorpresas mazo;
    private Tablero tablero;
    
    public CivitasJuego(ArrayList<String> n){
        int num = n.size()>4 ? 4 : n.size();
        for(int i=0; i<num; i++){
            jugadores.add(new Jugador(n.get(i)));
        }
        gestorEstados = new GestorEstados();
        gestorEstados.estadoInicial();
        indiceJugadorActual = Dado.getInstance().quienEmpieza(jugadores.size()); // gestor ??
        mazo = new MazoSorpresas();
        tablero = new Tablero(0);
        inicializaTablero(mazo);
        inicializaMazoSorpresas(tablero);
    }
    
    private void avanzaJugador(){
        Jugador jugadorActual = jugadores.get(indiceJugadorActual);
        int posicionActual = jugadorActual.getNumCasillaActual();
        int tirada = Dado.getInstance().tirar();
        int posicionNueva = tablero.nuevaPosicion(posicionActual, tirada);
        Casilla casilla = tablero.getCasilla(posicionNueva);
        this.contabilizarPasosPorSalida(jugadorActual);
        jugadorActual.moverACasilla(posicionNueva);
        casilla.recibeJugador(indiceJugadorActual, jugadores);
        this.contabilizarPasosPorSalida(jugadorActual);
    }
    
    void actualizarInfo(){
        for(int i=0; i<jugadores.size(); i++){
            jugadores.get(i).toString();
            jugadores.get(i).getPropiedades().toString();
            int c = jugadores.get(i).getNumCasillaActual();
            tablero.getCasilla(c).toString();
        }
    }
    
    private void inicializaTablero(MazoSorpresas mazo) {
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Praga", 760, (float) 1.5, 750, 1750, 550)));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Granada", 750, (float) 1.15, 600, 1900, 250)));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Moraleda", 800, (float) 1.1, 730, 1900, 370)));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("San Pedro", 560, (float) 1.05, 480, 1980, 420)));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Conil", 640, (float) 1.3, 590, 1700, 260)));
        tablero.añadeJuez();
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Budapest", 900, (float) 1.4, 800, 1730, 680)));
        tablero.añadeCasilla(new C_sorpresa(mazo, "Sorpresa1"));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Tarragona", 780, (float) 1.16, 700, 1560, 410)));
        tablero.añadeCasilla(new Casilla("Parking"));
        tablero.añadeCasilla(new C_sorpresa(mazo, "Sorpresa2"));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Benalmadena", 500, (float) 1.45, 390, 1150, 320)));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Almagro", 890, (float) 1.04, 770, 1690, 520)));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Sevilla", 730, (float) 1.7, 690, 1980, 490)));
        tablero.añadeCasilla(new C_impuesto(1000, "Impuesto"));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Palenciana", 1000, (float) 1.2, 950, 1800, 750)));
        tablero.añadeCasilla(new C_sorpresa(mazo, "Sorpresa3"));
        tablero.añadeCasilla(new C_calle(new TituloPropiedad("Malaga", 600, (float) 1.9, 480, 1380, 390)));
    }

    private void inicializaMazoSorpresas(Tablero tablero) {
        mazo.alMazo(new S_irCarcel(tablero, "Lo siento, te vas a la carcel"));
        mazo.alMazo(new S_salirCarcel(mazo, "Te libras de la carcel"));
        mazo.alMazo(new S_porJugador(250, "Es tu cumpleaños y tus amigos no pueden ir sin un regalo, cada jugador te paga 250"));
        mazo.alMazo(new S_porJugador(-300, "¿Oyes eso? creo que son los matones de tus acreedores llamando a la puerta, pagas a cada jugador 300"));
        mazo.alMazo(new S_porCasaHotel(50, "El banco te ha cobrado la clausula suelo y un abogado te ha conseguido un buen trato, ganas 50 por cada casa y hotel"));
        mazo.alMazo(new S_porCasaHotel(-50, "Un tifon ha causado serios daños en tus propiedades, pagas 50 por cada casa y hotel"));
        mazo.alMazo(new S_irCasilla(tablero, 4, "Me han dicho que Moraleda esta muy bonita en esta epoca del año, te desplazas a moraleda"));
        mazo.alMazo(new S_irCasilla(tablero, 14, "Tu primo se ha operado deberias ir a verle, te desplazas a Sevilla"));
        mazo.alMazo(new S_irCasilla(tablero, 6, "¡Tu hermana acaba de dar a luz!, te desplazas a Conil"));
        mazo.alMazo(new S_pagarCobrar(500, "Participas en el pasapalabra y empatas(ni tu te lo crees), te llevas 500"));
        mazo.alMazo(new S_pagarCobrar(-500, "Has roto la Playstation de tu amigo, deberias meterte las manos en los bolsillos, pagas 500"));
        mazo.alMazo(new S_especulador(500, "Has de convertirte en jugador especulador je, je, je"));
    }
    
    private void contabilizarPasosPorSalida (Jugador jugadorActual){
        if(tablero.getPorSalida()>0)
            jugadorActual.pasaPorSalida();
    }
    
    private void pasarTurno (){
        indiceJugadorActual++;
        indiceJugadorActual = indiceJugadorActual%(jugadores.size());
    }
    
    public void siguientePasoCompletado (OperacionesJuego operacion){
        estado = gestorEstados.siguienteEstado(getJugadorActual(), estado, operacion);
    }

    public boolean construirCasa (int ip){
        return getJugadorActual().construirCasa(ip);
    }
    
    public boolean construirHotel (int ip){
        return getJugadorActual().construirHotel(ip);
    }
    
    public boolean vender (int ip){
        return getJugadorActual().vender(ip);
    }
    
    public boolean hipotecar (int ip){
        return getJugadorActual().hipotecar(ip);
    }
    
    public boolean cancelarHipoteca (int ip){
        return getJugadorActual().cancelarHipoteca(ip);
    }
    
    public boolean salirCarcelPagando (){
        return getJugadorActual().salirCarcelPagando();
    }
    
    public boolean salirCarcelTirando (){
        return getJugadorActual().salirCarcelTirando();
    }
    
    public boolean finalDelJuego (int ip){
        boolean bo = false;
        int i = 0;
        while(i<jugadores.size() && !bo){
            bo = jugadores.get(i).enBancarrota();
            i++;
        }
        return bo;
    }
    
    public Casilla getCasillaActual(){
        return tablero.getCasilla(jugadores.get(indiceJugadorActual).getNumCasillaActual());
    }
    
    public Jugador getJugadorActual(){
        return jugadores.get(indiceJugadorActual);
    }
    
    public ArrayList<Jugador> ranking(){
        Collections.sort(jugadores);
        return jugadores;
    }
   
    public OperacionesJuego siguientePaso(){
        Jugador jugadorActual = jugadores.get(indiceJugadorActual);
        OperacionesJuego operacion = gestorEstados.operacionesPermitidas(jugadorActual, estado);
        if(operacion == OperacionesJuego.PASAR_TURNO){
            this.pasarTurno();
            this.siguientePasoCompletado(operacion);
        }
        else if(operacion == OperacionesJuego.AVANZAR){
            this.avanzaJugador();
            this.siguientePasoCompletado(operacion);
        }
        return operacion;
    }
            
    public boolean comprar(){
        boolean res = false;
        Casilla casilla = this.getCasillaActual();
        C_calle calle = (C_calle)casilla;
        TituloPropiedad titulo = calle.getTituloPropiedad();
        res = getJugadorActual().comprar(titulo);
        return res;
    }
}
