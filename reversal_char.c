#include<stdio.h>
#include<malloc.h>
void reversal_string(char *source_string,int string_length){
	char *begin=source_string;
	char *end=source_string+(string_length-2);
	char temp_ch;
	while(end>begin){
		temp_ch=*begin;
		*begin++=*end;
		*end--=temp_ch;
	}
}
int main(){
	char *test2="test";
	char test[5]="test";
	char *end=&test[1]+1;
	char *test3=&test2[1]+1;
//	reversal_string(test,sizeof(test));
//	printf("%d\n%d\n%d\n%d\n",test,test[0],&test,&test[0]);
	printf("%s",test3);
	return 1;
}
