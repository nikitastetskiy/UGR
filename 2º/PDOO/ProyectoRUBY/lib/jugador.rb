# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
  class Jugador
    @@CasasMax=4
    @@CasasPorHotel=4
    @@HotelesMax=4
    @@PasoPorSalida=1000
    @@PrecioLibertad=200
    @@SaldoInicial=7500
    def initialize(nombre, encarcelado, numCasillaActual, puedeComprar, saldo, salvoconducto, propiedades)
      @nombre=nombre
      @encarcelado=encarcelado
      @numCasillaActual=numCasillaActual
      @puedeComprar=puedeComprar
      @saldo =saldo
      @salvoconducto=salvoconducto
      @propiedades=propiedades
    end
    attr_reader :propiedades
    attr_reader :salvoconducto
    attr_reader :SaldoIncial
    attr_reader :PrecioLibertad
    attr_reader :CasasMax
    attr_reader :HotelesMax
    attr_reader :PasoPorSalida
    attr_reader :nombre, :numCasillaActual, :puedeComprar, :saldo, :encarcelado
    attr_writer :nombre,  :puedeComprar, :saldo, :encarcelado, :numCasillaActual,:salvoconducto, :propiedades
    def self.newJugador(otro)
      new(otro.nombre, otro.encarcelado, otro.numCasillaActual, otro.puedeComprar, otro.saldo, otro.salvoconducto, otro.propiedades)
    end
    def enBancarrota
      if(@saldo > 0)then
        return false;
      else
        return true;
      end
    end
    def self.newJugador(nombre)
      new(nombre, false, 0, false, @@SaldoInicial, nil, [])
    end
    def getNumCasillaActual
      return @numCasillaActual
    end    
    def propiedades
      return @propiedades
    end
    def cancelarHipoteca(ip)
      result=false
      if(@encarcelado==true)then
          return result
      end
      if(existeLaPropiedad(ip))then
          propiedad=@propiedades[ip]
          cantidad=propiedad.getImporteCancelarHipoteca
          puedoGastar=puedoGastar(cantidad)
          if(puedoGastar==true)then
              result=propiedad.cancelarHipoteca(self)
              if(result==true)then
                  Diario.instance.ocurre_evento("El jugador #{@nombre} cancela la hipoteca de la propiedad #{ip}")
              end
          end
      return result
    end
  end
  def existeLaPropiedad(ip)
    if(@propiedades.size>=ip)
      return true
    else  
      return false
    end
  end
  def hipotecar(ip)
    result=false
    if(@encarcelado==true)then
      return result
    end
    if(existeLaPropiedad(ip))then
      propiedad=@propiedades[ip]
      result=propiedad.hipotecar(self)
    end
    if(result==true)then
      Diario.instance.ocurre_evento("El juego #{@nombre} hipoteca la propiedad #{ip}")
    end
    return result
  end
  def construirCasa(ip)
    result=false
    puedoEdificarCasa=false
    if(@encarcelado==true)then
      return result
    else 
      existe=existeLaPropiedad(ip)
      if(existe==true)then
        propiedad=@propiedades[ip]
        puedoEdificarCasa=puedoEdificarCasa(propiedad)
        precio=propiedad.precioEdificar
        if(puedoGastar(precio) && propiedad.numCasas<@@CasasMax)then
          puedoEdificarCasa=true
        end
        if(puedoEdificarCasa==true)then
          result=propiedad.construirCasa(self)
        end
        if(result==true)then
          Diario.instance.ocurre_evento("El jugador #{@nombre} construye casa en la propiedad #{ip}")
        end
      end
    end
    return result
  end
  def construirHotel(ip)#aqui entra la vergota
    result=false
    if(@encarlado==true)then
      return result
    else  
      propiedad=@propiedades[ip]
      puedoEdificarHotel=puedoEdificarHotel(propiedad)
      if(puedoEdificarHotel==true)then
        result=propiedad.construirHotel(self)
        casasPorHotel=@@CasasPorHotel
        propiedad.derruirCasas(casasPorHotel,self)
      end
      Diario.instance.ocurre_evento("El Jugador #{@nombre} construye hotel en la propiedad #{ip}")
    end
    return result
  end
  def puedoEdificarHotel(propiedad)
    if(cantidadCasaHoteles()<=8)then
      if(propiedad.numHoteles<=4 && propiedad.numCasas==4)then
        if(@saldo>=propiedad.precioEdificar)then
          return true
        else
          return false
        end
      else
        return false;
      end
    else
      return false;
    end
  end
  def cantidadCasaHoteles
    suma=0
    @propiedades.each do |propiedad|
        suma=suma+propiedad.numCasas
        suma=suma+propiedad.numHoteles
    end
    return suma
  end
  def comprar(titulo)
    result=false
    if(titulo.propietario!=nil)then 
      return result
    end
    if(puedeComprarCasilla()==true)then
      precio=titulo.precioCompra
      if(puedoGastar(precio))then
        result=titulo.comprar(self)
        if(result==true)then
          @propiedades<<titulo
          Diario.instance.ocurre_evento("El jugador #{@nombre} compra la propiedad #{titulo.to_s}")
        end
      end
    end
    return result
  end
  def encarcelar(numCasillaCarcel)
       if(debeSerEncarcelado()==true)then
            moverACasilla(numCasillaCarcel)
            @encarcelado=true
            evento="El jugador #{@nombre} va a la carcel";
            Diario.instance.ocurre_evento(evento);
       end
        return @encarcelado
  end
  def obtenerSalvoconducto(s)
    if(@encarcelado==true)then
      return false
    else
      @salvoconducto=s
      return true
    end
  end
  def tieneSalvoconducto
    if(@salvoconducto == nil)then
      return false
    else
      return true
    end
  end
  def puedeComprarCasilla
    if(@encarcelado==true)then
      @puedeComprar=false
    else
      @puedeComprar=true
    end
      return @puedeComprar;       
  end
  def paga(cantidad)
        cantidad=cantidad*(-1)
        return modificarSaldo(cantidad)
  end
  def pagaImpuesto(cantidad)
    if(@encarcelado==true)then 
      return false;
    else
      return paga(cantidad);
    end
  end
  def pagaAlquiler(cantidad)
    if(@encarcelado==true)then
      return false;
    else
      return paga(cantidad);
    end
  end
  def recibe(cantidad)
    if(@encarcelado==true)then
      return false
    else
      return modificarSaldo(cantidad)
    end
  end
  def modificarSaldo(cantidad)
    @saldo=@saldo+cantidad
    return true
  end
  def moverACasilla(numCasilla)
    if(@encarcelado==true)then
      return false
    else
      @numCasillaActual=numCasilla
      @puedeComprar=false
      evento="El jugador #{@nombre} se ha desplazado a la casilla #{@numCasilla}" 
      Diario.instance.ocurre_evento(evento)
      return true
    end
  end
  def vender(ip)
    if(@encarcelado==true)then
      return false;
    else
      if(existeLaPropiedad(ip)==true)then
        if(propiedades[ip].vender(self)==true)then
          @propiedades.vender(self)
          @propiedades.delete_at(ip)         
          evento="El jugador #{@nombre} a vendido la casilla  #{ip}"
          Diario.instance.ocurre_evento(evento)
          return true
        else
          return false
        end
      else
            return false
      end
    end
  end
  def tieneAlgoQueGestionar
    if(@propiedades.size==0)then
      return false
    else
      return true
    end    
  end
  def salirCarcelPagando
    if(puedeSalirCarcelPagando()==true)then
      if(paga(@@PrecioLibertad)==true)then
        @encarcelado=false
        evento="El jugador #{@nombre} a salido de la carcel"
        Diario.instance.ocurre_evento(evento)
        return true
      else
        return false
      end    
    else
      return false
    end
  end
  def salirCarcelTirando
    if(Dado.instance.salgoDeLaCarcel()==true)then
      @encarcelado=false
      evento="El jugador #{@nombre} a salido de la carcel";
      Diario.instance.ocurre_evento(evento);
      return true
    else
      return false
    end
  end
  def pasaPorSalida
    modificarSaldo(PasoPorSalida)
    evento="El jugador #{@nombre} a pasado por la salida"
    Diario.instance.ocurre_evento(evento)
    return true
  end
  attr_reader :CasasPorHotel
  def to_s
    devuelve="Jugador\n"
    devuelve+="Jugador #{@nombre}.\n\t Posee #{@propiedades.size()} propiedades: "
    propiedades.each do |propiedad|
        devuelve=devuelve+"#{propiedad.nombre} "
    end
    #devuelve=devuelve+".\n Actualmente se encuentra "
    #if(@encarcelado==true)then
    #  devuelve+="encarcelado "
    #else
    #  devuelve+=" libre"
    #end
    devuelve+=".\n\tLa casilla actual es #{@numCasillaActual}.\n\tSaldo #{@saldo}.\n"
    #if(tieneSalvoconducto()==true)then
     # devuelve+="Posee salvoconducto."
    #else
    #  devuelve+="No posee salvoconducto." 
   # end
    return devuelve
  end
  def compareTo(otro)
    return self<=>otro  
  end
  def isEncarcelado
    return @encarcelado
  end
  def getNombre
    return @nombre
  end
  def debeSerEncarcelado
    if(@encarcelado==true)then
      return false
    else
      if(tieneSalvoconducto()==true)then
        perderSalvoconducto()
        evento="El jugador #{@nombre} se libra de la carcel"
        Diario.instance.ocurre_evento(evento)
        return false
      else
        return true
      end
    end
  end
  attr_reader :SaldoInicial
  def puedoGastar(precio)
    if(@encarcelado==true)then
      return false
   else
      return @saldo>=precio
    end
  end
  def puedoEdificarCasa(propiedad)
    if(cantidadCasaHoteles()<=8)then
      if(propiedad.numCasas<=4)then
          if(@saldo>=propiedad.precioEdificar)then
              return true
          else
              return false
          end
      else
        return false
      end
    else
      return false
    end
  end
  def puedeSalirCarcelPagando
    return @saldo>=@@PrecioLibertad
  end
  def perderSalvoconducto
    @salvoconducto=nill;
    @salvoconducto.usada();
  end
  def getPuedeComprar
    return @puedeComprar
  end
  def getSaldo
    return @saldo
  end
 end
end