#include <stdio.h>
typedef enum {S0, S1, S2, S3, S4, S5, S6, S7} STATES;
STATES NextState [][5] = {
                        S1, S0, S0, S0, S0,
                        S1, S2, S0, S0, S0,
                        S1, S0, S3, S0, S0,
                        S4, S0, S0, S0, S0,
                        S1, S5, S0, S0, S0,
                        S1, S0, S6, S0, S0,
                        S4, S0, S0, S7, S0,
                        S1, S0, S0, S0, S0};				  
int OutputTable [][5] = {
                        0,0,0,0,0,
                        0,0,0,0,0,
                        0,0,0,0,0,
                        0,0,0,0,0,
                        0,0,0,0,0,
                        0,0,0,0,0,
                        0,0,0,1,0,
                        0,0,0,0,0,
};
int main () {
    STATES current_state = S0;
    char input[100];
    int col, output;
    int count = 0;
    printf("Enter input string (M/U/R/S/...): ");
    fgets(input, sizeof(input), stdin);
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
        char ch = input[i];
        switch (ch) {
            case 'M': col = 0; break;
            case 'U': col = 1; break;
            case 'R': col = 2; break;
            case 'S': col = 3; break;
            default:  col = 4; break;
        }
        output = OutputTable[current_state][col];
        current_state = NextState[current_state][col];
        if (output == 1) {
            count++;
        }
        printf("Read '%c' -> State: %d, Output: %d\n", ch, current_state, output);
    }
    printf("\n\"MURMURS\" detected %d time(s).\n", count);
    return 0;
}