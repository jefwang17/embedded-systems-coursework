#include <stdio.h>

int main(){

    char ch;

    while (1)
    {
        printf("Enter a character (# to exit): ");
        scanf(" %c", &ch);

        if (ch == '#') {
            break;
        }
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        {
           printf("%c is a vowel \n", ch);
        }   
        else if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            printf("%c is a consonant \n", ch);
        }
        else {
            printf(" Invalid input.\n");
        
    }
    
}
    return 0;
}