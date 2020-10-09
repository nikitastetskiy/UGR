# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "casilla.rb"
require_relative "jugador.rb"

module Civitas
  class C_sorpresa<Casilla
    def initialize(mazo, nombre)
      super(nombre)
      @mazo=mazo
    end
    def  to_s
      devolver=super()
      devolver+="\n}\n"
      return devolver;
    end  
    def recibeJugador(iactual, todos)
      if(jugadorCorrecto(iactual,todos))then
        sorpresa=@mazo.siguiente
        super.informe(iactual,todos)
        sorpresa.aplicarAJugador(iactual, todos)
      end
    end

  end
end