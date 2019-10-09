#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>


ItemPQ newItemPQ(int a, int b){

  ItemPQ *p = malloc(sizeof(struct ItemPQ)) ;
  p->key = a;
  p->value = b;
  
  return *p;
}


int main(){

  PQ pq = newPQ();
  printf("\naddPQ: {1,100}\n");
  addPQ(pq,newItemPQ(1,100) );
  printf("addPQ: {2,15}\n");
  addPQ(pq,newItemPQ(2,15));
  printf("addPQ: {3,1}\n");
  addPQ(pq,newItemPQ(3,1));
  printf("addPQ: {4,4}\n");  
  addPQ(pq,newItemPQ(4,4));
  printf("addPQ: {5,3}\n");  
  addPQ(pq,newItemPQ(5,3));
  
  ItemPQ v; 
  for(int i=0; i<5; i++){  
      v = dequeuePQ(pq);
      printf("Dequeued: {%d,%d}\n",v.key,v.value);
  }

  printf("addPQ: {2,12}\n");  
  addPQ(pq,newItemPQ(2,12) );
  printf("addPQ: {4,8}\n");  
  addPQ(pq,newItemPQ(4,8));
  printf("addPQ: {3,10}\n");  
  addPQ(pq,newItemPQ(3,10));
  
  printf("Update {4,8} to {4,11}\n");
  updatePQ(pq, newItemPQ(4,11)) ;
  
  for(int i=0; i<3; i++){  
      v = dequeuePQ(pq);
      printf("Dequeued: {%d,%d}\n",v.key,v.value);
  }  
  
  printf("\n");

  freePQ(pq);
  
  return EXIT_SUCCESS;
}
