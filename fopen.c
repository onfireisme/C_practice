#include<stdio.h>
#include<string.h>
#define LANDMARK_NUMBER 154
#define LANDMAKR_PATH "home/onfire/FaceTracer/Project/LandMarks.txt"
void save_landMark(float array[],FILE **fp){
	if ((*fp=fopen("test.txt","w"))==NULL) /*打开只写的文本文件*/
	{
		printf("cannot open file!");
	}
	int i=0;
	char temp[20];
	for(i;i<LANDMARK_NUMBER-1;i++){
		sprintf(temp,"%f",array[i]);
		fputs(temp,*fp); /*写入串*/
		fputs("  ",*fp); /*写入串*/
	}
	fputs("\n",*fp); /*写入回车符*/
}

int main(void){
	FILE *fp;
	float array[LANDMARK_NUMBER];
	int i=0;
	for(i=0;i<LANDMARK_NUMBER-1;i++){
		array[i]=i;	
	}
	int j=0;
	for(j=0;j<5;j++){
		save_landMark(array,fp);
	}
	fclose(fp); /*关文件*/
	return 0;
}
