#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Normally the algorithm of KMP 
// the first element T[0] and S[0]
// are the number in the array 
// Here I changed it to normal string

// this function is used to get the next array
void get_next(char *T, int *next)
{
	int i, j;
	i = 0;
	j = -1;
	next[0] = -1;
	printf("the lenght of string is %ld\n", strlen(T));
	while(i < strlen(T) ) //  T[0] is the lenght of string
	{
		
		if(j ==-1 || T[i] == T[j])
		{
			++i;
			++j;
			next[i] =j;
		}
		else
			j = next[j];
	}
}

// in this function string S is the main string 
// we hope to search it contains the string T
// the search start from pos
int Index_KMP(char *S, char *T, int pos)
{
	int i = pos; // i is the pointer that for main string S 
	int j = 0; // j is the pointer that for substring T
	int next[100];
	get_next(T, next);
	printf("the string is %s\n", S);
	int t_Len = strlen(T);
	int s_Len = strlen(S);
	while((i < s_Len) && (j < t_Len))
	{
		if(j==-1 || S[i]==T[j])
		{
			++i;
			++j;	
		}
		else
		{
			j = next[j];
		}
	}
	// if j exceed the length of the string
	if(j >= strlen(T) )
		return i- strlen(T);
	else 
		return 0;
}



void main()
{
	int i;
	char *underTest="abcabx";
	char *substring="abcbdabcabxxcs";
	int next[100];
	int position;
	get_next(underTest,next);
	for(i=0; i<strlen(underTest); i++)
		printf("the %dth number is %d\n",i,next[i]); 
	
	position = Index_KMP(substring,underTest,0);
	printf("the position is %d\n", position);
}