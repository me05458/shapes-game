//ignore this
#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdbool.h>

//basic stuff
#define RELOAD 0
#define CLEAR 1
#define SIZE 9
#define SUBDIV 3 //don't make it zero

//random advanced settings:
#define NORM_COORD 1
#define DOUBLEINT 1
#define WAITTIME 500

//will there be clear()? 1 recommended for regular gameplay.
#define USE_SYS 1

//color stuff
#define TEXTCOL 0,0,0

#define SMALLOFF 20
#define BIGOFF 50
#define BASECOL 100
//these are the dangerous ones to mess with:
#define RMOD 0
#define GMOD 0
#define BMOD 0
#define MODBLOCK false



//more color stuff
/*#define ONE 255, 74, 74
#define TWO 255, 140, 74
#define THREE 255, 246, 74
#define FOUR 177, 255, 74
#define FIVE 100, 255, 74
#define SIX 174, 255, 128
#define SEVEN 174, 255, 221
#define EIGHT 174, 172, 255
#define NINE 179, 74, 255
#define TEN 177, 74, 255
#define ELEVEN 155, 74, 238
#define TWELVE 155, 74, 140
#define BACKUP 100,100,100
#define COLNUM 12
#define COLORS {{BACKUP},{ONE},{TWO},{THREE},{FOUR},{FIVE},{SIX},{SEVEN},{EIGHT},{NINE},{TEN},{ELEVEN},{TWELVE}}*/
#define COLORS {{100,100,100},{100,255,174},{255,100,174},{255,174,100},{100,174,255},{174,100,255},{174,255,100}}
#define COLNUM 6 //does not include backup



//block stuff
#define BLOCKS {1,2,3,4,5,0,6}
#define BLOCKNUM 7 //these HAVE to match!!!
/*
0: square
X

2: line
XXX

1: line
x
x
x

3: square
xx
xx

4:
xx

5:
x
x

6:
xxx
xxx
xxx
*/

//ignore this
#endif
