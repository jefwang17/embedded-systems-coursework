#include <stdio.h>

int main() {
    unsigned char value;
    unsigned int tmp;
    int p;

    printf("Enter a hexadecimal number: ");
    scanf("%x", &tmp);
    value = tmp & 0xFF;

    do {
        printf("Enter a value for P: ");
        scanf("%d", &p);
    } while (p < 0 || p > 8);

    value &= ~(0xFF << (8 - p));
    value |= (1 << (8 - p)) - 1;

    printf("%x\n", value);
    return 0;
}