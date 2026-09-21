#include <stdio.h>
typedef enum {S0, S1, S2, S3, S4, S5} STATES;
STATES NextState [][2] = {
                    S1, S2,
                    S1, S4,
                    S5, S3,
                    S5, S3,
                    S5, S3,
                    S1, S4};				  
int OutputTable [][2] = {
                        0,0,
                        0,0,
                        0,0,
                        1,1,
                        0,1,
                        0,1,};
int main () {
    STATES current_state = S0;
    int number, parity, output;

    printf("Enter integers (even/odd detected using %% 2). Ctrl+D to stop:\n");

    while (scanf("%d", &number) == 1) {
        parity = number % 2; // 0 = even, 1 = odd
        output = OutputTable[current_state][parity];
        current_state = NextState[current_state][parity];

        printf("Input: %d (parity %d) -> State: S%d -> Output: %d\n",
               number, parity, current_state, output);
    }

    return 0;
}