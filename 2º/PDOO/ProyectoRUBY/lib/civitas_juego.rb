# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "gestor_estados.rb"
require_relative "dado.rb"
require_relative"jugador.rb"
require_relative"s_ir_carcel.rb"
require_relative"s_salir_carcel.rb"
require_relative"s_por_jugador.rb"
require_relative"s_por_casa_hotel.rb"
require_relative"s_ir_casilla.rb"
require_relative"s_pagar_cobrar.rb"
require_relative"s_jugador_especulador.rb"

module Civitas
  class CivitasJuego
  @@Dado=Dado.instance
  def initialize(nombres)
    @jugadores=[]
      if(nombres.size()>4)then
        for i in nombres.size()
          nombres.remove(i);
        end
      end
      nombres.each do |nombre|
        @jugadores<<Jugador.newJugador(nombre)
      end   
    @gestorEstados=Gestor_estados.new
    @estado=@gestorEstados.estado_inicial
    @mazo=MazoSorpresas.new()
    @tablero=Tablero.new(1)
    @indiceJugadorActual=@@Dado.quienEmpieza(@jugadores.size)
    inicializaMazoSorpresas(@tablero)
    inicializaTablero(@mazo)   
  end
  def ranking()
      devuelve=[]
      des=@jugadores
      uno=nil
      @jugadores.each do |aux|
        max=aux
        des.each do |aux2|
          uno=aux
          if(max.compareTo(uno)==1)then
              max=uno;  
          end
        end
        if(des.size>2)
          des.delete(max)
          devuelve<<max
        else 
          devuelve<<max
        end
      end
    return devuelve;
  end   
  def cancelarHipoteca(ip)
    return @jugadores[@indiceJugadorActual].cancelarHipoteca(ip)
  end 
  def comprar
    jugadorActual=@jugadores[@indiceJugadorActual]
    numCasillaActual=jugadorActual.getNumCasillaActual
    casilla=@tablero.getCasilla(numCasillaActual)
    titulo=casilla.tituloPropiedad
    res=jugadorActual.comprar(titulo)
    return res
  end
  def construirCasa(ip)
    return @jugadores[@indiceJugadorActual].construirCasa(ip)
  end
  
  def construirHotel(ip)
    return @jugadores[@indiceJugadorActual].construirHotel(ip)
  end
  
  def finalDelJuego
    for i in 0..@jugadores.size()-1
         if(@jugadores[i].enBancarrota()==true)
             return true
         end
    end
    return false
  end
  
  def getCasillaActual
    return @tablero.getCasilla(@jugadores[@indiceJugadorActual].getNumCasillaActual)
  end
  
  def getJugadorActual
     return @jugadores[@indiceJugadorActual]
  end
  
  def hipotecar(ip)
    return @jugadores[@indiceJugadorActual].hipotecar(ip)
  end
  
  def infoJugadorTexto
    return @jugadores[@indiceJugadorActual].toString()
  end
  
  def salirCarcelPagando
    return @jugadores[@indiceJugadorActual].salirCarcelPagando()
  end
  
  def salirCarcelTirando
    return @jugadores[@indiceJugadorActual].salirCarcelTirando()
  end
  
  def siguientePasoCompletado(operacion)
    @estado=@gestorEstados.siguiente_estado(@jugadores[@indiceJugadorActual], @estado, operacion)
  end
  
  def vender(ip)
    return @jugadores[@indiceJugadorActual].vender(ip)
  end
   def to_string
    @jugadores[@indiceJugadorActual].to_s
  end
  def siguientePaso
    jugadorActual=@jugadores[@indiceJugadorActual]
    operacion=@gestorEstados.operaciones_permitidas(jugadorActual,@estado)
    if(operacion==Operaciones_juego::PASAR_TURNO)then
      pasarTurno
      siguientePasoCompletado(operacion)
    elsif(operacion==Operaciones_juego::AVANZAR)then  
      avanzaJugador
      siguientePasoCompletado(operacion)
    end
    return operacion
  end
  private
  def contabilizarPasosPorSalida(jugadorActual)
     while (@tablero.getPorSalida()>0)
       jugadorActual.pasaPorSalida();
     end
  end 
  
  def actualizarInfo
    mostrar=getJugadorActual.to_s
    puts(mostrar)
  end
  
  def inicializaTablero(mazo)
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Praga",650, 1.5,750,1750,550)))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Granada",750, 1.15,600,1900,250)))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Moraleda de Zafayona",800, 1.1,730,1900,370)))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("San Pedro de Alcantara",560, 1.05,480,1980,420)))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Conil",640, 1.3,590,1700,260)))
    @tablero.añadeJuez
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Budapest",900,1.4,800,1730,680)))
    @tablero.añadeCasilla(C_sorpresa.new(mazo, "Sorpresa"))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Tarragona",780,1.16,700,1560,410)))
    @tablero.añadeCasilla(C_sorpresa.new(mazo,"Sorpresa_2"))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Benalmadena",500,1.45,390,1150,320)))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Almagro",890,1.04,770,1690,520)))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Sevilla",730,1.7,690,1980,490)))
    @tablero.añadeCasilla(C_impuesto.new(1000,"Impuesto"))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Palenciana",1000,1.2,950,1800,750)))
    @tablero.añadeCasilla(C_sorpresa.new(mazo,"Sorpresa_3"))
    @tablero.añadeCasilla(C_calle.new(TituloPropiedad.new("Malaga",600,1.9,480,1380,390)))
    @tablero.añadeCasilla(Casilla.new("Parking"))
  end  
  
  def inicializaMazoSorpresas(tablero)
    @mazo.alMazo(S_irCarcel.new(tablero))
    @mazo.alMazo(S_salirCarcel.new(@mazo))
    @mazo.alMazo(S_porJugador.new(250,"Es tu cumpleaños y tus amigos no pueden ir sin un regalo, cada jugador te paga 250"))
    @mazo.alMazo(S_porJugador.new(-300,"¿Oyes eso? creo que son los matones de tus acreedores llamando a la puerta, pagas a cada jugador 300"))
    @mazo.alMazo(S_porCasaHotel.new(50,"El banco te ha cobrado la clausula suelo y un abogado te ha conseguido un buen trato, ganas 50 por cada casa y hotel"))
    @mazo.alMazo(S_porCasaHotel.new(-50,"Un tifon ha causado serios daños en tus propiedades, pagas 50 por cada casa y hotel"))
    @mazo.alMazo(S_irCasilla.new(tablero,4, "Me han dicho que Moraleda esta muy bonita en esta epoca del año, te desplazas a moraleda"))
    @mazo.alMazo(S_irCasilla.new(tablero, 14,"Tu primo se ha operado deberias ir a verle, te desplazas a Sevilla"))
    @mazo.alMazo(S_irCasilla.new(tablero,6, "¡Tu hermana acaba de dar a luz!, te desplazas a Conil"))
    @mazo.alMazo(S_pagarCobrar.new(500, "Participas en el pasapalabra y empatas(ni tu te lo crees), te llevas 500"))
    @mazo.alMazo(S_pagarCobrar.new(-500,"Has roto la Playstation de tu amigo, deberias meterte las manos en los bolsillos, pagas 500"))
    @mazo.alMazo(S_jugadorEspeculador.new(1000))
  end  
  
  def pasarTurno
    if((@indiceJugadorActual+1)>=@jugadores.size)
            @indiceJugadorActual=0
    else
            @indiceJugadorActual+=1
    end
  end
  def avanzaJugador()
    jugadorActual=@jugadores[@indiceJugadorActual]
    posicionActual=jugadorActual.getNumCasillaActual
    tirada=@@Dado.tirar
    posicionNueva=@tablero.nuevaPosicion(posicionActual,tirada)
    casilla=@tablero.getCasilla(posicionNueva)
    contabilizarPasosPorSalida(jugadorActual)
    jugadorActual.moverACasilla(posicionNueva)
    casilla.recibeJugador(@indiceJugadorActual,@jugadores)
    contabilizarPasosPorSalida(jugadorActual)
  end
  attr_reader :jugadores ,:gestorEstados, :estado, :mazo, :tablero, :indiceJugadorActual, :gestorEstados
  private :jugadores, :gestorEstados, :estado, :mazo, :tablero, :indiceJugadorActual, :gestorEstados 
  end
end

