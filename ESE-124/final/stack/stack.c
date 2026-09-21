#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
// Stack implementation
char stack[MAX];
int top = -1;
void push(char c) {
if (top < MAX - 1)
    stack[++top] = c;
}
char pop() {
if (top >= 0)
    return stack[top--];
return '\0'; // return null character if empty
}
int isMatchingPair(char open, char close) {
return (open == '(' && close == ')') ||
       (open == '{' && close == '}') ||
       (open == '[' && close == ']');
}
int isBalanced(char *str) {
for (int i = 0; str[i]; i++) {
    char c = str[i];
    if (c == '(' || c == '{' || c == '[') {
        push(c);
    } else if (c == ')' || c == '}' || c == ']') {
        char open = pop();
        if (!isMatchingPair(open, c)) {
            return 0; // unbalanced
        }
    }
}
return top == -1; // stack must be empty if balanced
}
int main() {
FILE *file = fopen("input.txt", "r");
if (!file) {
    printf("Cannot open file.\n");
    return 1;
}
char line[MAX];
while (fgets(line, MAX, file)) {
    top = -1; // reset stack
    if (isBalanced(line))
        printf("balanced\n");
    else
        printf("unbalanced\n");
}
fclose(file);
return 0;
}
