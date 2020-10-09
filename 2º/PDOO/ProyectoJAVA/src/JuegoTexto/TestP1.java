/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package JuegoTexto;

import civitas.Dado;
import civitas.CivitasJuego;
import java.util.ArrayList;
import civitas.Jugador;
import java.util.Scanner;

/**
 *
 * @author nikitastetskiy
 */
public class TestP1 {
   
    public static void main (String [ ] args) {
        
        int num=-1;
        ArrayList<String> nombres = new ArrayList<>();
        Scanner in = new Scanner (System.in);
        
        do{
            System.out.print("Introduce num de jugadores (2-4): ");
            num = in.nextInt();
        }while(num < 2 || num > 4);
        
        in.nextLine();
        
        for (int i=0; i<num; i++){
            System.out.print("Nombre del jugador " + (i+1) + ": ");
            nombres.add(in.nextLine());
        }
        
        CivitasJuego juego = new CivitasJuego(nombres);

        Dado.getInstance().setDebug(Boolean.TRUE);
        VistaTextual vista = new VistaTextual();
        Controlador control = new Controlador(juego, vista);
        
        control.juega();
    }
}
/*


*/

