# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module  Civitas
  class Casilla
    def initialize(nombre)
      @nombre=nombre  
    end
    attr_reader :nombre
    def  to_s
      devolver="\nCasilla{\n"
      devolver+="\tNombre: #{@nombre}."
      return devolver;
    end
    def jugadorCorrecto(actual, todos)
      if(actual<=(todos.size)) then
        return true
      else
        return false
      end
    end
    def jugadorCorrecto(actual, todos)
      if(actual<=(todos.size)) then
        return true
      else
        return false
      end
    end
    def recibeJugador(actual, todos)
      informe(actual, todos)
    end
    def informe(actual, todos)
      Diario.instance.ocurre_evento("El jugador #{todos[actual].nombre} a caido en la casilla #{@nombre}");
    end 
  end
end
