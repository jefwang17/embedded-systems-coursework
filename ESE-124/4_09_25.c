#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {S1, S2, S3, S4, S5, S6, S7} STATES;
STATES NextState [][4] = {
							S2, S1, S1, S1,
							S2, S3, S1, S1,
							S2, S1, S4, S1,
							S5, S1, S1, S1,
							S2, S6, S1, S1,
							S2, S1, S7, S1,
							S5, S1, S1, S1};

int OutputTable[][4] = {
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 0,
						};

int main()
{
	STATES current_state;
	char ch;
	int input;
	int col, output;
	
	
	current_state = S1;
	while(1)
	{
		printf("input: ");
		scanf("%c", &ch);
	
		switch(ch)
		{
			case 'm': col = 0; break;
			case 'u': col = 1; break;
			case 'r' : col = 2; break;
			default : col = 3; break;
		}
		
		output = OutputTable[current_state][col];
		current_state = NextState[current_state][col];
		
		printf("Current state: %d output: %d\n", current_state, output);
	}
}
