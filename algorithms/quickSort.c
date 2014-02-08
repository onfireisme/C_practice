#include</home/wangyan/C_practice/algorithms/quickSort.h>
/*
 * In this file.I write three algorithms
 * First,quick sort.Second middleValueQuickSort
 * The last one ,median of medians quick select
 */
/*
 * some defination of this function, in case that I forget it
 * the beginFlag equal to the first element of array,at first,equal to 0
 * end equal to the last element of the array,at first ,equal to ARRAYLENGTH-1
 */
void quickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray){
	int smallerNumberCountFlag=beginFlag-1;
	int countFlag=beginFlag;
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
//this function is based on the quickSort,but have different with it
NodeType pivotPartition(NodeType *sortArray,NodeType pivot,int beginFlag,int endFlag){
	int countFlag=beginFlag;
	int smallerNumberCountFlag=beginFlag-1;
	while(countFlag<=endFlag){
		if(sortArray[countFlag]>pivot){
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
}
/*
 * The beginFlag,endFlag attribute are both very important,as the begin and the end of the array
 * always change,so we have to add it
 */
int medianOfMedianQuickSelect(NodeType *sortArray,int beginFlag,int endFlag,int KthNumber){
	//first step,get the columns of array, 5 elements a row
	arrayLength=endFlag-beginFlag+1;
	int columns=getDivideUpperBound(arrayLength,DIVIDEDNUMBER);
	NodeType medians[columns-1];
	int i=0;
	//second,get all the medians
	for(i;i<columns;i++){
		medians[i]=medianOfFive(sortArray,beginFlag+i*5,arrayLength);
	}
	//then,its the most interesting part of this algorithm,we use
	//the recursion to get the median of the array medians[]
	int medianOfMediansPosition=medianOfMedianQuickSelect(medians,0,columns-1,
			getDivideUpperBound(columns,2));
	pivotPartition(sortArray,medians[medianOfMediansPosition],beginFlag,endFlag);
}
/*
 * depend on the taocp, 5.3.3 it tells us 
 * it only takes 6 comparations,but it will need at most 7 swap operations,but the operation still
 * only consume linear time
 * holy shit!! I forget about the special situation!!yeah,I have to say,its not a good choice to 
 * use this method
 */
NodeType medianOfFive(NodeType *sortArray,int beginFlag,int arrayLength){
	if(beginFlag+5>arrayLength){
		return sortArray[beginFlag];
	}
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
//we must give the address of the variable,or we cann't swap them 
//even if they belong to the array,it will be fine,because of the defination of the array
//you just need to send the address of the value which belong to this array is ok.
void xorSwap(NodeType *numOne,NodeType *numTwo){
	*numOne=*numOne^*numTwo;
	*numTwo=*numOne^*numTwo;
	*numOne=*numOne^*numTwo;
}
//length is the length of the array
void showTheArray(NodeType *sortArray,int length){
	int i=0;
	for(i;i<length;i++){
		printf("%d ",sortArray[i]);
	}
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
	globalSortArray=(NodeType *)malloc(sizeof(NodeType)*ARRAYLENGTH);
	generateRandomArray(globalSortArray);
//	showTheArray(globalSortArray,ARRAYLENGTH);
	printf("\n");
//	printf("%d",medianOfFive(globalSortArray,0));
	medianOfMedianQuickSelect(globalSortArray,10);
	free(globalSortArray);
	return 1;
}
