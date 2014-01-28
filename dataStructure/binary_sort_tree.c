#include</home/onfire/C/binary_sort_tree.h>
//规定，right子树的值必须大于父节点，哪怕等于也不行。
//left子树的值就可以小于等于父节点了
//还要写一下中序遍历，前序遍历，后序便里，求二叉数深度，按层遍历，清空二叉树。
//以后函数名跟类的名称统统通过大小写混写的方式，变量名就加上斜下线
void PrintNodeValue(TreeNode *arbitrary_tree_node){
	if(arbitrary_tree_node==NULL){
		printf("the pointer has error\n");
	}
	else{
		printf("%d\n",arbitrary_tree_node->node_value);
	}
}
TreeNode *TreeNodeMalloc(){
	TreeNode *arbitrary_tree_node=(TreeNode *)malloc(sizeof(TreeNode));
	if(arbitrary_tree_node==NULL){
		exit(1);
		printf("failed to malloc memory to pointer");
	}
	arbitrary_tree_node->node_value=-1;
	arbitrary_tree_node->right_child_node=NULL;
	arbitrary_tree_node->left_child_node=NULL;
	arbitrary_tree_node->father_node=NULL;
	return arbitrary_tree_node;
}
TreeNode *InitBinaryTree(int node_value){
	TreeNode *root_node=TreeNodeMalloc();
	root_node->node_value=node_value;
	return root_node;
}
void InsertTreeNode(TreeNode *root_node,int node_value){
	//只需要确定father_node是否为空，不为空肯定就可以继续插入
	TreeNode *new_node=TreeNodeMalloc();
	new_node->node_value=node_value;
	TreeNode *father_node=root_node;
	//这个就是三层嵌套了。。再多一层就要考虑重新写了。
	//只能三层，再多就恶心了
	while(father_node!=NULL){
		if(node_value>father_node->node_value){
			if(father_node->right_child_node!=NULL){
				father_node=father_node->right_child_node;
			}
			else{
				father_node->right_child_node=new_node;
				new_node->father_node=father_node;
				break;
			}
		}
		else{
			if(father_node->left_child_node!=NULL){
				father_node=father_node->left_child_node;
			}
			else{
				father_node->left_child_node=new_node;
				new_node->father_node=father_node;
				break;
			}
		}
	}
}
//这个
TreeNode *TreeSearch(TreeNode *root_node, int searched_node_value){
	TreeNode *father_node=root_node;
	TreeNode *result_node;
	while(father_node!=NULL){
		if(father_node->node_value==searched_node_value){
			result_node=father_node;
			break;
		}
		if(searched_node_value>father_node->node_value){
			if(father_node->right_child_node!=NULL){
				father_node=father_node->right_child_node;
			}
			else{
				result_node=NULL;
				break;
			}
		}
		else if(searched_node_value<father_node->node_value){
			if(father_node->left_child_node!=NULL){
				father_node=father_node->left_child_node;
			}
			else{
				result_node=NULL;
				break;
			}
		}
	}
	return result_node;
}
// 记住，你找的最小节点，是根据给出的根节点的值求的，不同的根节点的值是不同的
TreeNode *TreeMinimumNode(TreeNode *temporary_node){
	TreeNode *next_node=temporary_node;
	while(next_node->left_child_node!=NULL){
		next_node=next_node->left_child_node;
	}
	return next_node;
}
TreeNode *TreeMaximumNode(TreeNode *temporary_node){
	TreeNode *next_node=temporary_node;
	while(next_node->right_child_node!=NULL){
		next_node=next_node->right_child_node;
	}
	return next_node;
}
//需找任意节点的后继节点,后继节点就是以任意节点为根节点。需找大于这个节点中的节点的中的最小值。
//基本上就
TreeNode *TreeSuccessor(TreeNode *temporary_node){
	TreeNode *TreeSuccessor;
	if(temporary_node->right_child_node!=NULL){
		TreeNode *next_node=temporary_node->right_child_node;
		while(next_node->left_child_node!=NULL){
			next_node=next_node->left_child_node;
		}
		TreeSuccessor=next_node;	
	}
	if(temporary_node->right_child_node==NULL){
		//这个时候要往上查找一个节点，这个节点是他的祖先节点。
		//同时这个祖先节点的左子树，也是个祖先节点的。
		TreeNode *father_node=temporary_node;
		while((father_node->father_node!=NULL)&&(father_node->father_node->node_value<father_node->node_value)){
			father_node=father_node->father_node;	
		}
		if(father_node->father_node!=NULL){
			TreeSuccessor=father_node->father_node;
		}
		else{
			TreeSuccessor=NULL;
		}
	}
	return TreeSuccessor;
}
void DeleteTreeNode(TreeNode *root_node,int node_value){
	TreeNode *result_node=TreeSearch(root_node,node_value);
	TreeNode *father_node=result_node->father_node;
	TreeNode *free_node;
	int left_child_node_check;
	if(father_node->node_value>result_node->node_value){
		left_child_node_check=TRUE;
	}
	else{
		left_child_node_check=FALSE;
	}
	if(result_node->left_child_node==NULL&&result_node->right_child_node==NULL){
		if(left_child_node_check){
			result_node->father_node->left_child_node=NULL;
		}
		else{
			result_node->father_node->right_child_node=NULL;
		}
		free_node=result_node;
	}
	else if(result_node->left_child_node!=NULL&&result_node->right_child_node!=NULL){
		//由于左右子树都有。。故跟那一个子节点换关键字都是可以的
		//我擦。当节点有左右两个节点的时候，是最麻烦的。。
		TreeNode *successor_node=TreeSuccessor(result_node);
		//这里可以递归的,直接调用本函数，删除这个后继节点就可以，不过为了提高可读性，就不使用了
		result_node->node_value=successor_node->node_value;
		//这里把后继节点删除掉
		if(successor_node->right_child_node!=NULL){
			if(successor_node->father_node->node_value>successor_node->node_value){
				successor_node->father_node->left_child_node=successor_node->right_child_node;	
				successor_node->right_child_node->father_node=successor_node->father_node;
			}
			else{
				successor_node->father_node->right_child_node=successor_node->right_child_node;	
				successor_node->right_child_node->father_node=successor_node->father_node;
			}
		}
		else{
			if(successor_node->father_node->node_value>successor_node->node_value){
				successor_node->father_node->left_child_node=NULL;
			}
			else{
				successor_node->father_node->right_child_node=NULL;
			}
		}
		free_node=successor_node;
	}
	else{
		if(left_child_node_check){
			if(result_node->left_child_node!=NULL){
				father_node->left_child_node=result_node->left_child_node;
				result_node->left_child_node->father_node=father_node;
			}
			else{
				father_node->left_child_node=result_node->right_child_node;
				result_node->right_child_node->father_node=father_node;
			}
		}
		else{
			if(result_node->left_child_node!=NULL){
				father_node->right_child_node=result_node->left_child_node;
				result_node->left_child_node->father_node=father_node;
			}
			else{
				father_node->right_child_node=result_node->right_child_node;
				result_node->right_child_node->father_node=father_node;
			}
		}
		free_node=result_node;
	}
	free(free_node);
}
//三种遍历方式，把中间的节点除去后，都是先便利left,之后right。一直都是这个顺序，思考下，为什么？
//Left subtree, current node, right subtree (LDR)中序遍历
void tree_traversal_left_d_right(TreeNode *tree_node){
	//先左子树，后中间，最后右子树
	//很明显，这种结构用递归是最好的办法
	if(tree_node->left_child_node!=NULL||tree_node->right_child_node!=NULL){
		if(tree_node->left_child_node!=NULL){
			tree_traversal_left_d_right(tree_node->left_child_node);
		}
		PrintNodeValue(tree_node);
		if(tree_node->right_child_node!=NULL){
			tree_traversal_left_d_right(tree_node->right_child_node);
		}
	}
	else{
		PrintNodeValue(tree_node);
	}
}
//left right c LRD后序遍历
void tree_traversal_left_right_d(TreeNode *tree_node){
	if(tree_node->left_child_node!=NULL||tree_node->right_child_node!=NULL){
		if(tree_node->left_child_node!=NULL){
			tree_traversal_left_right_d(tree_node->left_child_node);
		}
		if(tree_node->right_child_node!=NULL){
			tree_traversal_left_right_d(tree_node->right_child_node);
		}
		PrintNodeValue(tree_node);
	}
	else{
		PrintNodeValue(tree_node);
	}
}
//c left right DLR前序便利
void tree_traversal_d_left_right(TreeNode *tree_node){
	if(tree_node->left_child_node!=NULL||tree_node->right_child_node!=NULL){
		PrintNodeValue(tree_node);
		if(tree_node->left_child_node!=NULL){
			tree_traversal_d_left_right(tree_node->left_child_node);
		}
		if(tree_node->right_child_node!=NULL){
			tree_traversal_d_left_right(tree_node->right_child_node);
		}
	}
	else{
		PrintNodeValue(tree_node);
	}
}
//这个，也可以考虑使用递归的方式
int TreeDepth(TreeNode *tree_node){
	int tree_depth;
	int left_tree_depth;
	int right_tree_depth;
	if(tree_node->left_child_node!=NULL||tree_node->right_child_node!=NULL){
		if(tree_node->left_child_node!=NULL&&tree_node->right_child_node!=NULL){
			left_tree_depth=TreeDepth(tree_node->left_child_node);
			right_tree_depth=TreeDepth(tree_node->right_child_node);
			if(left_tree_depth>right_tree_depth){
				tree_depth=left_tree_depth+1;
			}
			else{
				tree_depth=right_tree_depth+1;
			}
		}
		else if(tree_node->left_child_node!=NULL&&tree_node->right_child_node==NULL){
			left_tree_depth=TreeDepth(tree_node->left_child_node);
			tree_depth=left_tree_depth+1;
		}
		else if(tree_node->right_child_node!=NULL&&tree_node->left_child_node==NULL){
			right_tree_depth=TreeDepth(tree_node->right_child_node);
			tree_depth=right_tree_depth+1;
		}
	}
	else{
		tree_depth=1;
	}
	return tree_depth;
}
//不用递归的话，停止条件是什么？？
//恩，很多时候迭代有个条件，就是它的停止条件非常好找，你可以快速找到，并且进行判断
void TreeLevelTraversal(TreeNode *root_node){
	//firstly,save all the nodes to the array
	TreeNode **tree_node_array=(TreeNode **)malloc(ARRAY_LENGTH*SIZEOFP);
	tree_node_array[0]=root_node;
	printf("%d\n",root_node->node_value);
	int array_length=1;
	int current_node_position=0;
	while(current_node_position<array_length){
		//save all the nodes to the array
		int LastOfCurrentLevel=array_length;
		while(current_node_position<LastOfCurrentLevel){
			printf("%d",tree_node_array[current_node_position]->node_value);
			if(tree_node_array[current_node_position]->left_child_node!=NULL){
				tree_node_array[array_length]=tree_node_array[current_node_position]->left_child_node;
				array_length++;
			}
			if(tree_node_array[current_node_position]->right_child_node!=NULL){
				tree_node_array[array_length]=tree_node_array[current_node_position]->right_child_node;
				array_length++;
			}
			current_node_position++;
		}
		printf("\n");
	}
	free(*tree_node_array);
}
void ReMallocNodeArray(TreeNode **tree_node_array){
	ARRAY_COUNT++;
	*tree_node_array=(TreeNode *)realloc(*tree_node_array,ARRAY_COUNT*ARRAY_LENGTH*sizeof(TreeNode));	
}
int main(void){
	/*
	TreeNode *tree_root_node=InitBinaryTree(10);
	InsertTreeNode(tree_root_node,7);
	InsertTreeNode(tree_root_node,4);
	InsertTreeNode(tree_root_node,3);
	InsertTreeNode(tree_root_node,6);
	InsertTreeNode(tree_root_node,5);
	InsertTreeNode(tree_root_node,9);
	InsertTreeNode(tree_root_node,8);
	InsertTreeNode(tree_root_node,20);
	InsertTreeNode(tree_root_node,17);
	InsertTreeNode(tree_root_node,15);
	InsertTreeNode(tree_root_node,18);
	InsertTreeNode(tree_root_node,14);
	InsertTreeNode(tree_root_node,16);
	InsertTreeNode(tree_root_node,19);
	InsertTreeNode(tree_root_node,12);
	TreeLevelTraversal(tree_root_node);
//	TreeNode *search_result=TreeSearch(tree_root_node,17);
//	TreeNode *minimum_node=TreeMinimumNode(search_result);
//	TreeNode *maximum_node=TreeMaximumNode(search_result);
	*/
	return 0;
}
