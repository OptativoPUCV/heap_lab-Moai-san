#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    return NULL;
}



void heap_push(Heap* pq, void* data, int priority)
{
  if ((pq->size)==(pq->capac))
  {
    pq->capac =((2*(pq->capac))+1);
    pq->heapArray =(heapElem*)realloc(pq->heapArray,((pq->capac)*sizeof(heapElem)));
  }
  pq->heapArray->data =(data);
  pq->heapArray->priority =(priority);
  pq->size =((pq->size)+1);
}


void heap_pop(Heap* pq){

}

heapElem* create_heapArray()
{
  heapElem* output =(heapElem*)calloc(3,sizeof(heapElem));
  return(output);
}

Heap* createHeap()
{
  Heap* output =(Heap*)calloc(1,sizeof(Heap));
  output->heapArray =create_heapArray();
  output->capac =3;
  return output;
}
