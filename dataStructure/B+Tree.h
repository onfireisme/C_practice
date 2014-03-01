#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define ARRAYLENGTH 100
#define RANDOMMAX 100
#define random(x)(rand()%x)
#define MIDDLE 2
#define DEGREE 2
#define LEAFNODEPOINTERARRAYLENGTH 100
#define UNLEAFNODEPOINTERARRAYLENGTH 100
#define LEAF 1
#define UNLEAF 0
#define POINTERSIZE (sizeof(void *))
#define NEGATIVE -1
#define KEYVALUENUMBER 20
#define LOOPLIMIT 10
typedef int BOOL;
typedef int KeyType;
typedef int NodeType;
typedef const int * constPointerInt;
/*
 * Important Defination
 * 1.the sequence of the key value is from little to large
 * after consideration,it seems that the linked_list maybe a better choice
 * the most cost operation is at insert,we need to R
 * but when you delete the node,it may consume fewer time
 */
//the choice to use two kinds of node is really a bad idea
typedef struct MyNode{
	/*
	 * the question is ,the more attribute you set,the more you need to set
	 * once you forget to set it ,then something will wrong
	 */
	struct MyNode *fatherNode;
	struct MyNode *rightBrotherNode;
	struct MyNode **childNodePointerArray;
	int positionAtFatherNode;
	KeyType keyValueArray[2*DEGREE-1];
	int pointerCurrentIndex;
	int keyValueCurrentIndex;
	NodeType nodeType;
}BTreeNode;
typedef struct {
	BTreeNode *leafNode;
	int resultPosition;
}SearchResult;
//initial part
void BTreeCreate();
void initialNode(BTreeNode **newNode,BTreeNode *fatherNode,NodeType nodeType
		,int positionAtFatherNode);
void generateRandomTree(BTreeNode **rootNode,int treeKeyValueCount);
/*
 *split the node
 */
BTreeNode *splitNode(BTreeNode *node);
void keyValueArraySplit(KeyType *keyValueArrayOne,KeyType *keyValueArrayTwo);
void pointerArraySplit(BTreeNode **pointerArrayOne,BTreeNode **pointerArrayTwo);
BOOL isNodeFull(BTreeNode *node);
/*
 * insert the keyvalue and child pointer
 */
void BTreeInsert(BTreeNode *rootNode,KeyType keyValue);
void keyValueInsert(BTreeNode *node,KeyType keyValue);
void pointerInsert(BTreeNode *fatherNode,int insertPostion,
		BTreeNode *pointer);
void specifiedKeyValueInsert(BTreeNode *fatherNode,int insertPostion,KeyType keyValue);
BTreeNode *findPointer(BTreeNode *node,KeyType keyValue);
//search 
SearchResult BTreeSearch(BTreeNode *rootNode,KeyType keyValue);
/*
 * delete
 */
void BTreeDelete(BTreeNode *rootNode,KeyType keyValue);
/*
 * other functions 
 */
void generateRandomIntArray(KeyType *array,int arrayLength);
//show the array
void showTheKeyValueArray(BTreeNode *node);
void showThePointerArray(BTreeNode *node);
void showTheArray(KeyType *array,int arrayLength);
//show the tree
void showTheTreeByLevel(BTreeNode *rootNode);
//xor function
void xorSwap(KeyType *numOne,KeyType *numTwo);
void pointerXorSwap(BTreeNode **pointerOne,BTreeNode **pointerTwo);

//global variables
BTreeNode *globalRootNode;
KeyType globalKeyValueArray[20];
