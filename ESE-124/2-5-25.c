#include <stdio.h>

int main(){
	unsigned int a;
	
	a = 0x0000000
	
	printf ("number of bytes: %d\n", sizeof (char));
	
	a = 0xAA;
	
	printf ("A = 0x%\n", a); //10101010
	
	printf ("value: ");
	scanf("%x" , &a);
	printf("A = 0x%x\n", a); //
	
	return 0;
	
}
