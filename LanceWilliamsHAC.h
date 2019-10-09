// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif

typedef struct DNode *Dendrogram;
typedef struct DNode {
   int  vertex;
   Dendrogram left, right;
} DNode;




/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */
Dendrogram LanceWilliamsHAC(Graph g, int method);


void freeDendrogram(Dendrogram d);



