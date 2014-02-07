#include</home/wangyan/C_practice/algorithms/quickSort.h>
/*
 * mostly ,we choose the last element as the first element to decide its
 * position
 * however,when the elements are ordered,then the time consuming will be n square
 * can we find a better way to solve this problem?
 *
 * first solution: we choose a random element and change it with the last element
 *
 * second solution: we choose the middle value of three elements
 * they are the beginning one ,last one,and the middle one
 * for example, we have a sequence, 1,4,3,5,8
 * 1 is the beginning one ,2 is the last one, 0+4/2=2 which is 8,8 is the middle one
 * we choose the middle value ,the 8 is the first element that we choose to decide position
 * we replace it with the last one,then the seqence is 1,4,8,5,3
 * By prove,it reduce about 5% time consuming
 *
 * last solution:we call it the median of median selection algorithm which is based on the 
 * quickselect algorithm.what's more ,it has linear time complexity for select the kth
 * largest element.
 * remember it ,in this algorithm, our purpose is to select kth largest number
 */
//of course ,the endFlag equal to ARRAYLENGTH-1
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
//for this method,we get a pivot,but we don't now ,its position..
//So, we have to add something to make sure the partition is fine
NodeType pivotPartition(NodeType *sortArray,NodeType pivot){
	int countFlag=0;
	int smallerNumberCountFlag=-1;
	while(countFlag<ARRAYLENGTH){
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

}
/*
 * it seems that I have to add the arrayLength attribute to this function
 */
NodeType medianOfMedianQuickSelect(NodeType *sortArray,int KthNumber){
	//first step,get the columns of array, 5 elements a row
	int columns=getDivideUpperBound(ARRAYLENGTH,DIVIDEDNUMBER);
	printf("%d",columns);
	NodeType medians[columns-1];
	int i=0;
	//second,get all the medians
	for(i;i<columns;i++){
		medians[i]=medianOfFive(sortArray,i*5);
	}
	//then,its the most interesting part of this algorithm,we use
	//the recursion to get the median of the array medians[]
	int medianOfMedians=medianOfMedianQuickSelect(medians,getDivideUpperBound(columns,2);
}
/*
 * depend on the taocp, 5.3.3 it tells us 
 * it only takes 6 comparations,but it will need at most 7 swap operations,but the operation still
 * only consume linear time
 * holy shit!! I forget about the special situation!!yeah,I have to say,its not a good choice to 
 * use this method
 */
NodeType medianOfFive(NodeType *sortArray,int beginFlag){
	if(beginFlag+4>ARRAYLENGTH-1){
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
