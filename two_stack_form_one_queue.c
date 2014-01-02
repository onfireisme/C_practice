#include</home/onfire/C/two_stack_form_one_queue.h>
void initialQueue(StackFormedQueue *localQueue){
	initialStack(&localQueue->stackOne);
	initialStack(&localQueue->stackTwo);
}
void enQueue(StackFormedQueue *localQueue,stackNodeType local_node){
}
void deQueue(StackFormedQueue *localQueue){
}
stackNodeType maxQueueElement(StackFormedQueue *localQueue){
}
void freeQueue(StackFormedQueue *localQueue){
	freeStack(&localQueue->stackOne);
	freeStack(&localQueue->stackTwo);
}
int main(void){
	StackFormedQueue Queue;
//	initialQueue(&Queue);
//	freeQueue(&Queue);
	return 1;
}
