# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "casilla.rb"
require_relative "jugador.rb"

module Civitas
  class C_impuesto<Casilla
    def initialize(nombre, cantidad)
      super(nombre)
      @cantidad=cantidad
    end
    def  to_s
      devolver=super()
      devolver+="\n\tSu impuesto es de #{@cantidad}"
      devolver+="\n}\n"
      return devolver;
    end  
    def recibeJugador(actual, todos)
      if(actual<=todos.size && actual>0) then
        super.informe(actual, todos)
        return todos[actual].pagaImpuesto(@importe)
      end
      return false
    end
  end
end