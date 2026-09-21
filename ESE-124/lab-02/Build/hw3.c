#include <stdio.h>
   
   int main() {
        unsigned int num;
        int ones = 0;
    
        printf("Enter a 32 bit Hexadecimal value: ");
        scanf("%x", &num);
    
        for (int i = 0; i < 32; i++) {
            if (num & (1U << i)) ones++;
        }
    
        printf("Number of ones: %d\nNumber of zeroes: %d\n", ones, 32 - ones);
        return 0;
    }