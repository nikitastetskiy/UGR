# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
  class MazoSorpresas
    def initialize(bol='false')
      init
      @debug=bol
      @ultimaSorpresa
      if(@debug==true)
        e="Debug->true"
        ocurreEvento(e)
      end
    end
    def init()
      @sorpresas=[]
      @cartasEspeciales=[]
      @barajada=false
      @usadas=0
    end
    attr_reader :sorpresas
    attr_reader :cartasEspeciales
    attr_reader :barajada
    attr_reader :debug
    attr_reader :ultimaSorpresa
    attr_reader :usadas
    def alMazo(s)
      if(@barajada==false)
        @sorpresas<<s
      end
    end
    def siguiente
      if(@debug==true)
      else
        if(@barajada==false or @usadas==@sorpresas.size)
          @usadas=0
          @barajada=true
          @sorpresas.shuffle
        end
      end
      var=@usadas+1
      @usadas=var
      s=@sorpresas[0]
      @sorpresas.delete_at(0)
      @sorpresas<<s
      @ultimaSorpresa=s
      return s
    end
    def inhabilitarCartaEspecial(sorpresa)
      com=false
      carta=0
      tam=@sorpresas.size
      for i in 1..tam        
        if((@sorpresas[i]==sorpresa) and  (com==false))
          com=true
          carta=i
          @sorpresas.delete_at(carta)
          @cartasEspeciles<<sorpresa
          Diario.instance.ocurre_evento("Se elimina carta sorpresa #{sorpresa} del mazo y se añade a cartas especiales")
        end
      end
    end
    def habilitarCartaEspecial(sorpresa)
      com=false
      carta=0
      for i in 1..@cartasEspeciales.size
        if((@cartasEsciales[i]==@sorpresa) and  (com==false))
          com=true
          carta=i
          @cartasEspeciales.delete_at(carta)
          @sorpresas<<sorpresa
          a="Se elimina carta sorpresa #{sorpresa} de cartasEspeciales y se añade a mazo"
          ocurreEvento(a)
        end
      end
    end
    private :barajada, :debug, :ultimaSorpresa, :usadas
  end
end