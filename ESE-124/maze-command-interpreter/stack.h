/* stack.h */
#ifndef STACK_H
#define STACK_H

#include "functions.h"

#define MAX_STACK 100

int  is_empty(void);
int  is_full(void);
void PUSH(position pos);
position POP(void);
position PEEK(void);
void CLEAR(void);

#endif  // STACK_H
