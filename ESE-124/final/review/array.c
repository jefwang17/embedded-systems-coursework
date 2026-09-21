#include <stdio.h>

void printSpiral(int* matrix, int rows, int cols) {
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int index = 0;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            printf("%d ", matrix[top * cols + i]);
        }
        top++;
        for (int i = top; i <= bottom; i++) {
            printf("%d ", matrix[i * cols + right]);
        }
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                printf("%d ", matrix[bottom * cols + i]);
            }
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                printf("%d ", matrix[i * cols + left]);
            }
            left++;
        }
    }
    printf("\n");
}
int main() {
    // Test case
    int matrix[5][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {1, 2, 3, 4}
    };
    int rows = 5, cols = 4;
    printSpiral((int*)matrix, rows, cols);
    return 0;
}