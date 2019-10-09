// Dijkstra ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#include "Graph.h"
#ifndef _CS2521_DIJKSTRA_H
#define _CS2521_DIJKSTRA_H
typedef struct PredNode {
   int         v;
   struct PredNode *next;
} PredNode;

typedef struct ShortestPaths {
   int noNodes;
   int src;
   int *dist;
   PredNode **pred;
} ShortestPaths;


/* Finds shortest paths from a given vertex to all other vertices, as discussed in the lectures.
 * Returns 'ShortestPaths' structure with the required information
 * (i.e. 'distance' array, 'predecessor' arrays, source and no_of_nodes in the graph)
 */
ShortestPaths dijkstra(Graph, Vertex);


void  showShortestPaths(ShortestPaths);
void  freeShortestPaths(ShortestPaths);

#endif
