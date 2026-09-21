#include <stdio.h>

int main(){
    unsigned char a;
    int p,n;

    
    printf("Enter a Hexadecimal value (0x00-0xff): 0x");
    scanf("%x" , &a);

    printf("Enter p and n (p,n):");
    scanf("%d %d" ,&p, &n);

   a = a << (7-p);
   a = a >>(8-n);

    printf("0x%02x\n", a);
    return 0;
}
