#include</home/onfire/C/calculate_string_distance.h>
int calculate_string_distance_recursion(char *string_one,char *string_two,
		int string_one_position,int string_two_position,
		int string_one_length,int string_two_length){
	if(string_one_position>string_one_length-1||string_two_position>string_two_length-1){
		return 0;
	}
	if(string_one[string_one_position]==string_two[string_two_position]){
		int distance_length=calculate_string_distance_recursion(string_one,string_two,string_one_position+1,
				string_two_position+1,string_one_length,string_two_length);
		return distance_length+1;
	}
	else{
		int distance_length=calculate_string_distance_recursion(string_one,string_two,string_one_position+1,
				string_two_position,string_one_length,string_two_length);
		int distance_length2=calculate_string_distance_recursion(string_one,string_two,string_one_position,
				string_two_position+1,string_one_length,string_two_length);
		if(distance_length>distance_length2){
			return distance_length;
		}
		else{
			return distance_length2;
		}
	}
}
int calculate_string_distance(char *string_one,char *string_two,
		int string_one_length,int string_two_length){
	int distance_length;
	distance_length=calculate_string_distance_recursion(string_one,string_two,
		STRING_ONE_BEGIN,STRING_TWO_BEGIN,string_one_length,
		string_two_length);
	return distance_length;
}
int main(void){
	char *temp1="testsf";
	char *temp2="stest";
	char temp3[6];
	printf("%d",sizeof(*temp2));
//	printf("%d",calculate_string_distance(temp1,temp2,sizeof(temp2),5));
	return 0;
}
