#include <stdio.h>

int main() {
    unsigned int num;
    int count = 0;

    printf("Please enter a 32 bit hexadecimal number: ");
    scanf("%x", &num);

    for (int i = 31; i >= 0; i--) {
        unsigned int mask = 1U << i;
        if ((num & mask) == 0) {
            count++;
        } else {
            break;
        }
    }

    printf("Number of leading zeros are %d\n", count);
    return 0;
}