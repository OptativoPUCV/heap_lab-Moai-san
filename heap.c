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

/*piso tiene 2 a la n nodos, piso raiz 2 a la 0, y asi en adelante
entonces, para cumplir con la propiedad, se debe ver al padre solamente
por lo cual, debemos ver cual es nuestro current, y desde esa premisa
modificar nuestra posicion, si nuestra posicion es 5 o 6, nuestro padre es 2
osea, esto lo representamos matematicamente como pos-(piso del padre)*/
int get_pFloor(int index)
{
  int parentFloor =1;
  while(parentFloor*2<index)
  {
    parentFloor =parentFloor*2;
  }
  return (parentFloor);
}

int get_pIndex(int index)
{
  int parentFloor =get_pFloor(index);
  int pIndex;
  if(index%2==0)
  {
    pIndex =index-parentFloor-1;
  }
  else
  {
    pIndex =index-parentFloor;
  }
  return (pIndex);
}

void switch_Node(heapElem* elemArray,int index)
{
  heapElem aux;
  int pIndex =get_pIndex(index);
  while(1)
  {
    if(elemArray[index].priority > elemArray[pIndex].priority)
    {
      aux.data =elemArray[pIndex].data;
      aux.priority =elemArray[pIndex].priority;
      elemArray[pIndex].data =elemArray[index].data;
      elemArray[pIndex].priority =elemArray[index].priority;
      elemArray[index].data =aux.data;
      elemArray[index].priority =aux.priority;
      index =pIndex;
      pIndex =get_pIndex(index);
    }
    else
    {
      break;
    }
  }
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
  if (index!=0)
  {
    switch_Node(pq->heapArray,index);
  }
  pq->size =((pq->size)+1);
}


void heap_pop(Heap* pq)
{
  pq->heapArray[0] =pq->heapArray[1];
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
