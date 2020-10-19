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
  if(pq->size==0)
  {
    return NULL;
  }
  return pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority)
{
  int index =(pq->size);
  if ((pq->size)==(pq->capac))
  {
    pq->capac =((2*(pq->capac))+1);
    pq->heapArray =realloc(pq->heapArray,((pq->capac)*sizeof(heapElem)));
  }
  pq->heapArray[index].data =(data);
  pq->heapArray[index].priority =(priority);
  pq->size =((pq->size)+1);
}


void heap_pop(Heap* pq)
{
  for(int i =0;i<pq->size;i++)
  {
    printf("\n%d\n",pq->heapArray[i].priority);
    if(i%2==0)
    {
      if(i+2<pq->size)
      {
        if(pq->heapArray[i].priority<pq->heapArray[i+2].priority)
        {
          pq->heapArray[i] =pq->heapArray[i+2];
        }
      }
      else
      {
        pq->heapArray[i] =pq->heapArray[i+1];
        pq->size--;
      }
    }
  }
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
