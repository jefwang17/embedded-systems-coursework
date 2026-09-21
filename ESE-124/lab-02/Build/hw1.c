#include <stdio.h>

int main() {
    unsigned int num;
    printf("Enter a hexadecimal number: ");
    scanf("%x", &num);

    int num_bits = sizeof(num) * 8;
    unsigned int msb_mask = ~(3U << (num_bits - 2));
    num &= msb_mask;

    num |= 3;

    printf("Output: 0x%x\n", num);
    
    return 0;

}