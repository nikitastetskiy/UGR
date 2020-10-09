/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
import GUI.Dado;
/**
 *
 * @author nikitastetskiy
 */
public class Jugador implements Comparable<Jugador> {
    
    static protected int CasasMax = 4, CasasPorHotel = 4, HotelesMax = 4;
    protected boolean encarcelado;
    private String nombre;
    private int numCasillaActual;
    static protected float PasoPorSalida = 1000, PrecioLibertad = 200;
    private boolean puedeComprar;
    private float saldo;
    static private float SaldoInicial = 7500;
    
    private ArrayList<TituloPropiedad> propiedades = new ArrayList<>();
    private S_salirCarcel salvoconducto;
    
    Jugador(String n){
        encarcelado = false;
        nombre = n;
        numCasillaActual = 0;
        puedeComprar = true;
        saldo = SaldoInicial;
        salvoconducto = null;
    }
    // ruby ??
    protected Jugador(Jugador otro){
        encarcelado = otro.encarcelado;
        nombre = otro.nombre;
        numCasillaActual = otro.numCasillaActual;
        puedeComprar = otro.puedeComprar;
        saldo = otro.saldo;
        propiedades  = otro.propiedades;
        salvoconducto = otro.salvoconducto;
    }
    
    boolean cancelarHipoteca(int ip){
        boolean result = false;
        if(encarcelado)
            return result;
        if(this.existeLaPropiedad(ip)){
            TituloPropiedad propiedad = propiedades.get(ip);
            float cantidad = propiedad.getImporteCancelarHipoteca();
            boolean puedoGastar = this.puedoGastar(cantidad);
            if(puedoGastar){
                result = propiedad.cancelarHipoteca(this);
                if(result)
                    Diario.getInstance().ocurreEvento("El jugador "+nombre+ " cancela la hipoteca de la propiedad "+ip);
            }
        }
        return result;
    }
    
    int cantidadCasasHoteles(){
        int suma=0;
        for(int i=0; i<propiedades.size(); i++){
            suma+=propiedades.get(i).getNumCasas();
            suma+=propiedades.get(i).getNumHoteles();
        }
        return suma;
    }
    
    public int compareTo(Jugador otro){
        return (new Float(this.getSaldo())).compareTo(new Float(otro.getSaldo()));
    }
    
    boolean comprar(TituloPropiedad titulo){
        boolean result = false;
        if(encarcelado)
            return result;
        if(puedeComprar){
            float precio = titulo.getPrecioCompra();
            if(this.puedoGastar(precio)){
                result = titulo.Comprar(this);
                if(result){
                    propiedades.add(titulo);
                    Diario.getInstance().ocurreEvento("El jugador"+nombre+ " compra la propiedad "+titulo.toString());
                }
                puedeComprar = false;
            }
        }
        return result;
    }
    
    boolean construirCasa(int ip){
        boolean result = false;
        if(encarcelado)
            return result;
        else if(!encarcelado){
            boolean existe = this.existeLaPropiedad(ip);
            if(existe){
                TituloPropiedad propiedad = propiedades.get(ip);
                boolean puedoEdificarCasa = false;
                puedoEdificarCasa = this.puedoEdificarCasa(propiedad);
                float precio = propiedad.getPrecioEdificar();
                if(this.puedoGastar(precio) && propiedad.getNumCasas()<this.getCasasMax())
                    puedoEdificarCasa = true;
                if(puedoEdificarCasa)
                    result = propiedad.construirCasa(this);
            }
        }
        return result;
    }

    boolean construirHotel(int ip){
        boolean result = false;
        if(encarcelado)
            return result;
        if(this.existeLaPropiedad(ip)){
            TituloPropiedad propiedad = propiedades.get(ip);
            boolean puedoEdificarHotel = false;
            puedoEdificarHotel = this.puedoEdificarHotel(propiedad);
            float precio = propiedad.getPrecioEdificar();
            if(this.puedoGastar(precio) && propiedad.getNumHoteles()<this.getHotelesMax() && propiedad.getNumCasas()>=this.getCasasPorHotel())
                puedoEdificarHotel = true;
            else
                puedoEdificarHotel = false;
            if(puedoEdificarHotel){
                result = propiedad.construirHotel(this);
                int casasPorHotel = this.getCasasPorHotel();
                propiedad.derruirCasas(casasPorHotel, this);
                Diario.getInstance().ocurreEvento("El jugador "+nombre+ " construye hotel en la propiedad "+ip);
            }
        }
        return result;
    }
    
    protected boolean debeSerEncarcelado(){
        if(encarcelado)
            return false;
        else{
            if (!tieneSalvoconducto())
                return true;
            else{
                perderSalvoconducto();
                String e="El jugador "+nombre+" se libra de la carcel";
                Diario.getInstance().ocurreEvento(e);
                return false;
            }
        }
    }
    
    boolean enBancarrota(){
        return (saldo<0);
    }
    
    boolean encarcelar(int numCasillaCarcel){
        if(debeSerEncarcelado()){
            moverACasilla(numCasillaCarcel);
            encarcelado = true;
            String evento="El jugador "+nombre+" va a la carcel";
            Diario.getInstance().ocurreEvento(evento);
        }
        return encarcelado;
    }
        
    private boolean existeLaPropiedad(int ip){
        return propiedades.get(ip) != null ? true : false;
    }
    
    int getCasasMax(){
        return CasasMax;
    }

    int getCasasPorHotel(){
        return CasasPorHotel;
    }
    
    int getHotelesMax(){
        return HotelesMax;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    int getNumCasillaActual(){
        return numCasillaActual;
    }
    
    private float getPrecioLibertad(){
        return PrecioLibertad;
    }
    
    private float getPremioPasoSalida(){
        return PasoPorSalida;
    }
    
    public ArrayList<TituloPropiedad> getPropiedades(){
        return propiedades;
    }
    
    boolean getPuedeComprar(){
        return puedeComprar;
    }
    
    public float getSaldo(){
        return saldo;
    }
    
    boolean hipotecar(int ip){
        boolean result = false;
        if(encarcelado)
            return result;
        if(this.existeLaPropiedad(ip)){
            TituloPropiedad propiedad = propiedades.get(ip);
            result = propiedad.hipotecar(this);
        }
        if(result)
            Diario.getInstance().ocurreEvento("El jugador "+nombre+ " hipoteca la propiedad "+ip);
        return result;
    }
    
    public boolean isEncarcelado(){
        return encarcelado;
    }
    
    boolean modificarSaldo(float cantidad){
        saldo += cantidad;
        String e="Se ha modificado saldo "+saldo;
        Diario.getInstance().ocurreEvento(e);
        return true;
    }

    boolean moverACasilla(int numCasilla) {
        if (encarcelado) {
            return false;
        } else {
        numCasillaActual = numCasilla;
        puedeComprar = false;
        String e = "Se mueve a casilla " + numCasillaActual;
        Diario.getInstance().ocurreEvento(e);
        return true;
        }
    }
    
    boolean obtenerSalvoconducto (Sorpresa s){
        if(encarcelado)
            return false;
        else{
            salvoconducto = (S_salirCarcel) s;
            return true;
        }
    }
    
    boolean paga(float cantidad){
        return modificarSaldo(cantidad*-1);
    }
    
    boolean pagaAlquiler(float cantidad){
        if(encarcelado)
            return false;
        else{
            return paga(cantidad);
        }
    }
    
    boolean pagaImpuesto(float cantidad){
        if(encarcelado)
            return false;
        else{
            String e = "El jugador " + nombre + " paga de impuesto " + cantidad+'$';
            Diario.getInstance().ocurreEvento(e);
            return paga(cantidad);
        }
    }
    
    boolean pasaPorSalida(){
        modificarSaldo(PasoPorSalida);
        String e="Se ha pasado por la salida";
        Diario.getInstance().ocurreEvento(e);
        return true;
    }
    
    void perderSalvoconducto(){
        salvoconducto.usada();
        salvoconducto = null;
    }
    
    boolean puedeComprarCasilla (){
        if(encarcelado)
            puedeComprar = false;
        else
            puedeComprar = true;
        return puedeComprar;
    }
    
    private boolean puedeSalirCarcelPagando(){
        return saldo>=PrecioLibertad;
    }
    
    private boolean puedoEdificarCasa(TituloPropiedad propiedad){
        if(cantidadCasasHoteles()<= HotelesMax+CasasMax && propiedad.getNumCasas()<=CasasMax
            && saldo>=propiedad.getPrecioEdificar())
            return true;
        else
            return false;
    }
    
    private boolean puedoEdificarHotel(TituloPropiedad propiedad){
        if(cantidadCasasHoteles()<= HotelesMax+CasasMax && propiedad.getNumCasas()<=CasasMax
            && propiedad.getNumHoteles()<=HotelesMax && saldo>=propiedad.getPrecioEdificar())
            return true;
        else
            return false;
    }
    
    private boolean puedoGastar(float precio){
        if(encarcelado)
            return false;
        return saldo>=precio;
    }
    
    boolean recibe(float cantidad){
        if(encarcelado)
            return false;
        else{
            return modificarSaldo(cantidad);
        }
    }
     
    boolean salirCarcelPagando(){
        if(encarcelado && puedeSalirCarcelPagando()){
            paga(PrecioLibertad);
            encarcelado = false;
            String e="Se ha salido de la carcel";
            Diario.getInstance().ocurreEvento(e);
            return true;
        }
        return false;
    }
    
    boolean salirCarcelTirando(){
        if(Dado.getInstance().salgoDeLaCarcel()){
            encarcelado = false;
            String e="Se ha salido de la carcel";
            Diario.getInstance().ocurreEvento(e);
            return true;
        }
        return false;
    }
    
    boolean tieneAlgoQueGestionar(){
        return propiedades.size() > 0 ? true : false;
    }
    
    boolean tieneSalvoconducto(){
        return salvoconducto == null ? false : true;
    }

    @Override
    public String toString() {
        String e = ">> Jugador \t----("+ nombre+")----"
                + "\n\t\ten casilla "+numCasillaActual;
        if(encarcelado)
            e += "\n\t\tencarcelado";
        if(puedeComprar)
            e += "\n\t\tpuede comprar";
        else
            e += "\n\t\tno puede comprar";
        e += "\n\t\t" + saldo + "$" + "\n\t\tpropiedades=" + propiedades + "\n\t\tsalvoconducto=";
        if(salvoconducto == null)
            e += "()";
        else
            e += salvoconducto;
        e += "\n";
        return e;
    }
    
    boolean vender(int ip){
        if(encarcelado)
            return false;
        if(existeLaPropiedad(ip)){
            propiedades.get(ip).vender(this);
            String e="Se ha vendido la propiedad "+propiedades.get(ip);
            Diario.getInstance().ocurreEvento(e);
            propiedades.remove(ip);
            return true;
        }
        return false;
    }
    
}
