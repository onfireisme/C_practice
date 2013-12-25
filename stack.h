#include<stdio.h>
#include<malloc.h>
#define STACK_LENGTH 1000
typedef int node_type;
typedef struct {
	node_type node[STACK_LENGTH];
	int current_position;
}MyStack;
