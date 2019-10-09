// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

static double searchnode(ShortestPaths source_paths, int curr, int dest, double *count);

NodeValues outDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values = malloc(sizeof(double)*(numVerticies(g)));
	
	// Finding number of edges coming out of each vertex
	int i;
	double out;
	for (i = 0; i < numVerticies(g); i++) {
	    out = 0;
	    AdjList curr = outIncident(g, i);
	    while (curr != NULL) {
	        out++;
	        curr = curr->next;
	    }    
	    throwAway.values[i] = out;
	}
	
	return throwAway;
	
}
NodeValues inDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values = malloc(sizeof(double)*(numVerticies(g)));
	
	// Finding number of edges going into each vertex
	int i;
	double out;
	for (i = 0; i < numVerticies(g); i++) {
	    out = 0;
	    AdjList curr = inIncident(g, i);
	    while (curr != NULL) {
	        out++;
	        curr = curr->next;
	    }    
	    throwAway.values[i] = out;
	}
	
	return throwAway;
	
}
NodeValues degreeCentrality(Graph g) {
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values = malloc(sizeof(double)*(numVerticies(g)));
	
	// Finding number of edges coming out of each vertex
	int i;
	double out;
	for (i = 0; i < numVerticies(g); i++) {
	    out = 0;
	    AdjList curr = outIncident(g, i);
	    while (curr != NULL) {
	        out++;
	        curr = curr->next;
	    }    
	    throwAway.values[i] = out;
	}
	
	// Finding number of edges going into each vertex and adding this
	// to the number of edges coming out of each vertex to determine
	// the degree centrality of each vertex
	double in;
	for (i = 0; i < numVerticies(g); i++) {
	    in = 0;
	    AdjList curr = inIncident(g, i);
	    while (curr != NULL) {
	        in++;
	        curr = curr->next;
	    }    
	    throwAway.values[i] = throwAway.values[i] + in;
	}
	
	return throwAway;
	
}

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values = malloc(sizeof(double)*(numVerticies(g)));
	
	ShortestPaths distances;
	
	int j;
	int reachable_nodes; // Number of nodes you can reach from a vertex
	
	int k;
	double sum_distances;
	
	int i;
	for (i = 0; i < numVerticies(g); i++) {

	    // Finding number of nodes you can reach from vertex i
	    reachable_nodes = 0;
	    distances = dijkstra(g, i);
        
        for (j = 0; j < numVerticies(g); j++) {
            PredNode *curr = distances.pred[j];
            if (curr != NULL) {
                reachable_nodes++;
            }
        }
        
        reachable_nodes++; // Since a node can reach itself
	    
	    // Finding sum of shortest path distance from i to other vertexes
	    sum_distances = 0;	    
	    for (k = 0; k < numVerticies(g); k++) {	    
	        sum_distances = sum_distances + distances.dist[k];	    
	    }
	    
	    // If vertex i cant reach anything, its closeness is 0
        if (sum_distances == 0) {
            throwAway.values[i] = 0;
        } else {
	        throwAway.values[i] = 
	        ((reachable_nodes - 1)*(reachable_nodes - 1))/
	        ((numVerticies(g) - 1)*(sum_distances));
	    }
	
	}
	
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){

	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values = calloc(numVerticies(g), sizeof(double));

	// For every source vertice.
	for (int source = 0; source < throwAway.noNodes; source++) {

		ShortestPaths source_paths = dijkstra(g, source);

		// For every destination vertice for the current source.
	    for (int dest = 0; dest < throwAway.noNodes; dest++) {

			// For every vertice that a path can pass through
			// to get from the source to the destination.
			for (int i = 0; i < throwAway.noNodes; i++) {
				if ((i != source) && (i != dest)){

					double count = 0;
					double paths = 0;

					// Count the number of paths from the source to destination.
					// and the number of times a vertice was accessed.
					paths = searchnode(source_paths, i, dest, &count);

					// If number of paths is not 0, update the betweenness of the vertice.
					if (paths != 0) {
						throwAway.values[dest] += (count / paths);
					}
				}
			}
	    }
		freeShortestPaths(source_paths);
	}
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = betweennessCentrality(g);

	for (int i = 0; i < throwAway.noNodes; i++) {
		throwAway.values[i] = throwAway.values[i] / ((throwAway.noNodes - 1) * (throwAway.noNodes - 2));
	}

	return throwAway;
}

void showNodeValues(NodeValues values){

    int i;
    for (i = 0; i < values.noNodes; i++) {
        printf("%d: %lf\n", i, values.values[i]);
    }

}

void freeNodeValues(NodeValues values){

    free(values.values);
    
}

// Back track through the adjacency list to find the total number of shortest paths from
// a destination to a source. Also keep track of the number of times a particular vertice
// was accessed throughout the searching of the number of paths.
static double searchnode(ShortestPaths source_paths, int curr, int dest, double *count) {
	if (curr == source_paths.src) {
		return 1;
	}

	double paths = 0;

	PredNode *temp = source_paths.pred[curr];
	while (temp != NULL) {
		paths += searchnode(source_paths, temp->v, dest, count);
		temp = temp->next;
	}
	if (curr == dest) {
		(*count) += paths;
	}
	return paths;
}