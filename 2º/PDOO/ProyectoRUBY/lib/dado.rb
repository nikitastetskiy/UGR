# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require 'singleton'
#require_relative "diario.rb"
module Civitas
  class Dado
    include Singleton
    def tirar
      if(@debug==false)
        @random=rand(6)+1
        @random=@random.to_i
        @ultimoResultado=1+@random
        return @ultimoResultado
      else
        @ultimoResultado=1
        return @ultimoResultado
      end
    end
    def salgoDeLaCarcel
      if(tirar>=5)
        return true
      else
        return false
      end
    end
    def quienEmpieza(n)
      @random=rand(n)
      @random=@random.to_i
      return @random
    end
    def setDebug(d)
      @debug=d
      e=@debug==true ? "Debug->true":"Debug->false"
      Diario.instance.ocurre_evento(e)
    end
    attr_reader :ultimoResultado, :debug, :random, :SalidaCarcel, :instance
    private :debug, :random, :ultimoResultado
    private :SalidaCarcel, :instance
    private
    def initialize()
      @random=rand()
      @ultimoResultado=1
      @debug=true
      @SalidaCarcel=5
    end
  end
end
