# Makefile for Ass2

CC = gcc
CFLAGS =  -Wall -std=c11 -Werror -g
AR = ar
objs = Graph.o GraphVis.o CentralityMeasures.o PQ.o Dijkstra.o GraphRead.o 

all : testGraph testPQ testDijkstra testCentralityMeasures testLanceWilliamsHAC

$(objs) : %.o : %.c

GraphLib.a : $(objs)
	$(AR) rcs $@ $^

testGraph : testGraph.c BSTree.o GraphLib.a
	$(CC) -o testGraph testGraph.c BSTree.o GraphLib.a -lm

testPQ : testPQ.c PQ.o
	$(CC) -o testPQ  testPQ.c PQ.o -lm

testDijkstra : testDijkstra.c GraphLib.a
	$(CC) -o  testDijkstra testDijkstra.c GraphLib.a -lm

testCentralityMeasures : testCentralityMeasures.c GraphLib.a
	$(CC) -o testCentralityMeasures testCentralityMeasures.c GraphLib.a -lm


BSTree.o : BSTree.c BSTree.h 
	$(CC)  -c   BSTree.c  

LanceWilliamsHAC.o : LanceWilliamsHAC.c Graph.o  BSTree.o 
	$(CC)  $(CFLAGS) -c  -o LanceWilliamsHAC.o LanceWilliamsHAC.c    -lm

testLanceWilliamsHAC : testLanceWilliamsHAC.c Graph.h  Graph.o LanceWilliamsHAC.o BSTree.o GraphRead.o
	$(CC)   -o  testLanceWilliamsHAC testLanceWilliamsHAC.c Graph.o BSTree.o GraphRead.o LanceWilliamsHAC.o  -lm

clean :
	rm -f *.o testCentralityMeasures testDijkstra testGraph testPQ  testLanceWilliamsHAC GraphLib.a
	
	
