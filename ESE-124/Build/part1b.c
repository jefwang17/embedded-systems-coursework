#include <stdio.h>
#include <limits.h>
int main(){

    int n, i;
    int t = 9, s = 0, p_sum = 0;


    printf("Please enter a value for n: ");
    scanf("%d", &n);

    int l_n;
    for (i = 1; i <= n; i++) 
    {
    printf("%d", t);
        if (i < n) printf(" + ");
       
    s += t;
        if (s < p_sum) {  
    printf("\nOverflow occurred before reaching %d terms.\n", n);
    break;   
    }
    p_sum = s;
    t = t * 10 + 9;
    l_n = i;
    }
    if (l_n == n) {
        printf("\nWhen we reach %d terms, Sum = %d.\n", n, s);
    }
    printf("Largest term that can be calculated without error is: %d\n", l_n);

    return 0;
}
