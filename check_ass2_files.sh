#!/bin/bash

MYFILES=" Graph.c PQ.c  CentralityMeasures.c    LanceWilliamsHAC.c  PQ.c  Dijkstra.c  LanceWilliamsHAC.c "
ls -l $MYFILES

for i in $MYFILES
do
echo "--------------------------------- ---------------------------------"
cat $i
echo "--------------------------------- ---------------------------------"

done 
