#ifndef SHAPES_H
#define SHAPES_H
#include <stdbool.h>
#include "vars.h"
#include "render.h"

//draws a shape (includes newlines)
void renderShapeLineRGB(int type, int r, int g, int b, int line);
void renderShapeLine(int type, int color, int line);
void renderShapeRGB(int type, int r, int g, int b, bool head);
void renderShape(int type, int color, bool head);

//sets the color of the output.
void setCol(int color);
void setColRGB(int r, int g, int b);
#endif
