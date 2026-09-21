#include <stdio.h>

int main() {
    unsigned char value;
    unsigned int tmp;
    int p, n;
    char op;

    printf("Enter a Hexadecimal input: ");
    scanf("%x", &tmp);
    value = tmp & 0xFF;

    do {
        printf("Enter p and n(p,n): ");
        scanf("%d,%d", &p, &n);
    } while (p >= 8 || n >= 8 || (p - n + 1) < 0);

    while (1) {
        printf("Please enter an operation 'S', 'R', 'F', 'D', 'I': ");
        scanf(" %c", &op);

        unsigned int mask;
        switch (op) {
            case 'S':
                mask = ((1 << n) - 1) << (p - n + 1);
                value |= mask;
                printf("Output: 0x%02x\n", value);
                break;
            case 'R':
                mask = ((1 << n) - 1) << (p - n + 1);
                value &= ~mask;
                printf("Output: 0x%02x\n", value);
                break;
            case 'F':
                mask = ((1 << n) - 1) << (p - n + 1);
                value ^= mask;
                printf("Output: 0x%02x\n", value);
                break;
            case 'D':
                printf("Value of the input is %d\n", value);
                break;
            case 'I':
                printf("Enter a Hexadecimal input: ");
                scanf("%x", &tmp);
                value = tmp & 0xFF;
                break;
            default:
                printf("Invalid operation\n");
        }
    }
    return 0;
}