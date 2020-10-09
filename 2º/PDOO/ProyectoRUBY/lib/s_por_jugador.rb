# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "jugador.rb"
require_relative"sorpresa.rb"

module Civitas
  class S_porJugador<Sorpresa
    def initialize(valor, texto)
      super(texto)
      @valor=valor
    end
    def aplicarAJugador(actual, todos)
      super.informe(actual, todos)
      te="Pagar al jugador "+actual
      s=Sorpresa.new(TipoSorpresa.PAGARCOBRAR, (@valor*(-1)), te);
      for i in todos.size
        if(i==actual)then
        else
            s.aplicarAJugador_pagarCobrar(i, todos);
        end
      end
      s.setValor(@valor*(todos.size()-1));
      for i in todos.size
        if(i==actual)then
          s.aplicarAJugador_pagarCobrar(i, todos);
        else
        end
      end
    end
    def to_s
      aux=super
      return aux
    end  
  end
end