#include "vars.h"
int field[SIZE][SIZE][5]; //field
//int blocks[BLOCKNUM] = BLOCKS; //array of blocks
int *blocks;
int BLOCKNUM = 0;
//int colors[COLNUM+1][3] = COLORS; //array of colors
int *colors;
int COLNUM = 0;
int lastPlacedx = -1; //last coordinates (for * rendering)
int lastPlacedy = -1;
int c_block; //current block (currently dealing with it)
int c_col; //current color
bool started = true; //just started
int lineCount = 0; //lines filled?
int RELOAD = 0;
int CLEAR = 1;
int SUBDIV = 3;
int NORM_COORD =1;
int DOUBLEINT =1;
int WAITTIME =500;
int ANIMATE= 0;
int USE_SYS= 1;
int SMALLOFF= 20;
int BIGOFF =50;
int BASECOL =225;
int RMOD =10;
int GMOD= 0;
int BMOD= 0;
int MODBLOCK= false;
int MODCOL = true;
int VERBOSE = false;
int TEXTCOLR = 255;
int TEXTCOLG = 255;
int TEXTCOLB = 255;
