#include<stdio.h>
typedef int ULONGLONG;
//we count the number of 1 at each level from signle,ten,hundred,thousand
//的确就是数学啊！总结出关键点就可以了。
int countOneNumber(ULONGLONG number){
	int oneCount=0;
	ULONGLONG factor=1;
	ULONGLONG higherNumber=0;
	ULONGLONG currentNumber=0;
	ULONGLONG lowerNumber=0;
	while(number/factor!=0){
		lowerNumber=number-(number/factor)*factor;
		currentNumber=(number%(factor*10)-lowerNumber)/factor;
		higherNumber=number/(factor*10);
		printf("%d+%d+%d\n",higherNumber,currentNumber,lowerNumber);
		switch(currentNumber){
			case 0:
				oneCount=oneCount+higherNumber*factor;
				break;
			case 1:
				oneCount=oneCount+higherNumber*factor+lowerNumber+1;
				break;
			default:
				oneCount=oneCount+(higherNumber+1)*factor;
				break;
		}
		factor=factor*10;
	}
	return oneCount;
}
int main(void){
	ULONGLONG test=123;
	//对于运行错误，这里不显示？？我等下试一下内存方面的错误，指针光声明，不分配
	int result=5;
	result=countOneNumber(test);
	printf("%d",result);
	return 0;
}
