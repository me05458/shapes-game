#ifndef HELPER_H
#define HELPER_H
#define FALSE 0
#define TRUE 1
#include <stdbool.h>

//it turns out everything is in here :P

//how field works:
//filed[xcoord][ycoord][stuff]
//stuff -> 0th, 1st, 2nd = rgb, 3rd = head, 4th = full

//reset the character input area
//I finally figured out how it works!!
void cleanChar();
void clearScreen();
int init();
void changeColorRGB(int xpos, int ypos, int r, int g, int b);
void changeColor(int xpos, int ypos, int color);
int charEater(char c);
int blockToField(int x, int y, int block, int col);
bool isFull();
bool isEmpty();
int canPlace(int shape);
void renderBoard();
void waitMS(int ms);
void clearFull();
void renderBoardHead();
#endif
