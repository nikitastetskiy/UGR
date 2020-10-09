# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "dado.rb"
require_relative "tipo_casilla.rb"
require_relative "tablero.rb"
require_relative "diario.rb"
require_relative "mazo_sorpresas.rb"
require_relative "sorpresa.rb"
module Civitas
  class TestP1
    jugadores=4
    cont1=0
    cont2=0
    cont3=0
    cont4=0
    for i in 1..100
      a=Dado.instance.quienEmpieza(jugadores)
      if(a==0)
        var=cont1+1
        cont1=var
      elsif(a==1)
        var=cont2+1
        cont2=var
      elsif(a==2)
        var=cont3+1
        cont3=var
      elsif(a==3)
        var=cont4+1
        cont4=var
      end
    end
    puts("Los resultados de quienEmpieza son: #{cont1} #{cont2} #{cont3} #{cont4}")
    puts("Debug de dado en true")
    Dado.instance.setDebug(true)
    for i in 1..10
      puts(Dado.instance.tirar)
    end
    puts("Debug de dado en false")
    Dado.instance.setDebug(false)
    for i in 1..10
      puts(Dado.instance.tirar)
    end
    for i in 1..10
      puts(Dado.instance.salgoDeLaCarcel)
      puts(Dado.instance.ultimoResultado)
    end
    #puts(TipoCasilla.values())
    #puts(EstadosJuego.values())
    #puts(TipoSorpresa.values())
    @@mazito=MazoSorpresas.new()
    s=Sorpresa.new()
    s2=Sorpresa.new()
    s3=Sorpresa.new()
    @@mazito.alMazo(s)
    @@mazito.alMazo(s2)
    s3=@@mazito.siguiente
    if(s==s3)
      puts("La siguiente carta es s")
    elsif(s2==s3)
      puts("La siguiente carta es s2")
    else
      puts("La mamaste wei")
    end
    @@mazito.inhabilitarCartaEspecial(s2)
    puts(@@mazito.sorpresas.size)
    puts(@@mazito.cartasEspeciales.size)
    @@mazito.habilitarCartaEspecial(s2)
    puts(@@mazito.sorpresas.size)
    puts(@@mazito.cartasEspeciales.size)
    for i in 1..4
      puts(Diario.instance.leer_evento)
    end
    @@tabla=Tablero.new(3)
    c=Casilla.new("lololololo")
    c2=Casilla.new("momomomomomomomomomom")
    @@tabla.añadeCasilla(c)
    @@tabla.añadeCasilla(c2)
    numero=@@tabla.calcularTirada(1,4)
    puts("Esta es la tirada #{numero}")
    puts("Esta es la nueva posicion #{@@tabla.nuevaPosicion(2,Dado.instance.tirar)}")
  end
end
