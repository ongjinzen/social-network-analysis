/*
 * testCentralityMeasures.c
 * Written By Zain Afzal for cs2521 
 *
 * Includes basic interface to read a graph in from
 * a file and a measure and calls the related functions
 *
 * Feel free to override this with your own tests if
 * you so wish.
 */
#include "Graph.h"
#include "GraphRead.h"
#include "CentralityMeasures.h"
#include "GraphVis.h"

#include <stdlib.h>
#include <stdio.h>
#define BUFF_SIZE 1024


void printUsage(){
	printf("Usage: ./testCentralityMeasures [file] [flag]\n");
	printf("Valid Flags:\n");
	printf("    d    : degree centrality\n");
	printf("    do   : degree out centrality\n");
	printf("    di   : degree in centrality\n");
	printf("    c    : closeness centrality\n");
	printf("    b    : betweenness centrality\n");
	printf("    bn   : betweenness centrality normalised\n");
	printf("    v[m] : trigger Graph Vis with mode [m]\n");
	printf("Valid Graph Vis Modes:\n");
	printf("    0    : DEFAULT\n");
	printf("    1    : DEGREE_IN\n");
	printf("    2    : DEGREE_OUT\n");
	printf("    3    : DEGREE\n");
	printf("    4    : CLOSENESS\n");
	printf("    5    : BETWEENNESS\n");
}

int main(int argc, char* argv[]){
	if (argc < 3) {
		printUsage();
		return EXIT_FAILURE;
	}
	Graph g = readGraph(argv[1]);
	//printf("HASN'T BEEN IMPLEMENTED\n");
	if (argv[2][0] == 'd' && argv[2][1] == '\0') {
  	NodeValues val = degreeCentrality(g);
  	showNodeValues(val);
  	freeNodeValues(val);
	} else if (argv[2][0] == 'd' && argv[2][1] == 'i') {
  	NodeValues val = inDegreeCentrality(g);
  	showNodeValues(val);
  	freeNodeValues(val);
	} else if (argv[2][0] == 'c' && argv[2][1] == '\0') {
  	NodeValues val = closenessCentrality(g);
  	showNodeValues(val);
  	freeNodeValues(val);
	} else if (argv[2][0] == 'b' && argv[2][1] == '\0') {
  	NodeValues val = betweennessCentrality(g);
  	showNodeValues(val);
  	freeNodeValues(val);
	} else if (argv[2][0] == 'd' && argv[2][1] == 'o') {
  	NodeValues val = outDegreeCentrality(g);
  	showNodeValues(val);
  	freeNodeValues(val);
	} else if (argv[2][0] == 'b' && argv[2][1] == 'n') {
  	NodeValues val = betweennessCentralityNormalised(g);
  	showNodeValues(val);
  	freeNodeValues(val);
	} else if (argv[2][0] == 'v') {
			graphVis(g, argv[2][1]-'0');
	} else {
		printUsage();
	}
	freeGraph(g);
}
