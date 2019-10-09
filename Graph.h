// Graph ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#ifndef _CS2521_GRAPH_H
#define _CS2521_GRAPH_H

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

typedef struct _adjListNode {
   Vertex         w;
   int         weight;
   struct _adjListNode *next;
} adjListNode;

typedef adjListNode* AdjList;

Graph newGraph(int noNodes);

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight);
void  removeEdge(Graph g, Vertex src, Vertex dest);
bool  adjacent(Graph g, Vertex src, Vertex dest);
int  numVerticies(Graph g);


/*
 * Returns a list of adjacent vertices
 * on outgoing edges from a given vertex.
**/
AdjList outIncident(Graph g, Vertex v);
/*
 * Returns a list of adjacent vertices
 * on incoming edges from a given vertex.
**/
AdjList inIncident(Graph g, Vertex v);

void  showGraph(Graph g);
void  freeGraph(Graph g);

#endif
