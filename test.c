#include<malloc.h>
#include<stdio.h>
typedef char MyType;
void test(int **temp){
}
int *test2(){
}
void test3(char **char1,int row,int column){
	*char1=*char1+2*row+column;
//	printf("%c",*char1);
//	printf("test");
}
void Remalloc(MyType **temp){
	*temp=(MyType *)realloc(*temp,2*sizeof(MyType));
}
int main(){
	MyType *test1=(MyType *)malloc(1*sizeof(MyType));
	test1[0]='a';
	Remalloc(&test1);
	char char1[6][5]={
		"test1",
		"test2",
		"test3",
		"test4",
		"test5"
	};
	return 1;
//	test3(&char1,6,5);
}
