/* functions.h */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAZE_SIZE 8      // renamed

extern int itch_direction;
extern int itch_steps;

typedef struct { int row, col; } position;
// Cell processing
void check(position *pos, int c, int r);

// Actions
void MARK(position current);
position MOVE_F(position *pos);
position MOVE_B(position *pos);
position MOVE_L(position *pos);
position MOVE_R(position *pos);

// Itch detection
int CWL(position *pos);
int CWR(position *pos);
int CWF(position *pos);
int CWB(position *pos);

// Jumps
void BJPI(int direction, int steps, position *pos);
void CJPI(int direction, position *pos);

// Memory & backtracking
void BACKTRACK(position *curr);

// Repeat block
void RP_n_t(int n, int t, char command[][20], position *pos);

#endif  // FUNCTIONS_H
