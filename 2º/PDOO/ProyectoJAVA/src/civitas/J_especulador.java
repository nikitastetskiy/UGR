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
public class J_especulador extends Jugador{
    
    private static int factorEspeculador = 2;
    private float fianza;
    
    J_especulador(Jugador jugador, float fianza){
        super(jugador);
        this.fianza = fianza;
        for(int i=0; i<super.getPropiedades().size(); i++){
            super.getPropiedades().get(i).actualizaPropietarioPorConversion(this);
        }
    }
    
    @Override // esto funciona ?? no puede entrar dos veces en el if ?
    boolean encarcelar(int numCasillaCarcel){
        encarcelado = false;
        if(!super.encarcelado && super.tieneSalvoconducto()){
            super.perderSalvoconducto();
            String e = "El jugador " + super.getNombre() + " se libra de la carcel";
            Diario.getInstance().ocurreEvento(e);
            encarcelado = false;
        }
        else if(!super.encarcelado && fianza<super.getSaldo()){
            super.paga(fianza);
            String e = "El jugador " + super.getNombre() + " se libra de la carcel pagando la fianza";
            Diario.getInstance().ocurreEvento(e);
            encarcelado = false;
        }
        else
            encarcelado = true;
        return encarcelado;
    }
    
    @Override
    int getCasasMax(){
        return (super.getCasasMax()*factorEspeculador);
    }
    
    @Override
    int getHotelesMax(){
        return (super.getHotelesMax()*factorEspeculador);
    }
    
    @Override
    boolean pagaImpuesto(float cantidad){
        if(encarcelado)
            return false;
        else{
            String e = "El jugador " + super.getNombre() + " paga de impuesto " + cantidad/2+'$';
            Diario.getInstance().ocurreEvento(e);
            return paga(cantidad/2);
        }
    }
    
    @Override
    public String toString() {
        String e = super.toString();
        e += "\t\t☆ Especulador ☆\n";
        return e;
    }
}
