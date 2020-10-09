# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

class OperacionInmobiliaria
  def initialize(gest, ip)
    @numPropiedad=ip
    @gestion=gest
  end
  def getGestion
    return @gestion
  end
  def getNumPropiedad
    return @numPropiedad
  end
  
end
