#include <stdio.h>

int main(){

    printf ("number of bytes: %d\n", sizeof (unsigned char));
    printf ("number of bytes: %d\n", sizeof (unsigned short));
    printf ("number of bytes: %d\n", sizeof (unsigned int));
    printf ("number of bytes: %d\n", sizeof (unsigned long));

    unsigned char A =0x12, B = 0xda, C = 0x3b, D = 0xbe;

    printf("A: Hex = %x, Dec = %d, Char = %c\n", A, A, A);
    printf("B: Hex = %x, Dec = %d, Char = %c\n", B, B, B);
    printf("C: Hex = %x, Dec = %d, Char = %c\n", C, C, C);
    printf("D: Hex = %x, Dec = %d, Char = %c\n", D, D, D);

    printf("A & B: %x\n", A & B);
    printf("A | B: %x\n", A | B);
    printf("A ^ B: %x\n", A ^ B);
    printf("C & D: %x\n", C & D);
    printf("C | D: %x\n", C | D);
    printf("C ^ D: %x\n", C ^ D);

    unsigned int user_input;
    printf("Enter a hexadecimal number: ");
    scanf("%x", &user_input);
    user_input |= 0xF;
    printf("Result: 0x%X\n", user_input);

    return 0;

}