#!/bin/bash

echo "" > datos_seleccion.dat
ini=1000
fin=50000
rango=1000
i=$ini
while (( $i <= $fin ));
do
  ./seleccion $i >> datos_seleccion.dat
  i=`expr $i + $rango`
done
