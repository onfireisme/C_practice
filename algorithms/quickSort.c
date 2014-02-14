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
	//the special condition that when
	if(KthSmallestNumber>endFlag-beginFlag+1){
		showTheArray(sortArray,ARRAYLENGTH);
		printf("beginFlag is%d endFlagis %d Kth is %d",beginFlag,endFlag,KthSmallestNumber); 
		printf("the array length is not enough long");
		return 0;
	}
	int countFlag=beginFlag;
	int smallerNumberCountFlag=beginFlag;
	while(countFlag<endFlag){
		if(sortArray[countFlag]<sortArray[endFlag]){
			xorSwap(&sortArray[smallerNumberCountFlag],&sortArray[countFlag]);
			smallerNumberCountFlag++;
			countFlag++;
		}
		else{
			countFlag++;
		}
	}
	/*
	 *NOTICE!!!
	 *because of recursion ,the smaller number will soon be different with 
	 *the smallerNumberCountFlag
	 */
	int smallerNumber=smallerNumberCountFlag-beginFlag;
	xorSwap(&sortArray[smallerNumberCountFlag],&sortArray[endFlag]);
	if(smallerNumber+1==KthSmallestNumber){
		return sortArray[smallerNumberCountFlag];
	}
	if(smallerNumber>=KthSmallestNumber){
		if(beginFlag>smallerNumberCountFlag){
			printf("wrong");
			return 0;
		}
		return quickSelectSmallestNumberRecursion(sortArray,beginFlag,smallerNumberCountFlag-1,
				KthSmallestNumber);
	}
	else{
		if(smallerNumberCountFlag>endFlag){
			printf("wrong");
			return 0;
		}
		return quickSelectSmallestNumberRecursion(sortArray,smallerNumberCountFlag,endFlag,
				KthSmallestNumber-smallerNumber);
	}
}
int pivotPartition(NodeType *sortArray,NodeType pivot,int beginFlag,int endFlag){
	int countFlag=beginFlag;
	int smallerNumberCountFlag=beginFlag-1;
	while(countFlag<=endFlag){
		if(sortArray[countFlag]>=pivot){
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
	//holy shit!I forget that I define the 0 euqal to 1,at this place
	return smallerNumberCountFlag+1;
}
//fuck!! I have make a stupid mistake,every recursion should have stop conditon,I cann't
//believe I just write a algorithm without stop condition!!
//
NodeType medianOfMediansQuickSelectRecursion(NodeType *sortArray,int beginFlag,int endFlag,
		int KthNumber){
	//why I add a situation that,when the length of the array is smaller than 5,
	//then I just use the sortselect ,return the value that we want,because,as you know,when the number is
	//smaller ,then quickselect is acceptable!
	if(endFlag==beginFlag){
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
	showTheArray(medians,columns);
	/*
	//then,its the most interesting part of this algorithm,we use
	//the recursion to get the median of the array medians[]
	NodeType medianOfMedians=medianOfMediansQuickSelectRecursion(medians,0,columns-1,
			getDivideUpperBound(columns,2));
	int smallerNumber=pivotPartition(sortArray,medianOfMedians,beginFlag,endFlag);
	printf("smaller number is %d",smallerNumber);
	printf("\n");
	if(smallerNumber==KthNumber){
		return medianOfMedians;
	}
	if(smallerNumber>KthNumber){
		return medianOfMediansQuickSelectRecursion(sortArray,beginFlag,smallerNumber-1,KthNumber);
	}
	else{
		return medianOfMediansQuickSelectRecursion(sortArray,smallerNumber-1,endFlag,
				KthNumber-smallerNumber);
	}
	*/
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
int printNum(int number){
	printf("%d ",number);
}
int main(void){
	if(ARRAYLENGTH!=0){
		globalSortArray=(NodeType *)malloc(sizeof(NodeType)*ARRAYLENGTH);
	}
	generateRandomArray(globalSortArray);
	showTheArray(globalSortArray,ARRAYLENGTH);
	printf("\n");
	printf("final result is %d\n",quickSelectSmallestNumberRecursion(globalSortArray,0,ARRAYLENGTH-1,6));
	showTheArray(globalSortArray,ARRAYLENGTH);
	free(globalSortArray);
	return 1;
}
