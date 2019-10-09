// Graph ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#ifndef _CS2521_CENTRALITY_H
#define _CS2521_CENTRALITY_H
#include "Graph.h"

typedef struct NodeValues {
   int noNodes;
   double* values;
} NodeValues;



NodeValues outDegreeCentrality(Graph);
NodeValues inDegreeCentrality(Graph);
NodeValues degreeCentrality(Graph);

NodeValues closenessCentrality(Graph);

NodeValues betweennessCentrality(Graph);
NodeValues betweennessCentralityNormalised(Graph);


void  showNodeValues(NodeValues);
void  freeNodeValues(NodeValues);
#endif
