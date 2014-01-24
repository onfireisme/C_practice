#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define HEAPLENGTH 1000
typedef int NodeType;
typedef struct myHeap{
	NodeType *nodeArray;
	int lastNodePosition;
}Heap;
/*
 * the procedure of build heap
 * from the last one of the heap ,we use the buildMaxHeap or buildMinHeap
 * why? In this way,we can make the higher level of the binary heap is larger or smaller
 * thant the lower level
 */

/*
 * the properties of heap is the father nodes is always larger or smaller
 * than the son nodes,then we can get the largest node and smallest node
 * from the top node
 * first ,we build the heap.
 * second, we remove the top node which is already the largest or smallest
 * node 
 * third,we build the heap again,and then remove the top node
 */

/*
 * the first node position is 1,if the start position is 0, then it will be complicate
 * I can write a node sturct ,its fine.
 * But in fact,an array is enough
 * for arbitrary node, his position is x,then his left node is 2x,right node is 2x+1
 */
void initialHeap(Heap *localHeap);
void buildMaxHeap(Heap *localHeap,int nodePosition);
void buildMinHeap(Heap *localHeap,int nodePosition);
void heapSort(Heap *localHeap);
void showHeap(Heap *localHeap);
void getSortedHeap(Heap *localHeap);
void freeHeap(Heap *localHeap);
