#include</home/onfire/C/stack.h>
typedef struct{
	MyStack stackOne;
	MyStack stackTwo;
}StackFormedQueue;
typedef node_type stackNodeType;
void initialQueue(StackFormedQueue *localQueue);
void enQueue(StackFormedQueue *localQueue,stackNodeType local_node);
void deQueue(StackFormedQueue *localQueue);
