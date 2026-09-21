#include <stdio.h>

int main(){

    int n,i,j,r =0;

    printf("Input number of terms :");
    scanf("%d", &n);

    if (n<= 5)
    {
        for ( i = 1; i <= n; i++)
    {
        j = i * 2;
        printf("%d ", j); 
        r += j;
    }
    printf("\nThe sum of even natural numbers up to 5 terms: %d\n", r);
} else {
    printf("Input exceeds the limit of 5 terms.\n");
}

return 0;
}