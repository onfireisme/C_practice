#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define ARRAYLENGTH 54
#define RANDOMMAX 100
#define random(x)(rand()%x)
#define DIVIDEDNUMBER 5
/* this function,recursion is much better
 */
/*
 * now, after consideration,I think I make a huge mistake that I shoudn't
 * to add all local virable with local 
 * I just need to add Global with the global varible,that's all
 */
typedef int NodeType;
NodeType *globalSortArray;
void quickSort(NodeType *sortArray);
void quickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray);
void middleValueQuickSortRecursion(int beginFlag,int endFlag,NodeType *sortArray);
void middleValueQuickSort(NodeType *sortArray);
void showTheArray(NodeType *sortArray,int length);
void xorSwap(NodeType *numOne,NodeType *numTwo);
NodeType medianOfFive(NodeType *sortArray,int beginFlag);
int medianOfMedianQuickSelect(NodeType *sortArray,int KthNumber);
int getDivideUpperBound(int divideNumber,int dividedNumber);
