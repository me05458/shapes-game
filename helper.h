#ifndef HELPER_H
#define HELPER_H
//reset the character input area
//I finally figured out how it works!!
void cleanChar();
void clearScreen();
void init();
//global variables :3
int field[10][10]; //field
int blocks[BLOCKNUM] = BLOCKS;
#endif
