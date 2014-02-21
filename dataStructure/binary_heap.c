#include</home/wangyan/C_practice/dataStructure/binary_heap.h>
void initialHeap(Heap *localHeap){
	localHeap->nodeArray=(NodeType *)malloc(sizeof(NodeType)*HEAPLENGTH);
	localHeap->lastNodePosition=0;
}
void pushNode(Heap *localHeap,NodeType nodeValue){
	localHeap->nodeArray[++localHeap->lastNodePosition]=nodeValue;
}
void buildMaxHeap(Heap *localHeap,int nodePosition){
	if(nodePosition>localHeap->lastNodePosition){
		printf("error! the position is over the last position of the heap");
		return;
	}
	while(nodePosition/2!=0&&
			localHeap->nodeArray[nodePosition/2]<localHeap->nodeArray[nodePosition]){
		NodeType tempNode=localHeap->nodeArray[nodePosition];
		localHeap->nodeArray[nodePosition]=localHeap->nodeArray[nodePosition/2];
		localHeap->nodeArray[nodePosition/2]=tempNode;
		nodePosition=nodePosition/2;
	}
}
//use this fucntion, we can remove the smallest or largest node to the top
void heapSort(Heap *localHeap){
	int nodeLength=localHeap->lastNodePosition;
	while(nodeLength>1){
		buildMaxHeap(localHeap,nodeLength);
//		printf("%d",nodeLength);
		nodeLength--;
	}
}
//we replace the top node to the last every time ,so we can get a sorted heap
void getSortedHeap(Heap *localHeap){
	int nodeLength=localHeap->lastNodePosition;
	NodeType tempNode;
	while(localHeap->lastNodePosition>1){
		heapSort(localHeap);
		tempNode=localHeap->nodeArray[1];	
		localHeap->nodeArray[1]=localHeap->nodeArray[localHeap->lastNodePosition];
		localHeap->nodeArray[localHeap->lastNodePosition]=tempNode;
		--localHeap->lastNodePosition;
	}
	localHeap->lastNodePosition=nodeLength;
}
void showHeap(Heap *localHeap){
	int nodeLength=localHeap->lastNodePosition;
	int i=1;
	for(i;i<=nodeLength;i++){
		printf("%d\n",localHeap->nodeArray[i]);
	}
}
void freeHeap(Heap *localHeap){
	free(localHeap->nodeArray);
}
int main(void){
	Heap heap;
	initialHeap(&heap);
	int temp=10;
	pushNode(&heap,temp);
	pushNode(&heap,++temp);
	pushNode(&heap,7);
	pushNode(&heap,++temp);
	pushNode(&heap,++temp);
	getSortedHeap(&heap);
	showHeap(&heap);
	freeHeap(&heap);
	return 1;
}
