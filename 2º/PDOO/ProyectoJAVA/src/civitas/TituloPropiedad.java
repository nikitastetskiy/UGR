/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author nikitastetskiy
 */
public class TituloPropiedad {
    
    private float alquilerBase, factorRevalorizacion, hipotecaBase, precioCompra, precioEdificar;
    static final private float factorInteresesHipoteca = 1.1f;
    private boolean hipotecado;
    private String nombre;
    private int numCasas, numHoteles;
    
    private Jugador propietario;
    
    void actualizaPropietarioPorConversion(Jugador jugador){
        propietario = jugador;
    }
        
    boolean cancelarHipoteca (Jugador jugador){
        if(hipotecado && esEsteElPropietario(jugador)){
            jugador.paga(this.getImporteCancelarHipoteca());
            hipotecado = false;
            return true;
        }
        else
            return false;
    }
        
    int cantidadCasasHoteles(){
        return numCasas + numHoteles; 
    }
        
    boolean Comprar(Jugador jugador){
        if(tienePropietario()){
            return false;
        }
        else{
            propietario = jugador;      // ???
            jugador.paga(precioCompra);
            return true;
        }
    }
    
    boolean construirCasa(Jugador jugador){
        if(esEsteElPropietario(jugador)){
            jugador.paga(precioEdificar);
            numCasas++;
            return true;
        }
        else
            return false;
    }
    
    boolean construirHotel(Jugador jugador){
        if(esEsteElPropietario(jugador) && numCasas>=4){
            jugador.paga(precioEdificar);
            numHoteles++;
            return true;
        }
        else
            return false;
    }

    public boolean derruirCasas(int n, Jugador jugador){
        if(esEsteElPropietario(jugador) && numCasas >= n){
            numCasas = numCasas - n;
            return true;
        }
        else
            return false;
    }
    
    private boolean esEsteElPropietario(Jugador jugador){
        return jugador == propietario;
    }
    
    public boolean getHipotecado(){
        return hipotecado;
    }

    float getImporteCancelarHipoteca(){
        return alquilerBase * factorInteresesHipoteca;
    }

    private float getImporteHipoteca(){
        return (float)(hipotecaBase*(1+(numCasas*0.5)+(numHoteles*2.5)));
    }
    
    public String getNombre() {
        return nombre;
    }

    public int getNumCasas() {
        return numCasas;
    }

    public int getNumHoteles() {
        return numHoteles;
    }
    
    private float getPrecioAlquiler(){
        if(hipotecado || propietarioEncarcelado())
            return 0;
        else
            return (float)(alquilerBase*(1+(numCasas*0.5)+(numHoteles*2.5)));
    }
    
    float getPrecioCompra(){
        return precioCompra;
    }

    float getPrecioEdificar(){
        return precioEdificar;
    }

    private float getPrecioVenta(){
        return ((precioCompra + precioEdificar*(numCasas+ 5 *numHoteles))*factorInteresesHipoteca);
    }
   
    Jugador getPropietario(){
        return propietario;
    }
    
    boolean hipotecar(Jugador jugador){
        if(!hipotecado && esEsteElPropietario(jugador)){
            jugador.recibe(this.getImporteHipoteca());
            hipotecado = true;
            return true;
        }
        else
            return false;
    }
        
    private boolean propietarioEncarcelado(){
        return propietario.isEncarcelado()==true ? true : false;
    }
 
    boolean tienePropietario(){
        return propietario != null;
    }
    
    TituloPropiedad(String nom, float ab, float fr, float hb, float pc, float pe){
        nombre = nom;
        alquilerBase = ab;
        factorRevalorizacion = fr;
        hipotecaBase = hb;
        precioCompra = pc;
        precioEdificar = pe;
        numCasas = numHoteles = 0;
        hipotecado = false;
    }

    @Override
    public String toString() {
        String e = nombre + "("+ numCasas +"," + numHoteles + ")";
        return e;
    }

    void tramitarAlquiler(Jugador jugador){
        if(tienePropietario() && !esEsteElPropietario(jugador)){
            jugador.pagaAlquiler(alquilerBase);
            propietario.recibe(alquilerBase);
        }
    }
    
    boolean vender(Jugador jugador){
        return true;
    }

}
