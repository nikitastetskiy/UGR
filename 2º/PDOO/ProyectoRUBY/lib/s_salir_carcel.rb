# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative"sorpresa.rb"
require_relative"mazo_sorpresas.rb"
require_relative"jugador.rb"

module Civitas
  class S_salirCarcel<Sorpresa
    def initialize(mazo)
      super("Sales de la carcel")
      @mazo=mazo
    end
    def aplicarAJugador(actual, todos)
      super.informe(actual, todos)
      boolean salvado=false
      for i in todos.size()
        salvado=todos[i].tieneSalvoconducto()
      end
      if(salvado)then
        todos[actual].obtenerSalvoconducto(this)
        this.salirDelMazo()
      end
    end
    def usada
      @mazito.habilitarCartaEspecial(this)
    end  
    def to_s
      aux=super
      return aux
    end  
  end
end