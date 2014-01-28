#include</home/onfire/C/string_rotate_check.h>
int is_include_rotate_string(char *compared_string,
		char *compare_string,int compared_string_length,int compare_string_length){
	int i=0;
	char *copied_string=double_copy_string(compared_string,compared_string_length);
	for(i;i<compared_string_length*2-compare_string_length+2;i++){
		int j=0;
		while(copied_string[i+j]==compare_string[j]){
			if(j==compare_string_length-1){
				return true;
			}
			j++;
		}
	}
	return false;
	free(copied_string);
	copied_string=NULL;
}
void test(char *temp){
	temp=temp+2;
	printf("%s",temp);
}
//remember to free the space
char * double_copy_string(char *source_string,int string_length){
	int i=0;
	char *new_string=(char *)malloc(string_length*2);
	for(i;i<string_length;i++){
		new_string[i]=source_string[i];
		new_string[string_length+i]=source_string[i];
	}
	return new_string;
}
int main(void){
	char *temp="test";
	char *temp2="ttest";
	char temp3[5]="test";
	test(temp3);
//	printf("%d",is_include_rotate_string(temp,temp2,4,2));
	return 0;
}
