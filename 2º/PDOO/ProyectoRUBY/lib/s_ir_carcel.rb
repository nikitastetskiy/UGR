# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative"sorpresa.rb"
require_relative"jugador.rb"

module Civitas
  class S_irCarcel<Sorpresa
    def initialize(tablero)
      super("Vas a la carcel")
      @tablero=tablero
    end
    def aplicarAJugador(actual, todos)
      super.informe(actual,todos)
      todos[actual].encarcelar(@tabla.numCasillaCarcel)
    end
    def to_s
      aux=super
      return aux
    end

  end
end