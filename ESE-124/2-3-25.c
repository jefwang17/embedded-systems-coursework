#include <stdio.h>

int main (){
	
	
	
	float val1, val2, result;
	char oper; // variable for the operation
	int counter;
	
	for(counter = 1; counter <= 5; counter++){
		printf("value 1:");
		scanf ("%f", &val1);
	
		printf("value 2:");
		scanf ("%f", &val2);
		getchar();
	
		printf ("operation (+ - * /)");
		scanf ("%c", &oper);
	
		switch (oper) {
			case '+': result = val1 + val2; break;
			case '-': result = val1 - val2; break;
			case '*': result = val1 * val2; break;
			case '/': result = val1 / val2; break;
			default: printf ("%c is incorrect\n", oper);
		
		}
		printf ("result %0.10f\n", result);
	}
}
