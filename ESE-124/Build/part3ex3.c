#include <stdio.h>

int main(){

    int n, r, rn=0;

    printf("Input a number:");
    scanf("%d", &n);

    while (n != 0)
    {
        r = n % 10;
        rn = rn * 10 + r;
        n /= 10;
    }
    
    printf("The number in reverse order is : %d", rn);

    return 0;
}