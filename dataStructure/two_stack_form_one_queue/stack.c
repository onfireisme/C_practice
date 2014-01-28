//this one should can been used widely
#include</home/wangyan/C_practice/stack.h>
void initialStack(MyStack *temp_stack){
	temp_stack->nodeArray=(node_type*)malloc(STACK_LENGTH*sizeof(node_type));
	temp_stack->maxNodeIndexArray=(node_type*)malloc(STACK_LENGTH*sizeof(node_type));
	temp_stack->current_position=-1;
	temp_stack->stack_array_count=1;
	temp_stack->maxPosition=NEGATIVE_SINGNAL;
	temp_stack->maxNodeIndexArray[temp_stack->maxPosition]=0;
}
void push(MyStack *temp_stack,node_type node_value){
	temp_stack->nodeArray[++temp_stack->current_position]=node_value;
	if(node_value>maxStackElement(temp_stack)){
		temp_stack->maxPosition++;
		temp_stack->maxNodeIndexArray[temp_stack->maxPosition]=temp_stack->current_position;
	}
}
void pop(MyStack *temp_stack){
	if(temp_stack->current_position==-1){
		printf("the stack is null now!");
		return ;
	}
	if(temp_stack->current_position==
			temp_stack->maxNodeIndexArray[temp_stack->maxPosition]){
		//because when the maxPosition become -1 ,then the stack must be null
		//think about it
		temp_stack->maxPosition--;
	}
	temp_stack->current_position--;
}
void reMalloc(MyStack *temp_stack){
	temp_stack->stack_array_count++;
	temp_stack->nodeArray=(node_type *)realloc(temp_stack->nodeArray,temp_stack->stack_array_count*
			STACK_LENGTH*sizeof(node_type));
	temp_stack->maxNodeIndexArray=(node_type *)realloc(temp_stack->maxNodeIndexArray,
			temp_stack->stack_array_count*STACK_LENGTH*sizeof(node_type));
}
//this function return the max element
node_type maxStackElement(MyStack *temp_stack){
	if(temp_stack->maxPosition==-1){
		return NEGATIVE_SINGNAL;
	}
	else{
		return temp_stack->nodeArray[temp_stack->
			maxNodeIndexArray[temp_stack->maxPosition]];
	}
}
void showStack(MyStack *temp_stack){
	int i=0;
	for(i;i<=temp_stack->current_position;i++){
		printf("%d ",temp_stack->nodeArray[i]);
	}
	printf("\n");
}
void freeStack(MyStack *local_stack){
	free(local_stack->nodeArray);
	free(local_stack->maxNodeIndexArray);
}
void showMaxStackElement(MyStack *local_stack){
	printf("%d ",maxStackElement(local_stack));
}
	/*
	MyStack stack;
	initialStack(&stack);
	int x=5;
	push(&stack,x);
	push(&stack,++x);
	push(&stack,--x);
	push(&stack,--x);
	x=7;
	push(&stack,x);
//	pop(&stack);
	showMaxElement(&stack);
//	showStack(&stack);
	freeStack(&stack);
//	printf("%d",stack.node[stack.current_position]);
*/

