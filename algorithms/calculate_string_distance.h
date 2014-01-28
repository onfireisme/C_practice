#include<stdio.h>
#include<malloc.h>
#define false 0
#define true 1
#define STRING_ONE_BEGIN 0
#define STRING_TWO_BEGIN 0 
int calculate_string_distance_recursion(char *string_one,char *string_two,
		int string_one_position,int string_two_position,
		int string_one_length,int string_two_length);
int calculate_string_distance(char *string_one,char *string_two,
		int string_one_length,int string_two_length);
