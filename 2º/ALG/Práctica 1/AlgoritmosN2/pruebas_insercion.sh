#!/bin/bash

echo "" > datos_insercion.dat
ini=1000
fin=50000
rango=1000
i=$ini
while (( $i <= $fin ));
do
  ./insercion $i >> datos_insercion.dat
  i=`expr $i + $rango`
done
