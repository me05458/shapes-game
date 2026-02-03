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
#define ANIMATE 0

//will there be clear()? 1 recommended for regular gameplay.
#define USE_SYS 1

//color stuff
#define TEXTCOL 225,225,225

#define SMALLOFF 20
#define BIGOFF 50
#define BASECOL 225
//these are the dangerous ones to mess with:
#define RMOD 10
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
#define COLORS {{70,70,70},{140, 70, 137},{77, 140, 70},{70, 78, 140},{140, 70, 71}}
#define COLNUM 4 //does not include backup



//block stuff
#define BLOCKS {0,1,2,3,4,5,6,7}
#define BLOCKNUM 8 //these HAVE to match!!!
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

7:
 x
xxx
 x
*/

//ignore this
#endif
