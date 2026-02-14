#include "render.h"
#include <stdio.h>
void renderLine0(int type, int r, int g, int b)
{
    if(MODCOL)
    {
        r-=BIGOFF;
        g-=BIGOFF;
        b-=BIGOFF;
    }
    switch(type)
    {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
            setCol(-1);
            printf("         ");
            break;
        case 1:
        case 7:
            setCol(-1);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            printf("   ");
            break;
        case 6:
            setColRGB(r,g,b);
            printf("   ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            break;
        default:
            setCol(-1);
            printf("Incorrect shape type!\n");
            break;



    }
}
void renderLine1(int type, int r, int g, int b)
{
    if(MODCOL)
    {
        r-=BIGOFF;
        g-=BIGOFF;
        b-=BIGOFF;
    }
    switch(type)
    {
        case 0:
            setCol(-1);
            printf("   ");
            setColRGB(r,g,b);
            printf(" * ");
            setCol(-1);
            printf("   ");
            break;
        case 1:
            setCol(-1);
            printf("   ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf(" * ");
            setCol(-1);
            printf("   ");
            break;
        case 5:
            setColRGB(r,g,b);
            printf(" * ");
            setCol(-1);
            printf("   ");
            break;
        case 2:
        case 7:
            setColRGB(r,g,b);
            printf("   ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf(" * ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            break;
        case 3:
        case 4:
            setColRGB(r,g,b);
            printf(" * ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-1);
            break;
        case 6:
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf(" * ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-1);
            break;
        case 8:
            setColRGB(r,g,b);
            printf(" * ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            break;
        case 9:
            setColRGB(r,g,b);
            printf("   ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf(" * ");
            setCol(-1);
            break;
        default:
            setCol(-1);
            printf("Incorrect shape type!\n");
            break;
    }
}
void renderLine2(int type, int r, int g, int b)
{
    if(MODCOL)
    {
        r-=BIGOFF;
        g-=BIGOFF;
        b-=BIGOFF;
    }
    switch(type)
    {
        case 0:
        case 2:
        case 4:
            setCol(-1);
            printf("         ");
            break;
        case 1:
        case 7:
            setCol(-1);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            printf("   ");
            break;
        case 3:
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            break;
        case 6:
            setColRGB(r,g,b);
            printf("   ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            break;
        case 8:
        case 5:
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-1);
            printf("      ");
            break;
        case 9:
            setCol(-1);
            printf("      ");
            setColRGB(r-SMALLOFF,g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-1);
            break;
    }

}
void renderDot(int r, int g, int b, bool dot)
{
    setColRGB(r,g,b);
    if(dot)
    {
        printf(" * ");
    }
    else
        printf("   ");
    setCol(-1);
}
