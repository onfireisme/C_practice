#include</home/wangyan/C_practice/dataStructure/B+Tree.h>
//let us assume the value is always positive

//how to release the alocated node?I can write a recursion to do it.
void BTreeCreate(){
	initialNode(&globalRootNode,NULL,UNLEAF,NEGATIVE);
}
void initialNode(BTreeNode **newNode,BTreeNode *fatherNode,NodeType nodeType
		,int positionAtFatherNode){
	*newNode=(BTreeNode *)malloc(sizeof(BTreeNode));
	(*newNode)->keyValueCurrentIndex=-1;
	if(nodeType==UNLEAF){
		(*newNode)->childNodePointerArray=(BTreeNode **)malloc(2*DEGREE*POINTERSIZE);
		(*newNode)->nodeType=UNLEAF;
	}
	else{
		(*newNode)->nodeType=LEAF;
	}
	if(fatherNode!=NULL){
		/*
		 * I should insert the pointer to the pointer array after it was initialed
		 * why?becuase it makes procedure simpler
		 */
		(*newNode)->fatherNode=fatherNode;
		(*newNode)->positionAtFatherNode=positionAtFatherNode;
		pointerInsert(fatherNode,
				positionAtFatherNode,*newNode);
	}
	else{
		(*newNode)->fatherNode=NULL;
		(*newNode)->positionAtFatherNode=NEGATIVE;
	}
	(*newNode)->pointerCurrentIndex=NEGATIVE;
	(*newNode)->keyValueCurrentIndex=NEGATIVE;
}
BTreeNode *splitNode(BTreeNode *node){
	//check again ,if the node is full ,if not show the error
	if(!isNodeFull(node)){
		printf("error! the node is not full!\n");
		return;
	}
	/*
	 * first thing,the node will divide into two node,we will return the left leaf_node
	 * second thing,the keyValue[0] always larger all the keyValue of the 
	 * leaf_node childNodePointer[0](why? you can observe the way the node split,then you will know)
	 */
	BTreeNode *newNode;
	BTreeNode *fatherNode=node->fatherNode;;
	int positionAtFatherNode=node->positionAtFatherNode;
	//firstly,when the node is root node ,something will be different
	if(fatherNode==NULL){
		//initial the new root node
		BTreeNode *newRootNode;
		initialNode(&newRootNode,NULL,UNLEAF,NEGATIVE);
		globalRootNode=newRootNode;
		//set the node
		node->fatherNode=newRootNode;
		node->positionAtFatherNode=0;
		//set the new node
		fatherNode=newRootNode;
		fatherNode->childNodePointerArray[++(fatherNode->pointerCurrentIndex)]
			=node;
		fatherNode->rightBrotherNode=NULL;
		positionAtFatherNode=node->positionAtFatherNode;
	}
	//when the node is not root node
	if(node->nodeType==LEAF){
		initialNode(&newNode,node->fatherNode,LEAF,positionAtFatherNode+1);
	}
	else{
		initialNode(&newNode,node->fatherNode,UNLEAF,positionAtFatherNode+1);
		//split the array of pointer to the new node
		pointerArraySplit(node->childNodePointerArray,newNode->childNodePointerArray);
		node->pointerCurrentIndex=DEGREE-1;
		newNode->pointerCurrentIndex=DEGREE-1;
	}
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
	specifiedKeyValueInsert(fatherNode,positionAtFatherNode-1,
			insertedKeyValue);
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
void pointerArraySplit(BTreeNode **pointerArrayOne,BTreeNode **pointerArrayTwo){
	int i=0;
	for(i;i<DEGREE;i++){
		pointerArrayTwo[i]=pointerArrayOne[i+DEGREE];
	}
}
void BTreeInsert(BTreeNode *rootNode,KeyType keyValue){
	if(rootNode->pointerCurrentIndex==NEGATIVE){
		//the special case,that we don't have the fisrt 
		BTreeNode *newNode;
		initialNode(&newNode,rootNode,LEAF,0);
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
BTreeNode *findPointer(BTreeNode *node,KeyType keyValue){
	//the special case ,when it has no keyValue
	if(node->keyValueCurrentIndex==NEGATIVE){
		if(node->pointerCurrentIndex==0){
			return node->childNodePointerArray[0];
		}
		else{
			printf("error!!the pointer array has some questions!\n");
			return node->childNodePointerArray[0];
		}
	}
	int flag=0;
	while(node->keyValueArray[flag]<keyValue){
		if(flag>node->keyValueCurrentIndex){
			printf("error!! flag is larger than key value current index!\n");
			break;
		}
		flag++;
	}
	return node->childNodePointerArray[flag];
}
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
void pointerInsert(BTreeNode *fatherNode,int insertPostion,
		BTreeNode *pointer){
	int endFlag=fatherNode->pointerCurrentIndex;
	//remembet the insertPostion is count from 0,not from 1
	if(insertPostion>endFlag+1){
		printf("error\n the insertPostion is larger than the endFlag+1\n");
		return;
	}
	if(insertPostion<0){
		insertPostion=0;
	}
	endFlag++;
	(fatherNode->pointerCurrentIndex)++;
	BTreeNode **pointerArray=fatherNode->childNodePointerArray;
	pointerArray[endFlag]=pointer;
	if(insertPostion>=endFlag){
		return;
	}
	while(endFlag!=insertPostion){
		pointerXorSwap(&pointerArray[endFlag],&pointerArray[endFlag-1]);
		endFlag--;
	}
}
void specifiedKeyValueInsert(BTreeNode *fatherNode,int insertPostion,
		KeyType keyValue){
	if(fatherNode->keyValueCurrentIndex==2*DEGREE-2){
		printf("error!!!\nthe node is full we can not insert more!\n");
		return;
	}
	//remembet the insertPostion is count from 0,not from 1
	int endFlag=fatherNode->keyValueCurrentIndex;
	if(insertPostion>endFlag){
		printf("error\n the insertPostion is larger than the endFlag\n");
		return;
	}
	if(insertPostion<0){
		insertPostion=0;
	}
	endFlag++;
	fatherNode->keyValueCurrentIndex++;
	KeyType *keyValueArray=fatherNode->keyValueArray;
	keyValueArray[endFlag]=keyValue;
	while(endFlag!=insertPostion){
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
void showTheKeyValueArray(BTreeNode *node){
	int i=0;
	for(i;i<=node->keyValueCurrentIndex;i++){
		printf("%d ",node->keyValueArray[i]);
	}
	printf("\n");
}
void showThePointerArray(BTreeNode *node){
	int i=0;
	for(i;i<=node->pointerCurrentIndex;i++){
		printf("%p ",node->childNodePointerArray);
	}
	printf("\n");
}
void showTheTreeByLevel(BTreeNode *rootNode){
	int levelCount=1;
	int nodeCount=1;
	BTreeNode *node=rootNode;
	BTreeNode *tempNode;
	printf("the unleaf key value\n");
	while(node->nodeType==UNLEAF){
		tempNode=node->childNodePointerArray[0];
		nodeCount=1;
		while(node!=NULL){
			printf("the %d node of level %d\n",nodeCount,levelCount);
			showTheKeyValueArray(node);
			node=node->rightBrotherNode;
			nodeCount++;
		}
		node=tempNode;
		levelCount++;
	}
	printf("the leaf key value\n");
	nodeCount=1;
	while(node!=NULL){
		printf("the %d node \n",nodeCount);
		showTheKeyValueArray(node);
		node=node->rightBrotherNode;
		nodeCount++;
	}
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
			if(node->pointerCurrentIndex==(2*DEGREE-1)){
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
int main(void){
	BTreeCreate();
//	printf("%p\n",globalRootNode);
	BTreeInsert(globalRootNode,5);
	BTreeInsert(globalRootNode,3);
	BTreeInsert(globalRootNode,4);
	BTreeInsert(globalRootNode,6);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	BTreeInsert(globalRootNode,1);
	showTheTreeByLevel(globalRootNode);
	showThePointerArray(globalRootNode);
	showThePointerArray(globalRootNode->childNodePointerArray[0]);
	showThePointerArray(globalRootNode->childNodePointerArray[1]);
	/*
	printf("%p\n",globalRootNode);
	showThePointerArray(globalRootNode);
	showTheKeyValueArray(globalRootNode);
	showTheKeyValueArray(globalRootNode->childNodePointerArray[0]);
	showTheKeyValueArray(globalRootNode->childNodePointerArray[1]);
	*/
	return 1;
}
