#include <stdio.h>
#include "settings.h"
#include "shapes.h"
#include <stdbool.h>

extern int colors[COLNUM+1][3];
void setColRGB(int r, int g, int b) //your friendly formatting function
{
    printf("\033[38;2;%d;%d;%dm",TEXTCOL);
    if(r == -2)
    {
        printf("\033[0m\n");
        return;
    }
    if(r == -1)
    {
        printf("\033[0m");
        return;
    }
    printf("\033[48;2;%d;%d;%dm",r,g,b);
}

void setCol(int color)
{
    if(color<0)
    {
        setColRGB(color,-3,-3);
        return;
    }
    if(color >COLNUM)
    {
        color = 0;
    }
    setColRGB(colors[color][0],colors[color][1],colors[color][2]);
}

void renderShape(int type, int color, bool head)
{
    if(color<0 || color >COLNUM)
    {
        color = 0;
    }
    renderShapeRGB(type,colors[color][0],colors[color][1],colors[color][2],head);
}

void renderShapeRGB(int type, int r, int g, int b, bool head)
{ //SHAPES
    setColRGB(r,g,b);
    switch (type) {
        case -1:
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setCol(-1);
            break;
        case 0:
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setCol(-2);
            break;
        case 2:
            if(head)
            {
                printf("   ");
                setColRGB(r-SMALLOFF, g-SMALLOFF, b-SMALLOFF);
                printf(" * ");
                setColRGB(r,g,b);
                printf("   ");
            }
            else
            {
                printf("   ");
                setColRGB(r-SMALLOFF, g-SMALLOFF, b-SMALLOFF);
                printf("   ");
                setColRGB(r,g,b);
                printf("   ");
            }
            setCol(-2);
            break;
        case 3:
            setColRGB(r,g,b);
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("  ");
            }
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-2);
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2);
            break;
        case 4:
            setColRGB(r,g,b);
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-2);
            break;
        case 5:
            setColRGB(r,g,b);
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setCol(-2);
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-2);
            break;
        case 1:
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2);
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setCol(-2);
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2);
                    break;
                default:
                    printf("SOMETHING WENT WRONG OH NO");
    }
}
