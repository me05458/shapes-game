#ifndef HELPER_H
#define HELPER_H
#define FALSE 0
#define TRUE 1
//reset the character input area
//I finally figured out how it works!!
void cleanChar();
void clearScreen();
void init();
void changeColorRGB(int xpos, int ypos, int r, int g, int b);
void changeColor(int xpos, int ypos, int color);
#endif
