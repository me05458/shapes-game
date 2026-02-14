#ifndef RENDER_H
#define RENDER_H
#include "shapes.h"

//all shapes are actually 3 x 3 blocks.
void renderLine0(int type, int r, int g, int b);
void renderLine1(int type, int r, int g, int b);
void renderLine2(int type, int r, int g, int b);
void renderDot(int r, int g, int b, bool dot);
#endif
