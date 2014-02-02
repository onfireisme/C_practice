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
void quickSort(int beginFlag,int endFlag,NodeType *sortArray){
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
		quickSort(beginFlag,smallerNumberCountFlag-1,sortArray);
	}
	if(smallerNumberCountFlag+1<endFlag){
		quickSort(smallerNumberCountFlag+1,endFlag,sortArray);
	}
}
void middleValueQuickSort(int beginFlag,int endFlag,NodeType *sortArray){
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
		quickSort(beginFlag,smallerNumberCountFlag-1,sortArray);
	}
	if(smallerNumberCountFlag+1<endFlag){
		quickSort(smallerNumberCountFlag+1,endFlag,sortArray);
	}
}
/*
 * I don't know,if I should add the arrayLength attribute,it needs consideration
 */
NodeType medianOfMedianQuickSelect(NodeType *sortArray,int selectPosition,int arrayLength){
	//first step,get the columns of array, 5 elements a row
	int columns=arrayLength/5;
}
void mallocMedianArray(NodeType *medians,int columns){
	medians=(NodeType *)malloc(sizeof(NodeType)*columns);
}
/*
 * depend on the taocp, 5.3.3 it tells us 
 * it only takes 6 comparations,but it will need at most 7 swap operations
 */
NodeType medianOfFive(NodeType *sortArray,int beginFlag){
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
void showTheArray(NodeType *sortArray,int length){
	int i=0;
	for(i;i<=length;i++){
		printf("%d\n",sortArray[i]);
	}
}
int main(void){
	int test=11;
	printf("%d\n",test/5);
	/*
	globalSortArray=(NodeType *)malloc(sizeof(NodeType)*ARRAYLENGTH);
	globalSortArray[0]=2;
	globalSortArray[1]=3;
	globalSortArray[2]=7;
	globalSortArray[3]=6;
	globalSortArray[4]=8;
	test(&globalSortArray[0]);
//	printf("%d",medianOfFive(globalSortArray,0));
//	showTheArray(globalSortArray,4);
	free(globalSortArray);
	*/
	return 1;
}
