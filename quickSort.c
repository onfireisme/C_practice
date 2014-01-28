#include</home/wangyan/C_practice/quickSort.h>
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
 */
void quickSort(int beginFlag,int endFlag,NodeType *sortArray){
	int smallerNumberCountFlag=beginFlag-1;
	int countFlag=beginFlag;
	while(countFlag<=endFlag){
		if(sortArray[countFlag]>sortArray[endFlag]){
			countFlag++;
		}
		else{
//			printf("%d\n",sortArray[countFlag]);
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
//	printf("%d\n",countFlag);
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
//			printf("%d\n",sortArray[countFlag]);
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
	globalSortArray=(NodeType *)malloc(sizeof(NodeType)*ARRAYLENGTH);
	globalSortArray[0]=4;
	globalSortArray[1]=3;
	globalSortArray[2]=7;
	globalSortArray[3]=6;
	globalSortArray[4]=1;
	xorSwap(&globalSortArray[0],&globalSortArray[1]);
//	globalSortArray[5]=9;
//	globalSortArray[6]=10;
//	globalSortArray[7]=11;
//	int testArray[3]={3,1,2};
//	printf("%d",testArray);
	middleValueQuickSort(0,4,globalSortArray);
	showTheArray(globalSortArray,4);
	free(globalSortArray);
	return 1;
}
