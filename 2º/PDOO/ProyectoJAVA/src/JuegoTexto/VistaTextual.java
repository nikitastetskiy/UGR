package JuegoTexto;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import civitas.CivitasJuego;
import civitas.Diario;
import civitas.OperacionesJuego;
import civitas.Respuestas;
import civitas.SalidasCarcel;

class VistaTextual {
  
  CivitasJuego juegoModel; 
  int iGestion=-1;
  int iPropiedad=-1;
  private static String separador = "=====================";
  
  private Scanner in;
  
  VistaTextual () {
    in = new Scanner (System.in);
  }
  
  void mostrarEstado(String estado) {
    System.out.println (estado);
  }
              
  void pausa() {
    System.out.print ("Pulsa una tecla");
    in.nextLine();
  }

  int leeEntero (int max, String msg1, String msg2) {
    Boolean ok;
    String cadena;
    int numero = -1;
    do {
      System.out.print (msg1);
      cadena = in.nextLine();
      try {  
        numero = Integer.parseInt(cadena);
        ok = true;
      } catch (NumberFormatException e) { // No se ha introducido un entero
        System.out.println (msg2);
        ok = false;  
      }
      if (ok && (numero < 0 || numero >= max)) {
        System.out.println (msg2);
        ok = false;
      }
    } while (!ok);

    return numero;
  }

  int menu (String titulo, ArrayList<String> lista) {
    String tab = "  ";
    int opcion;
    System.out.println (titulo);
    for (int i = 0; i < lista.size(); i++) {
      System.out.println (tab+i+"-"+lista.get(i));
    }

    opcion = leeEntero(lista.size(),
                          "\n"+tab+"Elige una opción: ",
                          tab+"Valor erróneo");
    return opcion;
  }

  SalidasCarcel salirCarcel() {
    int opcion = menu ("Elige la forma para intentar salir de la carcel",
      new ArrayList<> (Arrays.asList("Pagando","Tirando el dado")));
    return (SalidasCarcel.values()[opcion]);
  }

  Respuestas comprar(){
      String e = juegoModel.getCasillaActual().toString();
      int opcion = menu ("Elige si quieres comprar la calle "+e,
      new ArrayList<> (Arrays.asList("No comprar","Comprar")));
    return (Respuestas.values()[opcion]);
  }

  void gestionar (){
      iGestion = -1;
      while(iGestion != 5){
        ArrayList<String> propiedadesString  = new ArrayList<>();
        juegoModel.getJugadorActual().getPropiedades().forEach((p) -> {
        propiedadesString.add(p.toString());
        });
        iGestion = menu ("Elige el numero de gestion inmobiliaria",
        new ArrayList<> (Arrays.asList("Vender", "Hipotecar", "Cancelar hipoteca", "Construir casa", "Construir hotel", "Terminar")));
        if(iGestion != 5)
            iPropiedad = menu ("Elige el numero de propiedad", propiedadesString);
        
        if(iGestion ==0)
          juegoModel.vender(iPropiedad);
        else if(iGestion ==1)
          juegoModel.hipotecar(iPropiedad);
        else if(iGestion ==2)
          juegoModel.cancelarHipoteca(iPropiedad);
        else if(iGestion ==3)
          juegoModel.construirCasa(iPropiedad);
        else if(iGestion ==4)
          juegoModel.construirHotel(iPropiedad);
      }
  }
  
  public int getGestion(){
      return iGestion;
  }
  
  public int getPropiedad(){
      return iPropiedad;
  }
    

  void mostrarSiguienteOperacion(OperacionesJuego operacion) {
      System.out.println (operacion);
  }


  void mostrarEventos(){
      while(Diario.getInstance().eventosPendientes()){
          System.out.println(Diario.getInstance().leerEvento()); 
      }
  }
  
  public void setCivitasJuego(CivitasJuego civitas){ 
        juegoModel=civitas;
        //this.actualizarVista();
    }
  
  void actualizarVista(){
    mostrarEstado("Vista:\n>"+juegoModel.getJugadorActual().toString() + juegoModel.getCasillaActual().toString());
  } 
}
