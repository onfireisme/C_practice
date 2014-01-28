#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define ARRAYLENGTH 1000
/* this function,recursion is much better
 */
/*
 * now, after consideration,I think I make a huge mistake that I shoudn't
 * to add all local virable with local 
 * I just need to add Global with the global varible,that's all
 */
typedef int NodeType;
NodeType *globalSortArray;
void quickSort(int beginFlag,int endFlag,NodeType *sortArray);
void showTheArray(NodeType *sortArray,int length);
void xorSwap(NodeType *numOne,NodeType *numTwo);
void middleValueQuickSort(int beginFlag,int endFlag,NodeType *sortArray);
