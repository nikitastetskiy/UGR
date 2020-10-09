# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
#require_relative"operacion_inmobiliaria.rb"
module Civitas
  class Controlador
    def initialize(juego, vista)
      @juego=juego
      @vista=vista
    end
    def juega
      @vista.setCivitasJuego(@juego)
      while(@juego.finalDelJuego==false)
        @vista.actualizarVista        
        @vista.pausa
        operacion=@juego.siguientePaso
        @vista.mostrarSiguienteOperacion(operacion)
        if(operacion==Operaciones_juego::PASAR_TURNO)then
          puts("*******************")
          @vista.mostrarEventos
          puts("*******************")
        end
        if(@juego.finalDelJuego==false)then
          if(operacion==Operaciones_juego::COMPRAR)then
           # if(@juego.getCasillaActual.tipo==TipoCasilla::CALLE)then
              resul=@vista.comprar
              if(resul==Respuestas::SI)then
                @juego.comprar
              end
            #else
            #  puts("Esta casilla no se puede comprar")
            #end  
            @juego.siguientePasoCompletado(operacion)####
          elsif(operacion==Operaciones_juego::GESTIONAR)
            @vista.gestionar
            gesti=@vista.getGestion
            propi=@vista.getPropiedad
            operacionIm=OperacionInmobiliaria.new(gesti, propi)
            if(operacionIm.getGestion()==GestionesInmobiliarias::CANCELAR_HIPOTECA)then
              @juego.cancelarHipoteca(propi)
            elsif(operacionIm.getGestion()==GestionesInmobiliarias::CONSTRUIR_CASA)then
              @juego.construirCasa(propi)
            elsif(operacionIm.getGestion()==GestionesInmobiliarias::CONSTRUIR_HOTEL)then  
              @juego.construirHotel(propi)
            elsif(operacionIm.getGestion()==GestionesInmobiliarias::HIPOTECAR)then
              @juego.hipotecar(propi)
            elsif(operacionIm.getGestion()==GestionesInmobiliarias::VENDER)then
              @juego.vender(propi)
            elsif(operacionIm.getGestion()==GestionesInmobiliarias::TERMINAR)then
              @juego.siguientePasoCompletado(operacion)
            end  
          elsif(operacion==Operaciones_juego::SALIR_CARCEL)  
            tiposal=@vista.salirCarcel
            if(tiposal==SalidasCarcel::PAGANDO)then
              @juego.salirCarcelPagando
            elsif(tiposal==SalidasCarcel::TIRANDO)then 
              @juego.salirCarcelTirando
            end
          end
        end
      end
      rerank=@juego.ranking
      if(rerank.size==4)then
        puts("El resultado del juego es el siguiente: 1º#{rerank[0].nombre}---2º#{rerank[1].nombre}---3º#{rerank[2].nombre}---4º#{rerank[3].nombre}")
      elsif(rerank.size==3)then
        puts("El resultado del juego es el siguiente: 1º#{rerank[0].nombre}---2º#{rerank[1].nombre}---3º#{rerank[2].nombre}")
      elsif(rerank.size==2)then
        puts("El resultado del juego es el siguiente: 1º#{rerank[0].nombre}---2º#{rerank[1].nombre}")
      else
        puts("El ranking del final del juego en controlador ha fallado")
      end
    end
  end
end
