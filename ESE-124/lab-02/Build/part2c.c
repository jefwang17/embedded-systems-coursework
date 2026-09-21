#include <stdio.h>

int main(){
    
    unsigned int a,b;
    unsigned char mask1 = 0xFF;
    unsigned char mask2 = 0xFF;

    int p,n;
    
    
    printf("Enter the first hexadecimal value : 0x");
    scanf("%x" , &a);

    printf("Enter the second hexadecimal value : 0x");
    scanf("%x" , &b);

    printf("Enter p and n (p,n):");
    scanf("%d %d" ,&p, &n);

    mask1 = mask1 << (8-n);
    mask1 = mask1 >>(7-p);
    mask1 = ~mask1;

    a= a & mask1;

    mask2 = mask2 >> (8-n);
    b = b & mask2;

    b = b << (p-n+1);
    a = a | b;


    printf("0x%02x\n", a);
    return 0;
}
