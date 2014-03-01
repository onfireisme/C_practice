#include</home/wangyan/C_practice/dataStructure/B+Tree.h>
//how to release the alocated node?I can write a recursion to do it.
/*
 * build tree
 */
void BTreeCreate(){
	initialNode(&globalRootNode,NULL,UNLEAF);
}
void initialNode(BTreeNode **newNode,BTreeNode *fatherNode,NodeType nodeType){
	*newNode=(BTreeNode *)malloc(sizeof(BTreeNode));
	(*newNode)->keyValueCurrentIndex=-1;
	if(nodeType==UNLEAF){
		(*newNode)->childNodePointerArray=(BTreeNode **)malloc(2*DEGREE*POINTERSIZE);
		(*newNode)->nodeType=UNLEAF;
	}
	else{
		(*newNode)->nodeType=LEAF;
		(*newNode)->childNodePointerArray=NULL;
	}
	if(fatherNode!=NULL){
		(*newNode)->fatherNode=fatherNode;
	}
	else{
		(*newNode)->fatherNode=NULL;
	}
	(*newNode)->childNodePointerCurrentIndex=NEGATIVE;
	(*newNode)->keyValueCurrentIndex=NEGATIVE;
	(*newNode)->rightBrotherNode=NULL;
}
void generateRandomTree(BTreeNode **rootNode,int treeKeyValueCount){
	int i=0;
	for(i;i<treeKeyValueCount;i++){
		globalKeyValueArray[i]=random(100);
		BTreeInsert(*rootNode,globalKeyValueArray[i]);
	}
	printf("\n");
}
/*
 * insert
 */
void BTreeInsert(BTreeNode *rootNode,KeyType keyValue){
	if(rootNode->childNodePointerCurrentIndex==NEGATIVE){
		//the special case,that we don't have the fisrt leaf node
		BTreeNode *newNode;
		initialNode(&newNode,rootNode,LEAF);
		rootNode->childNodePointerArray[++(rootNode->childNodePointerCurrentIndex)]=newNode;
		newNode->rightBrotherNode=NULL;
		keyValueInsert(newNode,keyValue);
		return;
	}
	BTreeNode *node=rootNode;
	/*
	 * first step,we find the leaf node that we need to insert the keyValue
	 * during this procudure,we split the full leaf or unleaf nodes that we meet
	 */
	while(node->nodeType==UNLEAF){
		if(!isNodeFull(node)){
			node=findPointer(node,keyValue);
		}
		else{
			if(node->keyValueArray[DEGREE-1]>keyValue){
				splitNode(node);
			}
			else{
				node=splitNode(node)->rightBrotherNode;
			}
			node=findPointer(node,keyValue);
		}
	}
	/*
	 * second,split the leaf node if it was full.
	 * then insert the value to the leaf
	 */
	if(!isNodeFull(node)){
		keyValueInsert(node,keyValue);
	}
	else{
		if(keyValue>node->keyValueArray[DEGREE-1]){
			node=splitNode(node)->rightBrotherNode;
			keyValueInsert(node,keyValue);
		}
		else{
			splitNode(node);
			keyValueInsert(node,keyValue);
		}
	}
}
BTreeNode *splitNode(BTreeNode *node){
	//check again ,if the node is full ,if not show the error
	if(!isNodeFull(node)){
		printf("error at splitNode fucntion!\n the node is not full!\n");
		return;
	}
	/*
	 * first thing,the node will divide into two node,we will return the left leaf_node
	 * second thing,the keyValue[0] always larger all the keyValue of the 
	 * leaf_node childNodePointer[0](why? you can observe the way the node split,then you will know)
	 */
	BTreeNode *newNode;
	BTreeNode *fatherNode=node->fatherNode;;
	//firstly,when the node is root node ,something will be different
	if(fatherNode==NULL){
		//initial the new root node
		BTreeNode *newRootNode;
		initialNode(&newRootNode,NULL,UNLEAF);
		globalRootNode=newRootNode;
		//set the node
		node->fatherNode=newRootNode;
		//set the new root node
		fatherNode=newRootNode;
		fatherNode->childNodePointerArray[++(fatherNode->childNodePointerCurrentIndex)]
			=node;
		fatherNode->rightBrotherNode=NULL;
	}
	//when the node is not root node
	if(node->nodeType==LEAF){
		initialNode(&newNode,node->fatherNode,LEAF);
	}
	else{
		initialNode(&newNode,node->fatherNode,UNLEAF);
		//split the array of pointer to the new node
		pointerArraySplit(node,newNode);
		node->childNodePointerCurrentIndex=DEGREE-1;
		newNode->childNodePointerCurrentIndex=DEGREE-1;
	}
	//insert the address of the new node to the father node,after the old node
	pointerInsert(fatherNode,node,newNode);
	//set the rightBrotherNode
	if(node->rightBrotherNode==NULL){
		newNode->rightBrotherNode=NULL;
		node->rightBrotherNode=newNode;
	}
	else{
		newNode->rightBrotherNode=node->rightBrotherNode;
		node->rightBrotherNode=newNode;
	}
	//insert the key value to the father node
	KeyType insertedKeyValue=node->keyValueArray[DEGREE-1];
	keyValueInsert(fatherNode,insertedKeyValue);
	//split the array of key value to the new node
	keyValueArraySplit(node->keyValueArray,newNode->keyValueArray);
	node->keyValueCurrentIndex=DEGREE-2;
	newNode->keyValueCurrentIndex=DEGREE-2;
	return node;
}
void keyValueArraySplit(KeyType *keyValueArrayOne,KeyType *keyValueArrayTwo){
	int i=0;
	for(i;i<DEGREE-1;i++){
		keyValueArrayTwo[i]=keyValueArrayOne[i+DEGREE];
	}
}
void pointerArraySplit(BTreeNode *oldNode,BTreeNode *newNode){
	/*
	 * I make a huge mistake,you split the pointer to a new node
	 * but the child node still regard the old node as its father node
	 */
	int i=0;
	for(i;i<DEGREE;i++){
		newNode->childNodePointerArray[i]=oldNode->childNodePointerArray[i+DEGREE];
		newNode->childNodePointerArray[i]->fatherNode=newNode;
	}
}
BTreeNode *findPointer(BTreeNode *node,KeyType keyValue){
	//the special case ,when it has no keyValue
	if(node->keyValueCurrentIndex==NEGATIVE){
		if(node->childNodePointerCurrentIndex==0){
			return node->childNodePointerArray[0];
		}
		else{
			printf("error!!the pointer array has some questions!\n");
			return node->childNodePointerArray[0];
		}
	}
	int flag=0;
	//I make a mistake here,that if the
	while(flag<=node->keyValueCurrentIndex&&
			node->keyValueArray[flag]<keyValue){
		flag++;
	}
	return node->childNodePointerArray[flag];
}
void pointerInsert(BTreeNode *fatherNode,BTreeNode *oldNode,
		BTreeNode *newNode){
	if(oldNode==NULL){
		fatherNode->childNodePointerArray[0]=newNode;
	}
	int countFlag=fatherNode->childNodePointerCurrentIndex;
	fatherNode->childNodePointerArray[++(fatherNode->childNodePointerCurrentIndex)]
		=newNode;
	while(fatherNode->childNodePointerArray[countFlag]!=oldNode){
		pointerXorSwap(&fatherNode->childNodePointerArray[countFlag],
				&fatherNode->childNodePointerArray[countFlag+1]);
		countFlag--;
		if(countFlag==-1){
			printf("error at pointerInsert function!!\n"
					"could not find the pointer at father node\n");
		}
	}
}
void specifiedKeyValueInsert(BTreeNode *fatherNode,int insertPostion,
		KeyType keyValue){
	if(fatherNode->keyValueCurrentIndex==2*DEGREE-2){
		printf("error !!!\nthe node is full we can not insert more!\n");
		return;
	}
	//remembet the insertPostion is count from 0,not from 1
	int endFlag=fatherNode->keyValueCurrentIndex;
	if(insertPostion>endFlag+1){
		printf("error at specified key value function\n"
				"the insertPostion is larger than the endFlag+1\n");
		return;
	}
	if(insertPostion<0){
		insertPostion=0;
	}
	endFlag++;
	fatherNode->keyValueCurrentIndex++;
	KeyType *keyValueArray=fatherNode->keyValueArray;
	keyValueArray[endFlag]=keyValue;
	while(endFlag>0&&endFlag!=insertPostion){
		xorSwap(&keyValueArray[endFlag],&keyValueArray[endFlag-1]);
		endFlag--;
	}
}
void keyValueInsert(BTreeNode *node,KeyType keyValue){
	if(node->keyValueCurrentIndex==2*DEGREE-2){
		printf("error!!!\nthe node is full we can not insert more!\n");
		return;
	}
	if(node->keyValueCurrentIndex==-1){
		node->keyValueArray[++(node->keyValueCurrentIndex)]=keyValue;
		return;
	}
	node->keyValueArray[++(node->keyValueCurrentIndex)]=keyValue;
	int flag=node->keyValueCurrentIndex;
	while(flag>0&&node->keyValueArray[flag]<node->keyValueArray[flag-1]){
		xorSwap(&node->keyValueArray[flag],&node->keyValueArray[flag-1]);
		flag--;
	}
}
/*
 * other functions
 */
void xorSwap(KeyType *numOne,KeyType *numTwo){
	if(numOne==numTwo){
		return;
	}
	*numOne=(*numOne)^(*numTwo);
	*numTwo=(*numOne)^(*numTwo);
	*numOne=(*numOne)^(*numTwo);
}
void pointerXorSwap(BTreeNode **pointerOne,BTreeNode **pointerTwo){
	if(pointerOne==pointerTwo){
		return;
	}
	void *temp[1];
	temp[0]=*pointerTwo;
	*pointerTwo=*pointerOne;
	*pointerOne=temp[0];
	/*
	 * why it doesn't work?
	 *pointerOne=(*pointerOne)^(*pointerTwo);
	 *pointerTwo=(*pointerOne)^(*pointerTwo);
	 *pointerOne=(*pointerOne)^(*pointerTwo);
	 */
}
void showTheKeyValueArray(BTreeNode *node){
	int i=0;
	for(i;i<=node->keyValueCurrentIndex;i++){
		printf("%d ",node->keyValueArray[i]);
	}
	printf("\n");
}
void showThePointerArray(BTreeNode *node){
	int i=0;
	for(i;i<=node->childNodePointerCurrentIndex;i++){
		printf("%p ",node->childNodePointerArray[i]);
	}
	printf("\n");
}
void showTheTreeByLevel(BTreeNode *rootNode){
	int levelCount=1;
	int nodeCount=1;
	int keyValueCount=0;
	BTreeNode *node=rootNode;
	BTreeNode *tempNode;
	printf("the unleaf key value\n\n");
	while(node->nodeType==UNLEAF){
		tempNode=node->childNodePointerArray[0];
		nodeCount=1;
		printf("the level %d\n",levelCount);
		while(node!=NULL){
			printf("the %d unleaf node,the address of the node is %p,"
					"the father node is %p\n",
					nodeCount,node,node->fatherNode);
			showTheKeyValueArray(node);
			keyValueCount=keyValueCount+node->keyValueCurrentIndex+1;
			node=node->rightBrotherNode;
			nodeCount++;
		}
		printf("\n");
		node=tempNode;
		levelCount++;
	}
	printf("\n");
	printf("the leaf key value\n\n");
	nodeCount=1;
	while(node!=NULL){
		printf("the %d leaf node,the node address is%p,"
				"the father node is %p\n",
				nodeCount,node,node->fatherNode);
		showTheKeyValueArray(node);
		keyValueCount=keyValueCount+node->keyValueCurrentIndex+1;
		node=node->rightBrotherNode;
		nodeCount++;
	}
//	printf("the total key value number is %d \n",keyValueCount);
}
void showTheArray(KeyType *array,int arrayLength){
	int i=0;
	for(i;i<arrayLength;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}
void generateRandomIntArray(KeyType *array,int arrayLength){
	int i=0;
	for(i;i<arrayLength;i++){
		array[i]=random(RANDOMMAX);
	}
}
BOOL isNodeFull(BTreeNode *node){
	if(node->nodeType==LEAF){
		if(node->keyValueCurrentIndex<(2*DEGREE-2)){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	else{
		if(node->keyValueCurrentIndex==(2*DEGREE-2)){
			if(node->childNodePointerCurrentIndex==(2*DEGREE-1)){
				return TRUE;
			}
			else{
				printf("error,the key value array is full ,but the pointer array is not full!!\n");
				return FALSE;
			}
		}
		else{
			return FALSE;
		}
	}
}
/*
 * delete
 */
void BTreeDelete(BTreeNode *rootNode,KeyType keyValue){
	/*
	 * first,we need to consider when the key value number is smalller than DEGREE-1
	 * second,we need to consider the situation,when the deleted key value belong to
	 * the unleaf node,not the leaf node,then we need to get a new key value to replace it
	 */
	//first step,we find the position of the key value
	
	//if the key value is belong to leaf node,then decide if we should combine node
	
	//if the key value belong to the unleaf node,then decide if we need combine node
}
void nodeCombine(){
}
/*
 * search
 */
SearchResult BTreeSearch(BTreeNode *rootNode,KeyType keyValue){
	BTreeNode *node=rootNode;
	SearchResult result;
	int countFlag;
	int levelCount=1;
	// find the leaf node
	while(node->nodeType==UNLEAF){
		countFlag=0;
		while(node->keyValueCurrentIndex>=countFlag&&keyValue>=node->keyValueArray[countFlag]){
			if(keyValue==node->keyValueArray[countFlag]){
				result.leafNode=node;
				result.resultPosition=countFlag;
				printf("the result is from unleaf node,at level %d\n",levelCount);
				printf("the value is %d the address of result node %p,the position of result at node %d\n",
						keyValue,result.leafNode,result.resultPosition);
				return result;
			}
			countFlag++;
		}
		levelCount++;
		node=node->childNodePointerArray[countFlag];
	}
	//search at the leaf node
	countFlag=0;
	while(countFlag<=node->keyValueCurrentIndex){
		if(keyValue==node->keyValueArray[countFlag]){
			result.leafNode=node;
			result.resultPosition=countFlag;
			printf("the result is from leaf node\n");
			printf("the value is %d the address of result node %p,the position of result at node %d\n",
					keyValue,result.leafNode,result.resultPosition);
			return result;
		}
		countFlag++;
	}
	printf("counld not find the key value,please set the right key value\n");
	return result;
}
int main(void){
	BTreeCreate();
	generateRandomTree(&globalRootNode,KEYVALUENUMBER);
	showTheArray(globalKeyValueArray,KEYVALUENUMBER);
	showTheTreeByLevel(globalRootNode);
//	showTheTreeByLevel(globalRootNode);
//	showThePointerArray(globalRootNode);
	SearchResult result=BTreeSearch(globalRootNode,globalKeyValueArray[0]);
	return 1;
	/*
	BTreeNode node1;
	BTreeNode node2;
	BTreeNode node3;
	BTreeNode node4;
	globalRootNode->childNodePointerArray[++(globalRootNode->childNodePointerCurrentIndex)]
		=&node1;
	globalRootNode->childNodePointerArray[++(globalRootNode->childNodePointerCurrentIndex)]
		=&node2;
	globalRootNode->childNodePointerArray[++(globalRootNode->childNodePointerCurrentIndex)]
		=&node3;
	globalRootNode->childNodePointerArray[++(globalRootNode->childNodePointerCurrentIndex)]
		=&node4;
	globalRootNode->keyValueArray[++(globalRootNode->keyValueCurrentIndex)]
		=4;
	globalRootNode->keyValueArray[++(globalRootNode->keyValueCurrentIndex)]
		=4;
	globalRootNode->keyValueArray[++(globalRootNode->keyValueCurrentIndex)]
		=4;
	splitNode(globalRootNode);
	*/
}
