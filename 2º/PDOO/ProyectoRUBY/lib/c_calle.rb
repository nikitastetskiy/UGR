# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "casilla.rb"
require_relative "titulo_propiedad.rb"
require_relative "jugador.rb"

module Civitas
  class C_calle<Casilla
    def initialize(titulo)
      super(titulo.nombre)
      @tituloPropiedad=titulo
      @importe=titulo.precioCompra
    end
    attr_reader :tituloPropiedad, :importe
    def  to_s
      devolver=super()
      devolver=devolver+ "\n\tSu titulo de propiedad es este: #{@tituloPropiedad.to_s}";
      devolver+="\n}\n"
      return devolver;
    end  
    def recibeJugador(iactual,todos)
        if(jugadorCorrecto(iactual,todos)==true)then
          informe(iactual,todos)
          jugador=todos[iactual]
          if(@tituloPropiedad.tienePropietario==false)then
            jugador.puedeComprarCasilla
          else  
            @tituloPropiedad.tramitarAlquiler(jugador)
          end
        end
      end
  end
end
