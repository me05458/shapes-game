#include <stdbool.h>
#ifndef VARS_H
#define VARS_H
#define SIZE 9

//global vars :3
extern int field[SIZE][SIZE][5]; //field
extern int * blocks;
extern int BLOCKNUM;
extern int * colors;
extern int COLNUM;
extern int lastPlacedx;
extern int lastPlacedy;
extern int c_block;
extern int c_col;
extern bool started;
extern int lineCount;
extern int RELOAD;
extern int CLEAR;
extern int SUBDIV;
extern int NORM_COORD;
extern int DOUBLEINT;
extern int WAITTIME;
extern int ANIMATE;
extern int USE_SYS;
extern int SMALLOFF;
extern int BIGOFF;
extern int BASECOL;
extern int RMOD;
extern int GMOD;
extern int BMOD;
extern int MODCOL;
extern int MODBLOCK;
extern int VERBOSE;
extern int TEXTCOLR;
extern int TEXTCOLG;
extern int TEXTCOLB;
#endif
