#include <stdio.h>

int main(){

    int n, p_num, c_p = 0, c_n = 0, c_z = 0;


    printf("Enter a number: ");
    scanf("%d", &p_num);

    if (p_num > 0) {
    c_p++;
    } 
    else if (p_num < 0) {
    c_n++;
    } 
    else {
    c_z++;
    }

    while (1) {
        printf("Enter a number: ");
        scanf("%d", &n);

        if (n == p_num) {
            break;
        }
        if (n > 0) {
            c_p++;
        } else if (n < 0) {
            c_n++;
        } else {
            c_z++;
        }

        p_num = n;


        printf("Number of positive numbers: %d\n", c_p);
        printf("Number of negative numbers: %d\n", c_n);
        printf("Number of zeroes: %d\n", c_z);
    }
        return 0;
}