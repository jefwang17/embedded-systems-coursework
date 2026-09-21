/* stack.c */
#include <stdio.h>
#include "stack.h"

static position stack_arr[MAX_STACK];
static int      top = -1;

int is_empty(void) {
    return top < 0;
}

int is_full(void) {
    return top >= MAX_STACK - 1;
}

void PUSH(position pos) {
    if (is_full()) {
        printf("Stack is full — can't push (%d, %d)\n", pos.row, pos.col);
        return;
    }
    stack_arr[++top] = pos;
    printf("He memorizes (%d, %d)\n", pos.row, pos.col);
}

position POP(void) {
    if (is_empty()) {
        printf("Stack is empty. Cannot pop.\n");
        return (position){-1, -1};
    }
    position popped = stack_arr[top--];
    printf("Michael recalls (%d, %d)\n", popped.row, popped.col);
    return popped;
}

position PEEK(void) {
    if (is_empty()) {
        printf("Stack is empty. Cannot peek.\n");
        return (position){-1, -1};
    }
    position topPos = stack_arr[top];
    printf("Michael peeks (%d, %d)\n", topPos.row, topPos.col);
    return topPos;
}

void CLEAR(void) {
    top = -1;
    printf("Stack cleared\n");
}
