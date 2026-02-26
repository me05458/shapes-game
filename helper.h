#ifndef HELPER_H
#define HELPER_H
#include <stdbool.h>
#include "vars.h"
#include "helper_big.h"

//it turns out everything is in here :P

//how field works:
//filed[xcoord][ycoord][stuff]
//stuff -> 0th, 1st, 2nd = rgb, 3rd = head, 4th = full

int init(); //start library and reset field
//set an element of the field to a color:
void changeColorRGB(int xpos, int ypos, int r, int g, int b);
void changeColor(int xpos, int ypos, int color);
int blockToField(int x, int y, int block, int col); //puts a block in the field
//checks full/empty field respectively:
bool isFull();
bool isEmpty();
int canPlace(int shape); //shape can be placed? (aka good empty space?)
void renderBoard(); //draw (includes current shape)
void clearFull(); //clear rows/cols that are full
void renderBoardHead(); //render board, but with different star settings
void uninit(); //destructor; cleans memory
#endif


//for ref
/*printf("\e[?25lcat:");
char tmp = getchar();
printf("\e[?25hcaaat:");
tmp = getchar();
return 0;
*/
