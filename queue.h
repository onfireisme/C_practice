#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define QUEUE_LENGTH 2 
typedef int queueElementType;
typedef struct{
	queueElementType *queueArray;
	int begin;
	int end;
	int elementCount;
}Queue;
//use the begin and end to realize the loop function
//when we insert first element,begin is 0, end is 1. when we insert 3
void EnQueue(queueElementType element,Queue *queue);
void DeQueue(Queue *queue);
queueElementType MaxElement();
void queueInitialize(Queue *queue);
void showTheQueue(Queue *queue);
//void QueueRemalloc(queueElementType **queue);
