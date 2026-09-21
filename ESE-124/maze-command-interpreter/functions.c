#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "stack.h"

#define MAX 8
#define MAX_SIZE 100
#define MAX_NUMBER_OF_STEPS 500

// Maze grid to mark progress
char maze[MAX][MAX];
int itch_direction = -1; // Direction for BJPI and CJPI
int itch_steps = 0;

// Stack structure for Michael's memory
position stack[MAX_SIZE];
int stack_top = -1;
position current = {0, 0}; // Starting position

// Function to load maze from file
void load_maze(FILE *file) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            fscanf(file, " %c", &maze[i][j]);
        }
    }
}

// Print the maze to the console
void print_maze() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

// Movement functions
void MOVE_F(position *pos) {
    int new_row = pos->row + 1;
    if (new_row < MAX && maze[new_row][pos->col] != 'X') {
        pos->row = new_row;
    }
}

void MOVE_B(position *pos) {
    int new_row = pos->row - 1;
    if (new_row >= 0 && maze[new_row][pos->col] != 'X') {
        pos->row = new_row;
    }
}

void MOVE_L(position *pos) {
    int new_col = pos->col - 1;
    if (new_col >= 0 && maze[pos->row][new_col] != 'X') {
        pos->col = new_col;
    }
}

void MOVE_R(position *pos) {
    int new_col = pos->col + 1;
    if (new_col < MAX && maze[pos->row][new_col] != 'X') {
        pos->col = new_col;
    }
}

// MARK current position
void MARK(position pos) {
    maze[pos.row][pos.col] = 'P';
}

// Stack functions
void PUSH(position pos) {
    if (stack_top < MAX_SIZE - 1) {
        stack[++stack_top] = pos;
    } else {
        printf("Stack overflow!\n");
    }
}

position POP() {
    if (stack_top >= 0) {
        return stack[stack_top--];
    } else {
        printf("Stack underflow!\n");
        return (position){-1, -1};
    }
}

position PEEK() {
    if (stack_top >= 0) {
        return stack[stack_top];
    } else {
        printf("Stack is empty!\n");
        return (position){-1, -1};
    }
}

void CLEAR() {
    stack_top = -1;
}

// Itch detection functions
void CWL(position *pos) {
    itch_direction = 2; // Left
    itch_steps = 0;
    for (int j = pos->col - 1; j >= 0; j--) {
        if (maze[pos->row][j] == 'X' || maze[pos->row][j] == 'P') break;
        itch_steps++;
    }
}

void CWR(position *pos) {
    itch_direction = 3; // Right
    itch_steps = 0;
    for (int j = pos->col + 1; j < MAX; j++) {
        if (maze[pos->row][j] == 'X' || maze[pos->row][j] == 'P') break;
        itch_steps++;
    }
}

void CWF(position *pos) {
    itch_direction = 0; // Forward
    itch_steps = 0;
    for (int i = pos->row + 1; i < MAX; i++) {
        if (maze[i][pos->col] == 'X' || maze[i][pos->col] == 'P') break;
        itch_steps++;
    }
}

void CWB(position *pos) {
    itch_direction = 1; // Backward
    itch_steps = 0;
    for (int i = pos->row - 1; i >= 0; i--) {
        if (maze[i][pos->col] == 'X' || maze[i][pos->col] == 'P') break;
        itch_steps++;
    }
}

// RP n t implementation
void RP(int n, int t, char actions[][32]) {
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(actions[j], "MOVE_F") == 0) MOVE_F(&current);
            else if (strcmp(actions[j], "MOVE_B") == 0) MOVE_B(&current);
            else if (strcmp(actions[j], "MOVE_L") == 0) MOVE_L(&current);
            else if (strcmp(actions[j], "MOVE_R") == 0) MOVE_R(&current);
            else if (strcmp(actions[j], "MARK") == 0) MARK(current);
            else if (strcmp(actions[j], "PUSH") == 0) PUSH(current);
            else if (strcmp(actions[j], "POP") == 0) current = POP();
            else if (strcmp(actions[j], "PEEK") == 0) current = PEEK();
            else if (strcmp(actions[j], "CLEAR") == 0) CLEAR();
            else if (strcmp(actions[j], "BJPI") == 0) BJPI(&current);
            else if (strcmp(actions[j], "CJPI") == 0) CJPI(&current);
            else if (strcmp(actions[j], "BACKTRACK") == 0) BACKTRACK(&current);
            else if (strcmp(actions[j], "CWL") == 0) CWL(&current);
            else if (strcmp(actions[j], "CWR") == 0) CWR(&current);
            else if (strcmp(actions[j], "CWF") == 0) CWF(&current);
            else if (strcmp(actions[j], "CWB") == 0) CWB(&current);
        }
    }
}
