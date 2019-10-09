#include "LanceWilliamsHAC.h"
#include "BSTree.h"
#include "GraphRead.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void printClusters(Tree t, int depth){

	// To avoid infinite looping, due to a possible  
	// incorrect logic in the program being tested!
	assert( depth < 200 );
	
	printf("%d: {", depth);
	printTree(t);	
	printf("}");

	if((getLeftTree(t) == NULL) && (getRightTree(t) == NULL)) {
		printf(" (leaf)");
	}
	printf("\n");
}

Tree printDendrogram(Dendrogram dn, int depth){

	// To avoid infinite looping, due to a possible  
	// incorrect logic in the program being tested!
	assert( depth < 200 );

	Tree tr, tl;
	if(dn == NULL) return NULL;
	
	if((dn->left == NULL) && (dn->right == NULL)){
		Tree t = newTree();
		t = TreeInsert(t, dn->vertex);
		return t;
	}
	if(dn->left !=NULL) {
		tl = printDendrogram(dn->left, depth+1);
		printClusters(tl, depth);
	}
	if(dn->right !=NULL) {
		tr = printDendrogram(dn->right, depth+1);
		printClusters(tr, depth);
	}
	Tree bothTrees = addTree(tl, tr);
	
	return bothTrees;
}


int main(int argc, char* argv[]){
	if(argc < 2) {
		printf("Usage: ./testLanceWilliamsHAC [file]\n");
		return EXIT_FAILURE;
	}
  	Graph g = readGraph(argv[1]);

	Dendrogram dn =  LanceWilliamsHAC(g, 1);
	
	Tree allTree = printDendrogram(dn, 1);
	printClusters(allTree, 0);
	
	freeDendrogram(dn);

}


