# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "sorpresa.rb"
require_relative "jugador.rb"

module Civitas
  class S_irCasilla<Sorpresa
    def initialize(tablero, valor, texto)
      super(texto)
      @tablero=tablero
      @valor=valor
    end
    def aplicarAJugador(actual, todos)
      super.informe(actual, todos)
      casi=todos[actual].getNumCasillaActual()
      nueva=@tabla.calcularTirada(casi, @valor)
      nueva=@tabla.nuevaPosicion(casi,nueva)
      todos[actual].moverACasilla(nueva)
      recibeJugador(actual,todos);
    end
    def to_s
      aux=super
      return aux
    end    
end
end