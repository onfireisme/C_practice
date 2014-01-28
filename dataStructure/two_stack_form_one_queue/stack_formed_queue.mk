stack_formed_queue:two_stack_form_one_queue.o stack.o
	cc -o stack_formed_queue two_stack_form_one_queue.o stack.o
two_stack_form_one_queue.o:two_stack_form_one_queue.c two_stack_form_one_queue.h 
	cc -c two_stack_form_one_queue.c
stack.o:stack.c stack.h
	cc -c stack.c
clean:
	rm stack_formed_queue stack.o two_stack_form_one_queue.o
