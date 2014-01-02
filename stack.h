#include<stdio.h>
#include<malloc.h>
#define STACK_LENGTH 1000
#define NEGATIVE_SINGNAL -1
typedef int node_type;
typedef struct {
	node_type *nodeArray;
	node_type *maxNodeIndexArray;
	int current_position;
	int stack_array_count;
	int maxPosition;
}MyStack;
void init_stack(MyStack *temp_stack);
void push(MyStack *temp_stack,node_type node_value);
void pop(MyStack *temp_stack);
void reMalloc(MyStack *temp_stack);
node_type maxElement(MyStack *temp_stack);
void showStack(MyStack *temp_stack);
void freeStack(MyStack *local_stack);
void showMaxElement(MyStack *local_stack);


