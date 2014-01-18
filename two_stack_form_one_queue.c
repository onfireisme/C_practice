#include</home/wangyan/C_practice/two_stack_form_one_queue.h>
void initialQueue(StackFormedQueue *localQueue){
	localQueue->stackOne=(MyStack *)malloc(sizeof(MyStack));
	localQueue->stackTwo=(MyStack *)malloc(sizeof(MyStack));
	initialStack(localQueue->stackOne);
	initialStack(localQueue->stackTwo);
}
void enQueue(StackFormedQueue *localQueue,stackNodeType local_node){
	//for enQueue,we just push the element into the stackOne is ok
	if(localQueue->stackOne->current_position<STACK_LENGTH-1){
		push(localQueue->stackOne,local_node);
	}
	else{
		printf("the queue is full");
	}
}
void deQueue(StackFormedQueue *localQueue){
	//firstly,we need checkt if stackTwo was null
	if(localQueue->stackOne->current_position==-1&&localQueue->stackTwo->current_position==-1){
		printf("the queue is null");
		return;
	}
	if(localQueue->stackTwo->current_position!=-1){
		pop(localQueue->stackTwo);
	}
	else{
		copy_stack(localQueue);
		pop(localQueue->stackTwo);
	}
}
void copy_stack(StackFormedQueue *localQueue){
	while(localQueue->stackOne->current_position!=-1){
		if(localQueue->stackTwo->current_position<STACK_LENGTH-1){
			push(localQueue->stackTwo,
					localQueue->stackOne->nodeArray[localQueue->stackOne->current_position]);
			pop(localQueue->stackOne);
		}
		else{
			printf("the stackTwo is full");
		}
	}
}
stackNodeType maxQueueElement(StackFormedQueue *localQueue){
	int local_stackOneMaxElement=maxStackElement(localQueue->stackOne);
	int local_stackTwoMaxElement=maxStackElement(localQueue->stackTwo);
	if(local_stackTwoMaxElement>local_stackOneMaxElement){
		return local_stackTwoMaxElement;
	}
	else{
		return local_stackOneMaxElement;
	}
}
//show the Queue from the fisrt one to the last
void showQueue(StackFormedQueue *localQueue){
	printf("print stackOne \n");
	showStack(localQueue->stackOne);
	printf("print stackTwo \n");
	showStack(localQueue->stackTwo);
}
void freeQueue(StackFormedQueue *localQueue){
	freeStack(localQueue->stackOne);
	freeStack(localQueue->stackTwo);
	free(localQueue->stackOne);
	free(localQueue->stackTwo);
}
int main(void){
	StackFormedQueue Queue;
	initialQueue(&Queue);
	int temp1=5;
	int temp2=6;
	int temp3=7;
	int temp4=8;
	enQueue(&Queue,temp4);
	enQueue(&Queue,temp3);
	enQueue(&Queue,temp2);
	deQueue(&Queue);
	enQueue(&Queue,temp1);
//	printf("%d",
//	maxQueueElement(&Queue));
	showQueue(&Queue);
//	initialQueue(&Queue);
//	freeQueue(&Queue);
	freeQueue(&Queue);
	return 1;
}
