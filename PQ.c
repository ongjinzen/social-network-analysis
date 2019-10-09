// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct PQRep {
	ItemPQ *array;
	int nitems;
};

static void fixup(ItemPQ array[], int i);
static void fixdown(ItemPQ array[], int i, int N);
static void swap(ItemPQ array[], int first, int second);

PQ newPQ() {

	PQ queue = malloc(sizeof(struct PQRep));
	if (queue == NULL) {
		printf("Unable to allocate memory for queue.\n");
	}

	queue->array = malloc(sizeof(ItemPQ));
	if (queue->array == NULL) {
		printf("Unable to allocate memory for array in queue.\n");
	}
	
	queue->nitems = 0;

	return queue;
}

int PQEmpty(PQ p) {
		
		assert(p != NULL);
		bool is_empty = false;

		if (p->nitems == 0) {
			is_empty = true;
		}

		return is_empty;
}

void addPQ(PQ pq, ItemPQ element) {

	assert(pq != NULL);

	int i = 1;
	bool element_found = false;

	// This while loop checks if there is an element in the queue
	// with the same key as the new element to be added.
	while (i <= pq->nitems) {
		if (pq->array[i].key == element.key) {
			if (element.value > pq->array[i].value) {
				pq->array[i].value = element.value;
				fixdown(pq->array, i, pq->nitems);
			} else if (element.value < pq->array[i].value){
				pq->array[i].value = element.value;
				fixup(pq->array, i);
			}
		}
		i++;
	}
	// This only runs if the key of the new
	// element is not already in the queue.
	if (element_found == false) {
		pq->nitems++;
		pq->array = realloc(pq->array, (pq->nitems + 1) * (sizeof(struct ItemPQ)));
		pq->array[pq->nitems] = element;
		fixup(pq->array, pq->nitems);
	}
}

ItemPQ dequeuePQ(PQ pq) {

	assert(pq != NULL);
	assert(pq->nitems > 0);
	
	ItemPQ throwAway = pq->array[1];
	pq->array[1] = pq->array[pq->nitems];
	pq->nitems--;
	fixdown(pq->array, 1, pq->nitems);

	return throwAway;
}

void updatePQ(PQ pq, ItemPQ element) {
	
	assert(pq != NULL);

	int i = 1;

	// Search for the element with the same key as
	// the new element and update the existing element's
	// value, then fix up or down depending on the value.
	while (i <= pq->nitems) {
		if (pq->array[i].key == element.key) {
			if (element.value > pq->array[i].value) {
				pq->array[i].value = element.value;
				fixdown(pq->array, i, pq->nitems);
			} else if (element.value < pq->array[i].value){
				pq->array[i].value = element.value;
				fixup(pq->array, i);
			}
		}
		i++;
	}
}

// Prints the queue in an array-like form.
void  showPQ(PQ pq) {
	
	int i = 1;
	printf("(%d)", pq->array[1].value);
	i++;
	
	while (i <= pq->nitems) {
		printf("-(%d)", pq->array[i].value);
		i++;
	}

	printf("\n");
}

void  freePQ(PQ pq) {
	free(pq->array);
		free(pq);
}

// Check if the value of a node is smaller than its parent's.
// If yes, swap with the parent.
static void fixup(ItemPQ array[], int i) {
	while ((i > 1) && (array[i].value < array[i/2].value)) {
		swap(array, i, i/2);
		i = i/2;
	}
}

// Check if the value of a node is greater than its childrens'.
// If yes, swap with the child with the greater value.
static void fixdown(ItemPQ array[], int i, int N) {
	while (2 * i <= N) {
		int j = 2 * i;

		if ((j < N) && (array[j].value > array[j + 1].value)) {
			j++;
		}

		if (array[i].value < array[j].value) {
			break;
		}

		swap(array, i, j);
		i = j;
	}
}

// Helper function to swap positions of two nodes in a queue.
static void swap(ItemPQ array[], int first, int second) {
	ItemPQ temp = array[first];
	array[first] = array[second];
	array[second] = temp;
}
