#include</home/wangyan/C/linked_list.h>
//问题原因终于找到了，我把链表整的太复杂了。。
//不过，其实可以加一个list类的，这样会省去很多的麻烦事情，长度，不过关于头节点，尾部节点
//不的不说，创建一个哨兵节点比创建一个头节点，尾节点，要省去很多事情，不用加那么多的条件限制
void insert_node(list_node *local_guard_node,int new_node_value){
	//new_node初始化并且赋值
	list_node *new_node=node_malloc();
	new_node->node_value=new_node_value;
	//这里进行节点的对应操作
	new_node->previous_node=local_guard_node->previous_node;
	local_guard_node->previous_node->next_node=new_node;
	new_node->next_node=local_guard_node;
	local_guard_node->previous_node=new_node;
}
list_node *node_malloc(){
	list_node *local_node=(list_node *)malloc(sizeof(list_node));
	if(local_node==NULL){
		printf("failed to malloc memory to list_node");
		exit(1);
	}
	return local_node;
}
//在创建链表的同时，创建哨兵节点
void create_list(list_node *local_guard_node){
	local_guard_node->node_value=-1;
	local_guard_node->next_node=local_guard_node;
	local_guard_node->previous_node=local_guard_node;
}
list_node *list_search(list_node *local_guard_node,int local_node_value){
	int count=0;
	list_node *local_node;
	local_node=local_guard_node->next_node;
	while(local_node->node_value!=-1&&local_node->node_value!=local_node_value){
		local_node=local_node->next_node;
		count++;
	}
	return local_node;
}
void delete_node(list_node *local_guard_node, int local_value){
	list_node *local_node;
	local_node=list_search(local_guard_node,local_value);
	local_node->previous_node->next_node=local_node->next_node;
	local_node->next_node->previous_node=local_node->previous_node;
	free(local_node);
	//同时删除掉已经赋予的空间
}
void show_list(list_node *local_guard_node){
	list_node *local_node;
	local_node=local_guard_node->next_node;
	int count=1;
	while(local_node->node_value!=-1){
		printf("the %d node's value is %d\n",count,local_node->node_value);
		local_node=local_node->next_node;
		count++;
	}
}
//这个是结束了之后，释放所有的资源的函数
void free_node(list_node *guard_node){
	list_node *local_next_node=local_guard_node->next_node;
	list_node *free_node;
	while(local_next_node->node_value!=-1){
		free_node=local_next_node;
		local_next_node=local_next_node->next_node;
		free(free_node);
	}

}
int main(){
	list_node guard_node; 
	create_list(&guard_node);
	insert_node(&guard_node,2);
	insert_node(&guard_node,3);
	insert_node(&guard_node,4);
	insert_node(&guard_node,5);
	show_list(&guard_node);
	delete_node(&guard_node,3);
	show_list(&guard_node);
	return 0;
}
