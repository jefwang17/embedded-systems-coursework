#include <stdio.h>

int main(){

    int i, r, j;

    printf("Input number of rows:");
    scanf("%d", &r);

    for (i = 0; i <= r ; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("%d", j);
        }
        printf("\n");
    }
    
    return 0;

}