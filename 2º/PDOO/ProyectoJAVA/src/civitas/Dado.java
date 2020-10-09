/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.Random;

/**
 *
 * @author nikitastetskiy
 */
public class Dado {

  static final private Dado instance = new Dado();
  static final private int SalidaCarcel = 5;
  
  Random random;
  int ultimoResultado;
  boolean debug;

  private Dado(){
      ultimoResultado=0;
      random= new Random();
      debug=false;
  }
    
  int getUltimoResultado(){
      return ultimoResultado;
  }
  
  public static Dado getInstance() {
      return instance;
  }
    
  int tirar (){
      if(debug){
          return ultimoResultado= 1;
      }
      else{
          return ultimoResultado= 1+random.nextInt(6);
      }
  }
  
  boolean salgoDeLaCarcel(){
      int n = tirar();
      boolean x = n >= 5 ? true : false;
      return x;
  }
  
  public int quienEmpieza(int n){
      return random.nextInt(n);
  }
  
  public void setDebug(Boolean d){
      debug = d;
      String e= debug == true ? "Debug-> true":"Debug-> false";
      Diario.getInstance().ocurreEvento(e);
  }

}
