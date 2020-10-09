# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas
  class Sorpresa
    def initialize(texto="sorpresa")
      @texto=texto
    end
    def jugadorCorrecto(actual,todos)
      if(actual<=todos.size)then
        return true
      else
        return false
      end
    end
    def setValor(nuevo)
        @valor=nuevo
    end
    attr_reader :tipoSorpresa
    attr_reader :texto
    attr_reader :valor
    attr_reader :tabla
    attr_reader :mazito
    def salirDelMazo
      if(getTipoSorpresa()==TipoSorpresa.IRCARCEL)then
        @mazito.inhabilitarCartaEspecial(this)
      end
    end
    def to_s
      return @texto
    end
    def informe(actual, todos)
      if(jugadorCorrecto(actual, todos))then
        evento="Al jugador "+ todos[actual].getNombre()
        evento=evento+" se le aplicara la sorpresa #{texto}"       
        Diario.instance.ocurre_evento(evento)
      end
    end
    private :texto, :valor, :tabla, :tipoSorpresa, :mazito
  end
end
