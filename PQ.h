// PQ ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#ifndef _CS2521_PQ_H
#define _CS2521_PQ_H

typedef struct PQRep *PQ;

typedef struct ItemPQ {
   int         key;
   int         value;
} ItemPQ;


/* Creates new priority queue, that can store items of type ItemPQ.
*/
PQ newPQ();

/* Adds item (ItemPQ) to the priority queue.
   If an item with 'key' exists, it's 'value' is updated.
*/
void  addPQ(PQ, ItemPQ);

/* Removes and returns the item (ItemPQ) with smallest 'value'.
   For items with equal 'value', observes FIFO.
*/
ItemPQ  dequeuePQ(PQ);

/* Updates item with a given 'key' value, by updating that item's value to the given 'value'.
   If item with 'key' does not exist in the queue, no action is taken
*/
void  updatePQ(PQ, ItemPQ);

int PQEmpty(PQ);

void  showPQ(PQ);
void  freePQ(PQ);

#endif
