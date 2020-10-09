# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative"jugador.rb"
require_relative"sorpresa.rb"

module Civitas
  class S_porCasaHotel<Sorpresa
    def initialize(valor, texto)
      super(texto)
      @valor=valor
    end
    def aplicarAJugador(actual, todos)
      super.informe(actual, todos)
      todos[actual].modificarSaldo(@valor*todos[actual].cantidadCasaHoteles())
    end
    def to_s
      aux=super
      return aux
    end  
  end
end