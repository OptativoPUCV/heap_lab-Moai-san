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
    if(index-parentFloor<parentFloor*2)
    {
      break;
    }
    parentFloor =parentFloor*2;
  }
  return (parentFloor);
}

int get_pIndex(int index)
{
  if(index==0)
  {
    return 0;
  }
  int parentFloor =get_pFloor(index);
  int pIndex;
  if(index%2==0)
  {
    pIndex =get_pIndex(index-1);
  }
  else
  {
    pIndex =index-parentFloor;
    if(pIndex>parentFloor)
    {
      pIndex =pIndex-1;
    }
  }
  return (pIndex);
}

void switch_PNode(heapElem* elemArray,int index)
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
    switch_PNode(pq->heapArray,index);
  }
  pq->size =((pq->size)+1);
}

void behead(heapElem* elemArray,int last)
{
  elemArray[0].data=elemArray[last].data;
  elemArray[0].priority=elemArray[last].priority;
  elemArray[last].priority =0;
  elemArray[last].data =NULL;
}

void heap_pop(Heap* pq)
{
  behead(pq->heapArray,(pq->size)-1);
  pq->size--;
  int current =0;
  int aSon =1;
  int bSon =2;
  heapElem aux;
  while(1)
  {
    printf("%d\n",current);
    aux =pq->heapArray[current];
    if((aSon<=pq->size)&&(bSon<=pq->size))
    {
      if((pq->heapArray[aSon].priority)<(pq->heapArray[bSon].priority))
      {
        pq->heapArray[current] =pq->heapArray[bSon];
        pq->heapArray[bSon] =aux;
        current =bSon;
        aSon =(2*current)+1;
        bSon =(2*current)+2;
        continue;
      }
      if((pq->heapArray[bSon].priority)<(pq->heapArray[aSon].priority))
      {
        pq->heapArray[current] =pq->heapArray[aSon];
        pq->heapArray[aSon] =aux;
        current =aSon;
        aSon =(2*current)+1;
        bSon =(2*current)+2;
        continue;
      }
    }
    break;
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
