#include <stdio.h>
#include <math.h>

int main(){

    float x, a, t, sum = 0.0;
    int i = 0;

    printf("Please enter a value for x:");
    scanf("%f", &x);
    printf("Please enter a precision value for a:");
    scanf("%f", &a);

    if (fabs(x) >= 1) 
    {
        printf("error x should be between (-1,1).\n");
        return 1;
    }

    t = 1.0;
    
    while (fabs(t) >= a) 
    {
        sum += t;
        i++;
        t = pow(x, i);
        printf("Taylor Series 1 / (1 - x) %dth Order Sum = %f.\n", i, sum);
    }

    printf("Final result: %f", sum);
    
    return 0;

}