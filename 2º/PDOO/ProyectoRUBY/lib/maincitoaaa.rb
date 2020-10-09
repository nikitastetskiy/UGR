#encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require 'io/console'
require_relative"casilla.rb"
require_relative"dado.rb"
require_relative"diario.rb"
require_relative"estados_juego.rb"
require_relative"gestiones_inmobiliarias.rb"
require_relative"gestor_estados.rb"
require_relative"operacion_inmobiliaria.rb"
require_relative"operaciones_juego.rb"
require_relative"respuestas.rb"
require_relative"salidas_carcel.rb"
require_relative"sorpresa.rb"
require_relative"titulo_propiedad.rb"

require_relative "tablero.rb"
require_relative "diario.rb"
require_relative "mazo_sorpresas.rb"
require_relative "sorpresa.rb"
require_relative "jugador.rb"
require_relative "civitas_juego.rb"
require_relative "vista_textual.rb"
require_relative "controlador.rb"
module Civitas
  class Maincitoaaa
      jugadores=[]
      puts("Escribe el numero de jugadores(de 2 a 4): \n")
      numJugadores=gets.chomp.to_i
      while(numJugadores<2 or numJugadores>4)
        puts("Escribe el numero de jugadores (de 2 a 4): \n")
        numJugadores=gets.chomp.to_i
      end
      i=0
      while(i<numJugadores)
        puts("Nombre del jugador #{i+1}")
        nombre=gets
        jugadores<<nombre
        i+=1
      end
      juego=CivitasJuego.new(jugadores)
      vista=Vista_textual.new
      Dado.instance.setDebug(true)
      controlador=Controlador.new(juego, vista)
      controlador.juega
  end
end
