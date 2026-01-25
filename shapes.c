#include <stdio.h>
#include "settings.h"
#include "shapes.h"
extern int colors[COLNUM+1][3];
void setColRGB(int r, int g, int b) //your friendly formatting function
{
    printf("\033[30m");
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

void renderShape(int type, int color, int head)
{
    if(color<0 || color >COLNUM)
    {
        color = 0;
    }
    renderShapeRGB(type,colors[color][0],colors[color][1],colors[color][2],head);
}

void renderShapeRGB(int type, int r, int g, int b, int head)
{
    printf("\033[30m");
    setColRGB(r,g,b);
    switch (type) {
        case -1:
            if(head == 0)
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
            if(head == 0)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setCol(-2);
            break;
        case 1:
            switch(head){
                case 0:
                    printf(" *       ");
                    break;
                case 1:
                    printf("    *    ");
                    break;
                case 2:
                    printf("    *    ");
                    break;
                default:
                    printf("         ");
            }
            setCol(-2);
            break;
                case 2:
                    for(int i = 0; i<3; i++)
                    {
                        setColRGB(r,g,b);
                        if(i == head)
                        {
                            printf(" * ");
                        }
                        else
                        {
                            printf("   ");
                        }
                        setCol(-2);
                    }
                    break;
                default:
                    printf("SOMETHING WENT WRONG OH NO");
    }
}
