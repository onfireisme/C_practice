#include</home/onfire/C/queue.h>
void EnQueue(queueElementType element,Queue *queue){
	queue->end++;
	queue->elementCount++;
	if(queue->elementCount>QUEUE_LENGTH){
		printf("the queue is full!\n");
		queue->end--;
		queue->elementCount--;
		return;
	}
	if(queue->end>=QUEUE_LENGTH+1){
		queue->end=1;
	}
	queue->queueArray[queue->end-1]=element;
}
void DeQueue(Queue *queue){
	queue->begin++;
	queue->elementCount--;
	if(queue->elementCount<0){
		printf("the queue is empty now\n");
		queue->elementCount=0;
		queue->begin--;
		return;
	}
	if(queue->begin==QUEUE_LENGTH){
		queue->begin=0;
	}
}
queueElementType MaxElement(){
}
void queueInitialize(Queue *queue){
	queue->queueArray=(queueElementType *)malloc(QUEUE_LENGTH*sizeof(queueElementType));
	queue->end=0;
	queue->begin=0;
	queue->elementCount=0;
}
void showTheQueue(Queue *queue){
	int begin=queue->begin;
	int end=queue->end;
	int i=0;
	for(i;i<queue->elementCount;i++){
		if(begin==QUEUE_LENGTH){
			begin=0;
		}
		printf("%d ",queue->queueArray[begin]);
		begin++;
	}
}
//if we want to realize the loop function,then the remalloc function is not need anymore!
//so,I have to say the linked_list_queue is the best choice
/*
void QueueRemalloc(queueElementType **queue){
	QUEUE_COUNT++;
	*queue=(queueElementType *)realloc(*queue,QUEUE_COUNT*QUEUE_LENGTH*sizeof(queueElementType));
}
*/
int main(void){
	Queue queue;
	queueInitialize(&queue);
	int temp1=5;
	int temp2=6;
	EnQueue(temp1,&queue);
	EnQueue(temp2,&queue);
	DeQueue(&queue);
//	printf("%d%d",BEGIN,END);
//	printf("%d",END);
	showTheQueue(&queue);
	free(queue.queueArray);
	return 1;
}
