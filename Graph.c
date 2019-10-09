#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "Graph.h"

typedef struct GraphRep {
    AdjList *edges; // Array of linked lists
    int nV;       // Number of vertices
    int nE;       // Number of edges
} GraphRep;

// Helper functions

// Make a new node to represent an edge in the graph
static adjListNode *newListNode(Vertex dest, int weight);

//void freeAdjList(AdjList L);

Graph newGraph(int noNodes) {

    assert(noNodes >= 0);
    
    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = noNodes;
    g->nE = 0;

    // allocating memory for array of lists
    int i;
    g->edges = malloc(noNodes * sizeof(AdjList));
    assert(g->edges != NULL);
    
    // there are no edges yet so all vertices'
    // have edges which point to NULL
    for (i = 0; i < noNodes; i++) {
        g->edges[i] = NULL;
    }
    
    return g;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    
    assert(src < g->nV);
    
    // Need to check if vertex exists already
    adjListNode *newnode = newListNode(dest, weight);
    
    if (g->edges[src] == NULL) {
        g->edges[src] = newnode;
    } else {
        newnode->next = g->edges[src];
        g->edges[src] = newnode;
    }
    
    g->nE++;

}

void removeEdge(Graph g, Vertex src, Vertex dest) {

    // Only 1 edge in list
    if (g->edges[src]->next == NULL) {
        
        // Edge to be deleted not in list
        if (g->edges[src]->w != dest) {
            fprintf(stderr, "Edge from %d to %d does not exist\n", src, dest);
            exit(EXIT_FAILURE);
            
        // Edge to be removed is only edge in list
        } else {
            free(g->edges[src]);
            g->edges[src] = NULL;
        }
    
    // Edge to be removed is first edge in list
    } else if (g->edges[src]->w == dest) {
        adjListNode *after = g->edges[src]->next;
        free(g->edges[src]);
        g->edges[src] = after;
    
    } else {
        
        // Finding edge
        adjListNode *curr = g->edges[src]->next;
        adjListNode *prev = g->edges[src];
        while (curr != NULL && curr->w != dest) {
            prev = curr;
            curr = curr->next;
        }
        
        // Edge to be removed was not found
        if (curr == NULL) {
            fprintf(stderr, "Edge from %d to %d does not exist\n", src, dest);
            exit(EXIT_FAILURE);
        }
        
        // Edge to be removed is at the end of the list
        if (curr->next == NULL) {
            free(curr);
            prev->next = NULL;
         
        // Edge to be removed is in the middle of the list
        } else {
            prev->next = curr->next;
            free(curr);
        }
    }
    
    g->nE--;
    
}

bool adjacent(Graph g, Vertex src, Vertex dest) {

    adjListNode *curr = g->edges[src];
    
    // If the dest vertex is adjacent to the src return 1
    // otherwise return 0
    while (curr != NULL) {
        if (curr->w == dest) {
            return 1;
        }
        curr = curr->next;
    }
    
    return 0;

}

void showGraph(Graph g) {

    int i;
    for (i = 0; i < g->nV; i++) {
        AdjList curr = g->edges[i];
        while (curr != NULL) {
            printf("Edge from Vertex %d to Vertex %d with weight %d\n",
                i, curr->w, curr->weight);
            curr = curr->next;
        }
    }

}

void freeGraph(Graph g) {
    assert(g != NULL);

    // Free memory used by graph
    int i;
    for (i = 0; i < g->nV; i++) {
    
        AdjList curr = g->edges[i];
        while (curr != NULL) {
            AdjList next = curr->next;
            free(curr);
            curr = next;
        }
        
    }
    
    free(g->edges);
    free(g);
}

int numVerticies (Graph g) {

    return g->nV;

}

AdjList outIncident(Graph g, Vertex v) {

    adjListNode *curr = g->edges[v];
    AdjList out = NULL;
    
    // If there are no edges going out of v,
    // return an empty adjacent list
    if (curr == NULL) {
        return out;
    }
    
    // Scanning through edges going out of v and adding them to the
    // end of the AdjList "out"
    while (curr != NULL) {
        adjListNode *newnode = newListNode(curr->w, curr->weight);
        if (out == NULL) {
            out = newnode;
        } else {
            AdjList curr2 = out;
            while (curr2->next != NULL) {
                curr2 = curr2->next;
            }
            curr2->next = newnode;
        }
        curr = curr->next;
    }
    
    return out;

}

AdjList inIncident(Graph g, Vertex v) {

    AdjList in = NULL;
    
    // Scanning through all edges in the graph. At each edge
    // encountered, check if the edge goes into vertex v. If the edge
    // goes into the vertex v, add the edge to the end of the AdjList
    // "in"
    int i = 0;
    for (i = 0; i < g->nV; i++) {       
        adjListNode *curr = g->edges[i];
        if (curr == NULL) {
            continue;
        }
        while (curr != NULL) {
            
            if (curr->w == v) {
                adjListNode *newnode = newListNode(i, curr->weight);
                if (in == NULL) {                
                    in = newnode;                
                } else {
                    AdjList curr2 = in;
                    while (curr2->next != NULL) {
                        curr2 = curr2->next;
                    }
                    curr2->next = newnode;
                }
            }  
            curr = curr->next;  
        }
    }
    
    
    return in;

}

static adjListNode *newListNode(Vertex dest, int weight) {
    
    AdjList new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate MMList node");
	*new = (adjListNode) {.w = dest , .weight = weight, .next = NULL} ;
	return new;
}