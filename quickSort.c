#include</home/wangyan/C_practice/quickSort.h>
//check the bug
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
			int tempNumber;
			if(smallerNumberCountFlag!=countFlag){
				tempNumber=sortArray[smallerNumberCountFlag];
				sortArray[smallerNumberCountFlag]=sortArray[countFlag];
				sortArray[countFlag]=tempNumber;
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
//	globalSortArray[5]=9;
//	globalSortArray[6]=10;
//	globalSortArray[7]=11;
//	int testArray[3]={3,1,2};
//	printf("%d",testArray);
	quickSort(0,4,globalSortArray);
//	showTheArray(globalSortArray,7);
	free(globalSortArray);
	return 1;
}
