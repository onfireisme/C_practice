#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define NIL -1
#define LEFT_NODE 0
#define RIGHT_NODE 1
#define TRUE 1
#define FALSE 0
#define ARRAY_LENGTH 1
/*
 if(1){
	printf("test\n");
 }
 输出的是test
 if(0){
	printf("test\n");
 }
 无输出。。所以。。其实这样也是可以的。。
 */
typedef struct tree_node_tag{
	int node_value;
//	int node_position;
//	为什么不加上node_position这个值呢？是因为当你删除节点的时候，这个也会变化。
//	所以，反而会增加很多不确定性。如果你在添加后，无法判断是否利大于弊，这个时候就不要添加了。
//	simple is better
	struct tree_node_tag *father_node;
	struct tree_node_tag *left_child_node;
	struct tree_node_tag *right_child_node;
}TreeNode;
int *GlobalPointTemp;
int static const SIZEOFP=sizeof(GlobalPointTemp);
int static ARRAY_COUNT=1;
//关于是否需要建立一个树的结构体，恩，暂时应该是不需要的。
//不过，我需要思考一件事情，就是如果使用php，js等语言的话，改如何实现这样的结构呢？
TreeNode *tree_node_malloc();
void PrintNodeValue(TreeNode *arbitrary_tree_node);
TreeNode *TreeNodeMalloc();
TreeNode *InitBinaryTree(int node_value);
void InsertTreeNode(TreeNode *root_node,int node_value);
TreeNode *TreeSearch(TreeNode *root_node, int searched_node_value);
TreeNode *TreeMinimumNode(TreeNode *temporary_node);
TreeNode *TreeMaximumNode(TreeNode *temporary_node);
void TreeLevelTraversal(TreeNode *tree_node);


