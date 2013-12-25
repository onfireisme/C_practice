//this one should can been used widely
#include</home/onfire/C/stack.h>
void init_stack(MyStack *temp_stack){
	temp_stack->current_position=-1;
}
void pop(MyStack *temp_stack){
	if(temp_stack->current_position==0){
		printf("the stack is null now!");
		return ;
	}
	temp_stack->current_position--;
}
void push(MyStack *temp_stack,node_type node_value){
	temp_stack->node[++temp_stack->current_position]=node_value;
}
int main(){
	MyStack stack;
	init_stack(&stack);
	int x=5;
	push(&stack,x);
	push(&stack,++x);
	pop(&stack);
	printf("%d",stack.node[stack.current_position]);
}
