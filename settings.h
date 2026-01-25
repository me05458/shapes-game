//ignore this
#ifndef SETTINGS_H
#define SETTINGS_H

//will there be clear()? 1 recommended for regular gameplay.
#define USE_SYS 0

//there are 10 colors.
#define ONE 247, 187, 129
#define TWO 247, 246, 129
#define THREE 202, 247, 129
#define FOUR 138, 247, 129
#define FIVE 129, 247, 176
#define SIX 129, 189, 247
#define SEVEN 131, 129, 247
#define EIGHT 202, 129, 247
#define NINE 247, 129, 234
#define TEN {247, 129, 129}
#define BACKUP 100,100,100
#define COLNUM 10
#define COLORS {{BACKUP},{ONE},{TWO},{THREE},{FOUR},{FIVE},{SIX},{SEVEN},{EIGHT},{NINE},{TEN}}



//there are 3 different blocks.
#define BLOCKS {0,1,2}
#define BLOCKNUM 3 //these HAVE to match!!!
/*
0: square
XX

1: line
XXXXXX

2: line
XX
XX
XX

3: square
XXXX
XXXX
 */

//ignore this
#endif
