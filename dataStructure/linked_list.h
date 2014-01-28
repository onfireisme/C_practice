#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct node_tag{
	int node_value;
	struct	node_tag *next_node;
	struct  node_tag *previous_node;
}list_node;
//貌似这里真的没有必要加tail之类的。。因为head->previous就是tail
//current貌似也没有必要，因为基本上都是通过一路next过去的。
//怪不得，单向链表。。连个这个都没有。。因为没有必要。。
typedef struct list_tag{
	list_node head;
	list_node tail;
//	list_node current;
	int length;
}linked_list;
void insert_node(list_node *local_guard_node,int new_node_value);
list_node *list_search(list_node *local_guard_node,int local_value);
void delete_node(list_node *local_guard_node, int local_value);
list_node *node_malloc();
void create_list(list_node *local_guard_node);

