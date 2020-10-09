# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative"jugador.rb"

module Civitas
  class JugadorEspeculador<Jugador
    @@factorEspeculador=2
    def initialize(fianza)
      @fianza=fianza
    end
    def self.nuevo_especulador(jugador, fianza)
      especulador=JugadorEspeculador.new(fianza)
      especulador.nombre = jugador.nombre
      especulador.encarcelado=jugador.encarcelado
      especulador.numCasillaActual=jugador.numCasillaActual
      especulador.puedeComprar=jugador.puedeComprar
      especulador.saldo=jugador.saldo
      especulador.salvoconducto=jugador.salvoconducto
      especulador.propiedades=jugador.propiedades
      for i in especulador.propiedades
        i.actualizaPropietarioPorConversion(self)
      end
      return especulador
    end
    def to_s
      devuelve=super
      devuelve=devuelve+"\tEs un Jugador Especulador"
      return devuelve
    end

  end
end