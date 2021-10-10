#!/bin/bash

echo "" > datos_burbuja.dat
ini=1000
fin=50000
rango=1000
i=$ini
while (( $i <= $fin ));
do
  ./burbuja $i >> datos_burbuja.dat
  i=`expr $i + $rango`
done
