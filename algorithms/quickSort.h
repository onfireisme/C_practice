#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define ARRAYLENGTH 100
#define RANDOMMAX 100
#define random(x)(rand()%x)
#define DIVIDEDNUMBER 5
#define MIDDLE 2
#define SMALL 0
#define BIG 1
#define LOOPCOUNTMAX 200
#define K 40
typedef int NodeType;
typedef int BOOL;
NodeType *globalSortArray;

/*
 * quickSort
 */

void quickSort(NodeType *sortArray);
void quickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray);

/* 
 * middleValueQuickSort
 */

void middleValueQuickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray);
void middleValueQuickSort(NodeType *sortArray);

/*
 * quickSelect
 */

NodeType quickSelectSmallestNumberRecursion(NodeType *sortArray,int beginFlag,
		int endFlag,int KthSmallestNumber);
/*
 * medians of medians sort algorithm
 */

int pivotPartition(NodeType *sortArray,NodeType pivot,int beginFlag,int endFlag);
int medianOfMediansQuickSelectRecursion(NodeType *sortArray,int beginFlag,int endFlag,int KthNumber);
NodeType medianOfFive(NodeType *sortArray,int beginFlag,int endFlag);
NodeType medianOfMediansQuickSelect(NodeType *sortArray,int KthNumber);

/* 
 *other functions
 */

void showTheArray(NodeType *sortArray,int length);
void showTheArrayWithEnd(NodeType *sortArray,int beginFlag,int endFlag);
void xorSwap(NodeType *numOne,NodeType *numTwo);
int getDivideUpperBound(int divideNumber,int dividedNumber);
