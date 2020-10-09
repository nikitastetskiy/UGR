# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative"sorpresa.rb"
require_relative"jugador.rb"
require_relative"jugador_especulador.rb"

module Civitas
  class S_jugadorEspeculador<Sorpresa
    def initialize(valor)
      super("Diosito te ha elegido, ahora eres un iluminaty por un modico precio")
      @valor=valor
    end
    def aplicarAJugador(actual, todos)
      if(jugadorCorrecto(actual, todos))
        informe(actual, todos)
        especulador=JugadorEspeculador.nuevo_especulador(todos[actual], @valor)
        todos[actual]=especulador
      end
    end
  end
end