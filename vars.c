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
int RELOAD = 0;
int CLEAR = 1;
int SUBDIV = 3;
int NORM_COORD =1;
int DOUBLEINT =1;
int WAITTIME =500;
int ANIMATE= 0;
int USE_SYS= 0;
int SMALLOFF= 20;
int BIGOFF =50;
int BASECOL =225;
int RMOD =10;
int GMOD= 0;
int BMOD= 0;
int MODBLOCK= false;
int VERBOSE = false;
int TEXTCOLR = 225;
int TEXTCOLG = 225;
int TEXTCOLB = 225;
