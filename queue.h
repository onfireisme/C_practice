#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define QUEUE_LENGTH 2 
typedef int queueElementType;

queueElementType *Queue;

static queueElementType QUEUE_COUNT =1;
//use the begin and end to realize the loop function
//when we insert first element,begin is 0, end is 1. when we insert 3
int static BEGIN=0;
int static END=0;
int static ELEMENT_COUNT=0;
void EnQueue(queueElementType element);
void DeQueue();
queueElementType MaxElement();
void QueueRemalloc(queueElementType **queue);
