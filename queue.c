#include</home/onfire/C/queue.h>
void EnQueue(queueElementType element){
	END++;
	ELEMENT_COUNT++;
	if(ELEMENT_COUNT>QUEUE_LENGTH){
		printf("the queue is full!");
		return;
	}
	if(END=QUEUE_LENGTH+1){
		END=1;
		Queue[END-1]=element;
	}
}
void DeQueue(){
	BEGIN++;
	ELEMENT_COUNT--;
	if(ELEMENT_COUNT<0){
		printf("the queue is empty now");
		ELEMENT_COUNT=0;
		return;
	}
	if(BEGIN==QUEUE_LENGTH){
		BEGIN=0;
	}
}
queueElementType MaxElement(){
}
void queueInitialize(){
	Queue=(queueElementType *)malloc(QUEUE_LENGTH*sizeof(queueElementType));
}
void showTheQueue(){
	int i=0;
	for(i;i<ELEMENT_COUNT;i++){
	}
}
//if we want to realize the loop function,then the remalloc function is not need anymore!
//so,I have to say the linked_list_queue is the best choice
void QueueRemalloc(queueElementType **queue){
	QUEUE_COUNT++;
	*queue=(queueElementType *)realloc(*queue,QUEUE_COUNT*QUEUE_LENGTH*sizeof(queueElementType));
}
int main(void){
	queueInitialize();
	DeQueue();
	int temp1=5;
	int temp2=4;
	int temp3=6;
	EnQueue(temp1);
	EnQueue(temp1);
	EnQueue(temp1);
	return 1;
}
