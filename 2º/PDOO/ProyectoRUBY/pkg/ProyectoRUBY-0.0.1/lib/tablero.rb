# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "casilla.rb"
class Tablero
  def initialize(numCasillaCarcel=1, casillas=[], porSalida=0, tieneJuez=false)
    if numCasillaCarcel<1
      @numCasillaCarcel=1
    end
    @casillas=casillas
    @casillas<<"Salida"
    @porSalida=porSalida
    @tieneJuez=tieneJuez
  end
  def correcto
    if(@numCasillaCarcel<@casillas.size() and tieneJuez==true)
      return true
    else
      return false
    end
  end

  def correcto(numCasilla)
    if(correcto and @numCasilla<@casillas.size)
      return true
    else
      return false
    end
  end
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
      @casillas<<'Cárcel'
      @casillas<<casilla
    else  
      @casillas<<casilla
    end
  end
  def añadeJuez
    if(@tieneJuez==false)
      @casillas<<'Juez'
      @tieneJuez=true
    end
  end
  def getCasilla(numCasilla)
    if(correcto(numCasilla))
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
end
