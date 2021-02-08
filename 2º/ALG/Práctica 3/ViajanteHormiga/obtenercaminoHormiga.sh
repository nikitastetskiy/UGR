#!/bin/bash

make
echo "$1"
./viajante_comercio datosTSP/$1.tsp datosHormiga/$1.tsp

./tsp datosTSP/$1.tsp datosHormiga/$1.tsp > datosHormiga/$1plot.tsp
