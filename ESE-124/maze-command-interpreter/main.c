#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "functions.h"
#include "stack.h"

#define MAX 8
#define SIZE 100

char maze[MAX][MAX];

void print_maze(void) {
    printf("\nMaze:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    FILE *inp = fopen("input.txt", "r");
    FILE *outp = fopen("output.txt", "w");
    FILE *intl = fopen("Intelligence.txt", "r");
    if (!inp || !outp || !intl) {
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }

    int x = -1, y = -1;
    char ch;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            ch = fgetc(inp);
            while (ch == '\n') ch = fgetc(inp);
            if (ch == '*') { x = i; y = j; }
            maze[i][j] = ch;
        }
    }
    position current = { x, y };
    print_maze();

    char cmd[SIZE];
    char cmds_buf[SIZE][20];
    int n, t;
    int max_Steps = 0;

    while (fscanf(intl, "%s", cmd) == 1 && strcmp(cmd, "END") != 0) {
        fprintf(outp, "%s\n", cmd);
        if (strcmp(cmd, "MARK") == 0) {
            MARK(current);
            max_Steps++;
        } else if (strcmp(cmd, "MOVE_F") == 0) {
            MOVE_F(&current);
            max_Steps++;
        } else if (strcmp(cmd, "MOVE_B") == 0) {
            MOVE_B(&current);
            max_Steps++;
        } else if (strcmp(cmd, "MOVE_L") == 0) {
            MOVE_L(&current);
            max_Steps++;
        } else if (strcmp(cmd, "MOVE_R") == 0) {
            MOVE_R(&current);
            max_Steps++;
        } else if (strcmp(cmd, "CWL") == 0) {
            CWL(&current);
            max_Steps++;
        } else if (strcmp(cmd, "CWR") == 0) {
            CWR(&current);
            max_Steps++;
        } else if (strcmp(cmd, "CWF") == 0) {
            CWF(&current);
            max_Steps++;
        } else if (strcmp(cmd, "CWB") == 0) {
            CWB(&current);
            max_Steps++;
        } else if (strcmp(cmd, "PUSH") == 0) {
            PUSH(current);
            max_Steps++;
        } else if (strcmp(cmd, "POP") == 0) {
            POP();
            max_Steps++;
        } else if (strcmp(cmd, "PEEK") == 0) {
            position topPos = PEEK();
            (void)topPos;
            max_Steps++;
        } else if (strcmp(cmd, "CLEAR") == 0) {
            CLEAR();
            max_Steps++;
        } else if (strcmp(cmd, "BJPI") == 0) {
            BJPI(itch_direction, itch_steps, &current);
            max_Steps++;
        } else if (strcmp(cmd, "CJPI") == 0) {
            CJPI(itch_direction, &current);
            max_Steps++;
        } else if (strcmp(cmd, "BACKTRACK") == 0) {
            BACKTRACK(&current);
            max_Steps++;
        } else if (strncmp(cmd, "RP_", 3) == 0 && sscanf(cmd, "RP_%d_%d", &n, &t) == 2) {
            for (int i = 0; i < n; i++) {
                fscanf(intl, "%s", cmds_buf[i]);
            }
            RP_n_t(n, t, cmds_buf, &current);
            max_Steps++;
        } else {
            printf("Unknown command: %s\n", cmd);
        }

        printf("\nSteps so far: %d\n", max_Steps);
        print_maze();
    }

    fclose(inp);
    fclose(outp);
    fclose(intl);
    return 0;
}
