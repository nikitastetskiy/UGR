#!/bin/bash

echo "" > $1.dat
i=2000
while (( $i <= 500001 ));
do
  ./$1 $i >> $1.dat
  i=`expr $i + 2000`
done
