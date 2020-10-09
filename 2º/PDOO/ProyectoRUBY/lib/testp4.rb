# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
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
  class Testp4
    uno = Jugador.newJugador("uno")
    sorpresa = S_jugadorEspeculador.new(500)
    lista =[]
    lista<<uno  
    
    propiedad = TituloPropiedad.new("Praga", 760, 1.5, 750, 1750, 550);
    
    lista[0].comprar(propiedad);
    
    puts(lista[0].to_s);
    
    sorpresa.aplicarAJugador(0, lista);
    
    puts(lista[0].to_s);
    
    lista[0].debeSerEncarcelado();
    lista[0].encarcelar(1);
    puts(lista[0].to_s);
  end
end