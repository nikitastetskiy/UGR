# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
  class TituloPropiedad
    def initialize(nom, ab, fr, hb, pc, pe)
      @factorInteresesHipoteca= 1.1
      @nombre=nom
      @alquilerBase=ab
      @factorRevalorizacion=fr
      @hipotecaBase=hb
      @precioCompra=pc
      @precioEdificar=pe
      @propietario=nil
      @numCasas=0
      @numHoteles=0
      @hipotecado=false
    end
    attr_reader :hipotecado
    attr_reader :nombre
    attr_reader :numCasas
    attr_reader :numHoteles
    attr_reader :precioCompra
    attr_reader :precioEdificar
    attr_reader :propietario
    def precioCompra
      return @precioCompra
    end
    def numCasas
      return @numCasas
    end
    def nombre
      return @nombre
    end
    def getImporteCancelarHipoteca
      return (@hipotecaBase*@factorInteresesHipoteca)
    end
    def cancelarHipoteca(jugador)
      if(@hipotecado==true && esEsteElPropietario(jugador)==true)then
        jugador.paga(@alquilerBase*(1+(@numCasas*0.5)+(@numHoteles*2.5))*0.1)
        @hipotecado=false
        return true
      else
        return false
      end
    end
    def hipotecar(jugador)
      if(@hipotecado==false && esEsteElPropietario(jugador)==true)then
        jugador.recibe(@alquilerBase*(1+(@numCasas*0.5)+(@numHoteles*2.5)))
        @hipotecado=true
        return true
      else
        return false
      end
    end
    def tramitarAlquiler(jugador)
      if(tienePropietario()==true && @propietario!=jugador)then
        @precioAlquiler=(alquilerBase*(1+(@numCasas*0.5)+(@numHoteles*2.5)))
        jugador.pagaAlquiler(@precioAlquiler)
        @propietario.recibe(@precioAlquiler)
      end
    end
    def cantidadCasaHoteles
      return (@numCasas+@numHoteles)
    end
    def derruirCasas(n, jugador)
      if(esEsteElPropietario(jugador)==true && n<=@numCasas)then
        @numCasas=@numCasas-n
        return true
      else
        return false
      end
    end
    def construirCasa(jugador)
      if(esEsteElPropietario(jugador)==true)then
        jugador.paga(@precioEdificar)
        @numCasas=@numCasas+1
        return true
      else
        return false
      end 
    end
    def construirHotel(jugador)
      devuelve=false
      if(esEsteElPropietario(jugador)==true)then
          jugador.paga(@precioEdificar)
          @numHoteles=@numHoteles+1
          devuelve=true
          return devuelve
      else
          return devuelve
      end 
    end
    def comprar(jugador)
      if(tienePropietario()==true)then
        return false
      else
        @propietario=jugador
        jugador.paga(@precioCompra)
        return true
      end
    end
    def actualizaPropietarioPorConversion(jugador)
      if(esEsteElPropietario(jugador)==false)then
        @propietario=jugador
      end
    end
    def tienePropietario
      if(@propietario==nil)then
        return false
      else
        return true
      end

    end
    def vender(jugador)
      if(esEsteElPropietario(jugador)==true)then
        @propietario.recibe(@precioCompra+@precioEdificar*cantidadCasaHoteles*@factorRevalorizacion)
        jugador.paga(@precioCompra+@precioEdificar*cantidadCasaHoteles*@factorRevalorizacion)
        @propietario=nil
        return true
      else
        return false
      end
    end
    def to_s
      devuelve="TituloPropiedad{\n"
      devuelve+="\tNombre #{@nombre}. \n\tAlquiler base: #{@alquilerBase}. \n\tInteres hipoteca: #{@factorInteresesHipoteca}. \n\tFactor revalorizacion: #{@factorRevalorizacion}. \n\tHipoteca base: #{@hipotecaBase}. \n\t" 
      if(@hipotecado==true)then
        devuelve+="Esta hipotecado"
      else
        devuelve+="No esta hipotecado"
      end
      devuelve+=". El titulo tienen #{@numCasas} casas y #{@numHoteles} hoteles. Precio edificacion: #{@precioEdificar}.Precio compra: #{@precioCompra}"
      devuelve+="\n}\n"
      return devuelve
    end
    private    
    def getPrecioVenta
      precio=@precioCompra+(@precioEdificar*cantidadCasasHoteles)*@factorRevalorizacion
      return precio
    end
    def getPrecioAlquiler
      if(@hipotecado || @propietario.isEncarcelado())then
        return 0
      else
        return (@alquilerBase*(1+(@numCasas*0.5)+(@numHoteles*2.5)))
      end
    end
    def esEsteElPropietario(jugador)
      return @propietario==jugador  
    end
    def getImporteHipoteca
      return importeHipoteca
    end
    def  propietarioEncarcelado
      return @propietario.isEncarcelado
    end  
    attr_reader :factorInteresesHipoteca, :factorRevalorizacion
    attr_reader :alquilerBase, :hipotecaBase
  end
end