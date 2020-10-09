#encoding:utf-8
#require_relative 'operaciones_juego'
require 'io/console'
#require_relative "salidas_carcel.rb"
#require_relative"gestiones_inmobiliarias.rb"
#require_relative"jugador.rb"
require_relative"respuestas.rb"
module Civitas
  class Vista_textual
    def initialize
      @iGestion=0
      @iPropiedad=0
      @juegoModel
    end
    def mostrar_estado(estado)
      puts estado
    end  
    def pausa
      print "Pulsa una tecla"
      STDIN.getch
      print "\n"
    end

    def lee_entero(max,msg1,msg2)
      ok = false
      begin
        print msg1
        cadena = gets.chomp
        begin
          if (cadena =~ /\A\d+\Z/)###
            numero = cadena.to_i
            ok = true
          else
            raise IOError 
          end
        rescue IOError
          puts msg2
        end
        if (ok)
          if (numero >= max)
            ok = false
          end
        end
      end while (!ok)

      return numero
    end
    def menu(titulo,lista) 
      tab = "  "
      puts titulo
      index = 0
      lista.each { |l|
        puts tab+index.to_s+"-"+l.to_s
        index += 1
      }

      opcion = lee_entero(lista.length,
                          "\n"+tab+"Elige una opcion: ",
                          tab+"Valor erroneo")
      return opcion
    end    
    def comprar
      if(@juegoModel.getCasillaActual.instance_of?(C_calle))
        if(@juegoModel.getCasillaActual.tituloPropiedad.propietario!=nil)then 
          puts("Esta casilla no se puede comprar")
          cadena=Respuestas::NO 
          return cadena
        end
        lista=[Respuestas::NO,Respuestas::SI]
        num=menu("#{@juegoModel.getJugadorActual.nombre}, ¿Quiere comprar la propiedad #{@juegoModel.getCasillaActual.nombre}?", lista)
        cadena=lista[num]
      else
        puts("Esta casilla no se puede comprar")
        cadena=Respuestas::NO
      end
      return cadena
    end
    def gestionar
        cadena="Que tipo de gestion inmobiliaria desearealizar: "
        lista1=[GestionesInmobiliarias::VENDER, GestionesInmobiliarias::HIPOTECAR, GestionesInmobiliarias::CANCELAR_HIPOTECA, GestionesInmobiliarias::CONSTRUIR_CASA, GestionesInmobiliarias::CONSTRUIR_HOTEL, GestionesInmobiliarias::TERMINAR]
        @iGestion=lista1[menu(cadena,lista1)]
        lista2=[]
        cadena="Que propiedad quiere gestionar: "
        if(@iGestion==GestionesInmobiliarias::CANCELAR_HIPOTECA)then
          propiedades=@juegoModel.getJugadorActual().propiedades
          propiedades.each do |propiedad|
            if(propiedad.hipotecado==true)then
              lista2<<propiedad
            end
          end
          if(lista2.size==0)
            @iPropiedad=-1
          else
            @iPropiedad=menu(cadena, lista2)
          end
        elsif(@iGestion==GestionesInmobiliarias::HIPOTECAR) 
          propiedades=@juegoModel.getJugadorActual().propiedades
          propiedades.each do |propiedad|
            if(propiedad.hipotecado==false)then
              lista2<<propiedad
            end
          end
          @iPropiedad=menu(cadena, lista2)
        elsif(@iGestion==GestionesInmobiliarias::VENDER)
          propiedades=@juegoModel.getJugadorActual().propiedades
          propiedades.each do |propiedad|
              lista2<<propiedad
          end
          @iPropiedad=menu(cadena, lista2)
        elsif(@iGestion==GestionesInmobiliarias::CONSTRUIR_CASA)
          propiedades=@juegoModel.getJugadorActual().propiedades
          propiedades.each do |propiedad|
            lista2<<propiedad
          end
          @iPropiedad=menu(cadena, lista2)        
        elsif(@iGestion==GestionesInmobiliarias::CONSTRUIR_HOTEL)
          propiedades=@juegoModel.getJugadorActual().propiedades
          propiedades.each do |propiedad|
              lista2<<propiedad
          end
          @iPropiedad=menu(cadena, lista2)   
        elsif(@iGestion==GestionesInmobiliarias::TERMINAR)then
           @iPropiedad=-1
        end 
    end
    def getGestion
      return @iGestion
    end
    def getPropiedad
      return @iPropiedad
    end

    def mostrarSiguienteOperacion(operacion)
      puts("La siguiente operacion es #{operacion}")
    end

    def mostrarEventos
      while(Diario.instance.eventos_pendientes==true) 
        puts(Diario.instance.leer_evento)
      end
    end

    def setCivitasJuego(civitas)
         @juegoModel=civitas
         self.actualizarVista
    end

    def actualizarVista
      puts("----------------------Actualizar vista----------------------------")
      jugador=@juegoModel.getJugadorActual
      casilla=@juegoModel.getCasillaActual
      puts(jugador.to_s)
      puts(casilla.to_s)
      puts("------------------------------------------------------------------")
      #muestra informacion del jugador actual, sus propiedades y la casilla
    end
    def salirCarcel()
      lista=[SalidasCarcel::TIRANDO, SalidasCarcel::PAGANDO]
      num=menu("¿Como prefiere salir de la carcel?",lista)
      cadena=lista[num]
      return cadena
    end
    
    
  end

end
