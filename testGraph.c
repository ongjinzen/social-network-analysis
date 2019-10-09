/**
#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
**/
#include "Graph.h"
#include "GraphVis.h"
#include "BSTree.h"
#include <stdlib.h>
#include <stdio.h>


void check_removeEdge_adjacent(Graph g);
void check_inIncident(Graph g);
void check_outIncident(Graph g);
	
void printSortedAdjList(AdjList list){

    Tree t = newTree();
	while(list != NULL) {
        t = TreeInsert(t, list->w);
		list = list->next;
	}
    printTree(t);
    freeTree(t);
}


int main(int argc, char* argv[]){
	
    Graph g = newGraph(10);
	insertEdge(g,0,1,2);
	insertEdge(g,0,2,5);
	insertEdge(g,0,3,1);
	insertEdge(g,1,4,1);
	insertEdge(g,0,5,7);
	insertEdge(g,1,6,2);
	insertEdge(g,0,7,100);
	insertEdge(g,2,8,3);
	insertEdge(g,0,9,9);
	insertEdge(g,9,0,11);
	insertEdge(g,5,1,6);
	insertEdge(g,9,4,2);
	insertEdge(g,3,8,4);
	insertEdge(g,8,1,8);
	insertEdge(g,1,3,4);
	insertEdge(g,7,5,2);
	insertEdge(g,7,2,6);		
	
	check_removeEdge_adjacent(g);
	check_inIncident(g);
	check_outIncident(g);
	
	printf("\n\n");
	
	//graphVis(g, DEFAULT);
}

void check_removeEdge_adjacent(Graph g) {
	printf("\nnV: %d\n",numVerticies(g));
	printf("\n\n***** Check Adjacency...\n");
	int i = 0;
	int j = 0;
	for (i=0;i<10;i++) {
		for (j=0;j<10;j++) {
			if (i == j) continue;
			printf("    %d -> %d : %d\n",i,j,adjacent(g,i,j));
		}
	}
	printf("Remove Edge 8->1\n");
	removeEdge(g,8,1);
	printf("Remove Edge 9->0\n");
	removeEdge(g,9,0);
	printf("Remove Edge 0->3\n");
	removeEdge(g,0,3);
	printf("\n\n***** Check Adjacency (after remove edge)...\n");
	for (i=0;i<10;i++) {
		for (j=0;j<10;j++) {
			if (i == j) continue;
			printf("    %d -> %d : %d\n",i,j,adjacent(g,i,j));
		}
	}
	printf("\nnV: %d\n",numVerticies(g));
}

void check_outIncident(Graph g) {
	printf("\n\n***** Check outIncident...\n");
	int i = 0;
	for (i=0;i<10;i++) {
		printf("  %d : ",i);
		printSortedAdjList( outIncident(g,i) );
		printf("\n");
	}
}


void check_inIncident(Graph g) {
	printf("\n\n***** Check inIncident...\n");
	int i = 0;
	for (i=0;i<10;i++) {
		printf("  %d : ",i);
		AdjList l1 = inIncident(g,i);
		printSortedAdjList( l1 );
		printf("\n");
	}
}
