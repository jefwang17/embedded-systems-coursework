#include <stdio.h>

int main() {
    int n, count = 0, largest_stable_count = 0;
    float num, smallest = 0, second_smallest = 0, third_smallest = 0, largest = 0;

    printf("Enter the number of iterations(n), should be greater than or equal to 3: ");
    scanf("%d", &n);

    // Ensure n is at least 3
    while (n < 3) {
        printf("Invalid input. Enter a number greater than or equal to 3: ");
        scanf("%d", &n);
    }

    // Initialize the first number
    printf("Enter a decimal number: ");
    scanf("%f", &num);
    smallest = second_smallest = third_smallest = largest = num;
    count++;
    printf("Count: %d - Smallest: %.2f - Second Smallest: %.2f - Third Smallest: %.2f - Largest: %.2f\n",
           count, smallest, second_smallest, third_smallest, largest);

    // Loop to process subsequent numbers
    while (1) {
        printf("Enter a decimal number: ");
        scanf("%f", &num);
        count++;

        // Update smallest, second_smallest, and third_smallest
        if (num < smallest) {
            third_smallest = second_smallest;
            second_smallest = smallest;
            smallest = num;
        } else if (num < second_smallest) {
            third_smallest = second_smallest;
            second_smallest = num;
        } else if (num < third_smallest) {
            third_smallest = num;
        }

        // Update largest and track stability
        if (num > largest) {
            largest = num;
            largest_stable_count = 0;  // Reset stability count
        } else if (num == largest) {
            largest_stable_count++;    // Increment stability count
        }

        // Print current state
        printf("Count: %d - Smallest: %.2f - Second Smallest: %.2f - Third Smallest: %.2f - Largest: %.2f\n",
               count, smallest, second_smallest, third_smallest, largest);

        // Break if the largest value remains unchanged for n iterations
        if (largest_stable_count >= n) {
            printf("Program stopped because the largest value (%.2f) did not change for %d iterations.\n", largest, n);
            break;
        }
    }

    return 0;
}