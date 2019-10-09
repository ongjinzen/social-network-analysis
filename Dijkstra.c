// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// Helper function to add a node to an adjacency list.
void add_to_list(PredNode **list, Vertex vertex, Vertex pred) {
	
	// Allocate memory for new list.
	PredNode *new = malloc(sizeof(PredNode));
	new->v = pred;
	new->next = NULL;

	// If the list is empty, the new node is the start of the list.
	// Else, place the new node at the end of the list.
	if (list[vertex] == NULL) {
		list[vertex] = new;
	} else {
		PredNode *curr = list[vertex];

		// If node is already in the list,
		// do not add it again and return.
		if (curr->v == pred) {
			return;
		}

		while (curr->next != NULL) {
			curr = curr->next;
			if (curr->v == pred) {
				return;
			}
		}
		curr->next = new;
	}
}

// Frees all nodes on an index of an adjacency list.
void clear_list(PredNode **list, Vertex vertex) {
	
	if (list[vertex] == NULL) {
		return;
	} else if (list[vertex]->next == NULL) {
		PredNode *curr = list[vertex];
		free(curr);
	} else {
		PredNode *prev = list[vertex];
		PredNode *curr = prev->next;

		while (curr != NULL) {
			free (prev);
			prev = curr;
			curr = curr->next;
		}
	}
	list[vertex] = NULL;
}

ShortestPaths dijkstra(Graph g, Vertex v) {
	
	// Initialist the ShortestPaths struct.
	ShortestPaths answer;
	answer.noNodes = numVerticies(g);
	answer.src = v;
	answer.dist = malloc(answer.noNodes * sizeof(answer.dist));
	answer.pred = malloc(answer.noNodes * sizeof(PredNode *));

	int visited[answer.noNodes];

	
	// Set all distances in the struct to infinity
	// Set all predecessors in the struct to NULL
	for(int i = 0; i < answer.noNodes; i++) {
		answer.dist[i] = __INT_MAX__;
		answer.pred[i] = NULL;
		visited[i] = 0;
	}

	// Set the distance for the source node to 0.
	answer.dist[answer.src] = 0;
	ItemPQ edge;
	PQ set = newPQ();
	int length = 0;

	// Add all vertices to queue.
	for (int i = 0; i < answer.noNodes; i++) {
		edge.key = i;
		edge.value = answer.dist[i];
		addPQ(set, edge);
	}

	// While priority queue is not empty
	while (!PQEmpty(set)) {
		
		// Dequeue node with shortest distance
		edge = dequeuePQ(set);
		visited[edge.key] = 1;

		// Find all adjacent nodes to.
		AdjList head = outIncident(g, edge.key);

		while (head != NULL) {
			// If node has never been visited,
			// check the length of the path taken.
			if (visited[head->w] == 0) {
				
				// If the vertice with a distance of infinity
				// is dequeued, all other vertices still in the PQ
				// also have a distance of infinity and cannot be
				// reached from the source.
				if (answer.dist[edge.key] == __INT_MAX__) {
					break;
				} else {
					length = answer.dist[edge.key] + head->weight;
				}

				// If the length is same as another path taken,
				// Add it to the predecessor list.
				if (length == answer.dist[head->w]) {
					add_to_list(answer.pred, head->w, edge.key);

				// If the length is shorter than a previous path
				// taken, clear the list, add the new predecessor
				// to the adjacency list, update the shortest
				// distance to the node and update the distances
				// in the priority queue.
				} else if (length < answer.dist[head->w]) {
					answer.dist[head->w] = length;
					clear_list(answer.pred, head->w);
					add_to_list(answer.pred, head->w, edge.key);
					ItemPQ update;
					update.key = head->w;
					update.value = length;
					updatePQ(set, update);
				}
			}
			head = head->next;
		}
	}

	// If there are nodes with distances
	// still at infinity then it is unreachable,
	// so we set the distances back to 0.
	for (int i = 0; i < answer.noNodes; i++) {
		if (answer.dist[i] == __INT_MAX__) {
			answer.dist[i] = 0;
		}
	}
	freePQ(set);

	return answer;
}

void showShortestPaths(ShortestPaths paths) {

	for (int i = 0; i < paths.noNodes; i++) {

		printf("The shortest path from vertex %d to vertex %d is length %d.\n", paths.src, i, paths.dist[i]);
		
		if (paths.pred[i] != NULL) {

			printf("The predecessor nodes are: ");

			for(PredNode *curr = paths.pred[i]; curr != NULL; curr = curr->next) {

				if (curr->next == NULL) {
					printf("%d\n\n", curr->v);
				} else {
					printf("%d, ", curr->v);
				}
			}
		} else {
			printf("\n");
		}
	}

}

void  freeShortestPaths(ShortestPaths paths) {

	free(paths.dist);

	for (int i = 0; i < paths.noNodes; i++) {
		clear_list(paths.pred, i);
	}

	free(paths.pred);
}