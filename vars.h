#ifndef VARS_H
#define VARS_H
#include "settings.h"
//global vars :3
extern int field[SIZE][SIZE][5]; //field
extern int blocks[BLOCKNUM];
extern int colors[COLNUM+1][3];
extern int lastPlacedx;
extern int lastPlacedy;
extern int c_block;
extern int c_col;
extern bool started;
extern int lineCount;
#endif
