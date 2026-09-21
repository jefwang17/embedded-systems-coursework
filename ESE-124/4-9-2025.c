#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 32


int is_palindrome (char s[])
{
	int i;
	
	for(i = 0; i < strlen(s) - 1 - i; i++)
	{
		if(s[i] != s[strlen(s) - 1 - i])
		{
			return 0;
		}
		return 1;
	}
}

int main()
{
	char str[LEN];
	
	while(1)
	{
		printf ("string: ");
		scanf ("%s", str); getchar();
		if(is_palindrome(str))
		{
			printf("%s is a palindrome\n", str);
		}
		else
		{
			printf("%s is not a palindrome\n", str);
		}
	}
}

