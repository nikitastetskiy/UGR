# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "casilla.rb"
require_relative"c_calle.rb"
require_relative"c_impuesto.rb"
require_relative"c_juez.rb"
require_relative"c_sorpresa.rb"

module Civitas
  class Tablero
    attr_reader :numCasillaCarcel
    def getPorSalida
      if(@porSalida>0)
        vari=@porSalida +1
        @porSalida=vari
        return @porSalida
      else
        return @porSalida
      end
    end
    def añadeCasilla(casilla)
      if(@casillas.size==@numCasillaCarcel)
        casilla2=Casilla.new('Carcel')
        @casillas<<casilla2
        @casillas<<casilla
      else  
        @casillas<<casilla
      end
    end
    def añadeJuez
      if(@tieneJuez==false)
        casilla=C_juez.new(@numCasillaCarcel,"Juez")
        @casillas<<casilla
        @tieneJuez=true
      end
    end
    def getCasilla(numCasilla)
      if(correcto(numCasilla)==true)
        return @casillas[numCasilla]
      else
        return nil
      end
    end
    def nuevaPosicion(actual, tirada)
      nueva=actual+tirada
      if(nueva<@casillas.size)
        return nueva
      else
        nueva=nueva%@casillas.size
        var=@porSalida+1
        @porSalida=var
        return nueva
      end
    end
    def calcularTirada(origen, destino)
      tirada=destino-origen
      if(tirada<0)
        tirada=tirada+20
      end
      return tirada
    end
    public
    def initialize(numCasillaCarcel=1, casillas=[], porSalida=0, tieneJuez=false)
      if numCasillaCarcel<1 then
        @numCasillaCarcel=1
      else
        @numCasillaCarcel=numCasillaCarcel
      end
      @casillas=casillas
      @casillas<<"Salida"
      @porSalida=porSalida
      @tieneJuez=tieneJuez
    end
    attr_reader :tieneJuez
    attr_reader :porSalida
    private
    def correctoA
      if(@numCasillaCarcel<@casillas.size() and @tieneJuez==true)then
        return true
      else
        return false
      end
    end
    def correcto(numCasilla)
      if(correctoA==true and numCasilla<@casillas.size)then
        return true
      else
        return false
      end
    end
    private :tieneJuez, :porSalida
  end
end