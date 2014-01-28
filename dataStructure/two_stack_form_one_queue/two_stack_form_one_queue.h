#include</home/wangyan/C_practice/stack.h>
typedef struct{
	//the first stack enQueue the element, the second stack deQueue the element
	MyStack *stackOne;
	MyStack *stackTwo;
}StackFormedQueue;
typedef node_type stackNodeType;
void initialQueue(StackFormedQueue *localQueue);
void enQueue(StackFormedQueue *localQueue,stackNodeType local_node);
void deQueue(StackFormedQueue *localQueue);
void copy_stack(StackFormedQueue *localQueue);
void showQueue(StackFormedQueue *localQueue);
