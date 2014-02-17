#include</home/wangyan/C_practice/algorithms/quickSort.h>
/*
 * In this file.I write three algorithms
 * First,quick sort.Second middleValueQuickSort
 * The last one ,median of medians quick select
 */
/*
 * Definition
 * 1 beginFlag
 * equal to the first element of the array,at the beginning,it always equal to 0
 * 2 endFlag
 * endFlag equal to the last element of the array.
 * at the beginning, it always equal to ARRAYLENGTH-1 
 * 3 KthSmallestNumber
 * if it euqal to 10,then it means that 9 numbers are smaller than it.
 * 4 smallerNumberCountFlag
 * it means that the numbers that smaller than the pivot
 */
void quickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray){
	int smallerNumberCountFlag=beginFlag;
	//when the smallerNumberCountFlag is 10,it means that we do have
	//10 numbers smaller it
	int countFlag=beginFlag;
	while(countFlag<endFlag){
		if(sortArray[countFlag]<sortArray[endFlag]){
			xorSwap(&sortArray[smallerNumberCountFlag],
					&sortArray[countFlag]);
			smallerNumberCountFlag++;
			countFlag++;
		}
		else{
			countFlag++;
		}
	}
	//in fact,I really don't want to add this line,however,if I consider the 
	//special situation that have too values are equal 
	xorSwap(&sortArray[smallerNumberCountFlag],&sortArray[endFlag]);

	if(beginFlag<smallerNumberCountFlag-1){
		quickSortRecursion(beginFlag,smallerNumberCountFlag-1,sortArray);
	}
	if(smallerNumberCountFlag+1<endFlag){
		quickSortRecursion(smallerNumberCountFlag+1,endFlag,sortArray);
	}
}
void quickSort(NodeType *sortArray){
	quickSortRecursion(0,ARRAYLENGTH-1,sortArray);
}
void middleValueQuickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray){
	int middlePosition=(beginFlag+endFlag)/2;
	int smallerNumberCountFlag=beginFlag-1;
	int countFlag=beginFlag;
	// firstly ,we need to find a better pivot,this time we choose the middle
	// value as the pivot
	//it's ok,even they have some values are equal to each other
	if((beginFlag-endFlag)*(beginFlag-middlePosition)<=0){
		xorSwap(&sortArray[beginFlag],&sortArray[endFlag]);
	}
	else{
		if((middlePosition-endFlag)*(middlePosition-beginFlag)<=0){
			xorSwap(&sortArray[middlePosition],&sortArray[endFlag]);
		}
	}
	while(countFlag<=endFlag){
		if(sortArray[countFlag]>sortArray[endFlag]){
			countFlag++;
		}
		else{
			smallerNumberCountFlag++;
			if(smallerNumberCountFlag!=countFlag){
				xorSwap(&sortArray[smallerNumberCountFlag],
						&sortArray[countFlag]);
			}
			countFlag++;
		}
	}
	if(beginFlag<smallerNumberCountFlag-1){
		middleValueQuickSortRecursion(beginFlag,smallerNumberCountFlag-1,sortArray);
	}
	if(smallerNumberCountFlag+1<endFlag){
		middleValueQuickSortRecursion(smallerNumberCountFlag+1,endFlag,sortArray);
	}
}
void middleValueQuickSort(NodeType *sortArray){
	middleValueQuickSortRecursion(0,ARRAYLENGTH-1,sortArray);
}
NodeType quickSelectSmallestNumberRecursion(NodeType *sortArray,int beginFlag,
		int endFlag,int KthSmallestNumber){
	/*
	 *那就是，值重复的问题。pivot的位置是由smallerNumber决定的
	 *这样就导致，你只能求比它小的数，有多少，但小的数里面，是否有重复，你就无法决定了
	 *况且，这样还是有问题
	 */
	//the special condition that when
	if(KthSmallestNumber>endFlag-beginFlag+1){
		printf("the array length is not enough long");
		return 0;
	}
	int countFlag=beginFlag;
	int smallerNumberCountFlag=beginFlag;
	while(countFlag<endFlag){
		if(sortArray[countFlag]<=sortArray[endFlag]){
			xorSwap(&sortArray[smallerNumberCountFlag],&sortArray[countFlag]);
			smallerNumberCountFlag++;
			countFlag++;
		}
		else{
			countFlag++;
		}
	}
	int smallerNumber=smallerNumberCountFlag-beginFlag;
	xorSwap(&sortArray[smallerNumberCountFlag],&sortArray[endFlag]);
	if(smallerNumber+1==KthSmallestNumber){
		return sortArray[smallerNumberCountFlag];
	}
	if(smallerNumber>=KthSmallestNumber){
		printf("one");
		showTheArray(sortArray,ARRAYLENGTH);
		printf("smallerNumber is %d beginFlag is %d endFlag is %d KthSmallestNumber is %d\n",
				smallerNumber,beginFlag,endFlag,KthSmallestNumber);
		printf("\n");
		if(beginFlag>smallerNumberCountFlag){
			printf("wrong");
			return 0;
		}
		return quickSelectSmallestNumberRecursion(sortArray,beginFlag,smallerNumberCountFlag-1,
				KthSmallestNumber);
	}
	else{
		printf("two");
		showTheArray(sortArray,ARRAYLENGTH);
		printf("smallerNumber is %d beginFlag is %d endFlag is %d KthSmallestNumber is %d\n",
				smallerNumber,beginFlag,endFlag,KthSmallestNumber);
		printf("\n");
		if(smallerNumberCountFlag>endFlag){
			printf("wrong");
			return 0;
		}
		return quickSelectSmallestNumberRecursion(sortArray,smallerNumberCountFlag,endFlag,
				KthSmallestNumber-smallerNumber);
	}
}
int pivotPartition(NodeType *sortArray,NodeType pivot,int beginFlag,int endFlag){
	if(beginFlag==endFlag){
		return 0;
	}
	int countFlag=beginFlag;
	int smallerNumberCountFlag=beginFlag;
	//BOOL pivotDetect=FALSE;
	while(countFlag<=endFlag){
		if(sortArray[countFlag]<pivot){
			xorSwap(&sortArray[smallerNumberCountFlag],&sortArray[countFlag]);
			smallerNumberCountFlag++;
			countFlag++;
		}
		/*
		else if(sortArray[countFlag]==pivot){
			pivotDetect=TRUE;
			if(countFlag!=endFlag){
				xorSwap(sortArray[countFlag],sortArray[endFlag]);
			}
			else{
				countFlag++;
			}
		}
		*/
		else{
			countFlag++;
		}
	}
	/*
	if(pivotDetect!=TRUE){
		printf("could not find the pivot");
		return 0;
	}
	*/
	int smallerNumber=smallerNumberCountFlag-beginFlag;
	return smallerNumber;
}
NodeType medianOfMediansQuickSelectRecursion(NodeType *sortArray,int beginFlag,int endFlag,
		int KthNumber){
	if(beginFlag==endFlag){
		return sortArray[endFlag];
	}
	if(beginFlag>endFlag){
		printf("wrong");
		return 0;
	}
	//first step,get the columns of array, 5 elements a row
	int arrayLength=endFlag-beginFlag+1;
	int columns=getDivideUpperBound(arrayLength,DIVIDEDNUMBER);
	NodeType medians[columns-1];
	int i=0;
	//second,get all the medians
	for(i;i<columns;i++){
		medians[i]=medianOfFive(sortArray,beginFlag+i*5,arrayLength);
	}
	printf("columns is %d\n",columns);
	showTheArray(medians,columns);
	showTheArray(medians,columns);
	//the recursion..If I use the recursion here ,then I need to set a stop condition
	//at the begin of the function,or,the recursion will never stop
	NodeType medianOfMedians;
	if(columns>1){
		medianOfMedians=medianOfMediansQuickSelectRecursion(medians,0,columns-1,
				getDivideUpperBound(columns,2));
	}
	else{
		medianOfMedians=medians[0];
	}
	int smallerNumber=pivotPartition(sortArray,medianOfMedians,beginFlag,endFlag);
	printf("beginFlag is%d endFlag is%d smaller number is %d  KthNumber is%d medianOfMedians is %d\n",
			beginFlag,endFlag,smallerNumber,KthNumber,medianOfMedians);
	if(smallerNumber+1==KthNumber){
		return medianOfMedians;
	}
	if(smallerNumber>=KthNumber){
		return medianOfMediansQuickSelectRecursion(sortArray,beginFlag,
				smallerNumber+beginFlag-1,KthNumber);
	}
	else{
		return medianOfMediansQuickSelectRecursion(sortArray,smallerNumber+beginFlag,
				endFlag,KthNumber-smallerNumber);
	}
}
NodeType medianOfMediansQuickSelect(NodeType *sortArray,int KthNumber){
	medianOfMediansQuickSelectRecursion(sortArray,0,ARRAYLENGTH-1,KthNumber);
}
NodeType medianOfFive(NodeType *sortArray,int beginFlag,int arrayLength){
	if(beginFlag+5>arrayLength){
		quickSortRecursion(beginFlag,arrayLength-1,sortArray);
		int median=getDivideUpperBound(arrayLength-beginFlag,MIDDLE);
		return sortArray[median+beginFlag-1];
	}
	//below is the normal situation
	if(sortArray[beginFlag]<sortArray[beginFlag+1]){
		xorSwap(&sortArray[beginFlag],&sortArray[beginFlag+1]);
	}
	if(sortArray[beginFlag+2]<sortArray[beginFlag+3]){
		xorSwap(&sortArray[beginFlag+2],&sortArray[beginFlag+3]);
	}
	if(sortArray[beginFlag]<sortArray[beginFlag+2]){
		xorSwap(&sortArray[beginFlag],&sortArray[beginFlag+2]);
		xorSwap(&sortArray[beginFlag+1],&sortArray[beginFlag+3]);
	}
	if(sortArray[beginFlag+1]<sortArray[beginFlag+4]){
		xorSwap(&sortArray[beginFlag+1],&sortArray[beginFlag+4]);
	}
	if(sortArray[beginFlag+1]<sortArray[beginFlag+2]){
		xorSwap(&sortArray[beginFlag+1],&sortArray[beginFlag+2]);
		xorSwap(&sortArray[beginFlag+3],&sortArray[beginFlag+4]);
	}
	if(sortArray[beginFlag+2]<sortArray[beginFlag+4]){
		return sortArray[beginFlag+4];
	}
	else{
		return sortArray[beginFlag+2];
	}
}
void xorSwap(NodeType *numOne,NodeType *numTwo){
	if(numOne==numTwo){
		return;
	}
	*numOne=(*numOne)^(*numTwo);
	*numTwo=(*numOne)^(*numTwo);
	*numOne=(*numOne)^(*numTwo);
}
//length is the length of the array
void showTheArray(NodeType *sortArray,int length){
	int i=0;
	for(i;i<length;i++){
		printf("%d ",sortArray[i]);
	}
	printf("\n");
}
void showTheArrayWithEnd(NodeType *sortArray,int beginFlag,int endFlag){
	int i=beginFlag;
	for(i;i<=endFlag;i++){
		printf("%d",sortArray[i]);
	}
	printf("\n");
}
void generateRandomArray(NodeType *sortArray){
	int i=0;
	for(i;i<ARRAYLENGTH;i++){
		sortArray[i]=random(RANDOMMAX);
	}
}
//keep this function to remind that the usage of the malloc
void mallocMedianArray(NodeType *medians,int columns){
	medians=(NodeType *)malloc(sizeof(NodeType)*columns);
}
int getDivideUpperBound(int divideNumber,int dividedNumber){
	int result;
	if(divideNumber%dividedNumber==0){
		result=divideNumber/dividedNumber;
	}
	else{
		result=divideNumber/dividedNumber+1;
	}
	return result;
}
int main(void){
	if(ARRAYLENGTH>0){
		globalSortArray=(NodeType *)malloc(sizeof(NodeType)*ARRAYLENGTH);
	}
	else{
		printf("error,the arraylength should larger than 1");
	}
	generateRandomArray(globalSortArray);
	showTheArray(globalSortArray,ARRAYLENGTH);
	printf("\n");
//	printf("%d",pivotPartition(globalSortArray,3,0,3));
//	printf("%d\n",medianOfMediansQuickSelectRecursion(globalSortArray,0,ARRAYLENGTH-1,7));
	printf("%d\n",quickSelectSmallestNumberRecursion(globalSortArray,0,ARRAYLENGTH-1,4));
	free(globalSortArray);
	return 1;
}
