#!/bin/bash

make
echo "$1"
./bin/viajante_comercio ./datosTSP/$1.tsp ./caminos/$1.tsp

./bin/tsp ./datosTSP/$1.tsp ./caminos/$1.tsp > ./caminos/$1plot.tsp
