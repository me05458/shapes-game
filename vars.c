#include "settings.h"
int field[SIZE][SIZE][5]; //field
int blocks[BLOCKNUM] = BLOCKS; //array of blocks
int colors[COLNUM+1][3] = COLORS; //array of colors
int lastPlacedx = -1; //last coordinates (for * rendering)
int lastPlacedy = -1;
int c_block; //current block (currently dealing with it)
int c_col; //current color
bool started = true; //just started
int lineCount = 0; //lines filled?
