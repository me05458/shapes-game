#include <stdio.h>
#include "shapes.h"
#include "render.h"
#include <stdbool.h>

void setColRGB(int r, int g, int b) //your friendly formatting function
{
    //this comes first: clear w/ newline or clear w/o
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
    //all of these are checks for incorrect r,g,b s
    if(r<0)
        r=0;
    if(r>255)
        r=255;
    if(g<0)
        g=0;
    if(g>255)
        g = 255;
    if(b<0)
        g=0;
    if(b>255)
        b=0;

    //just escape codes
    printf("\033[38;2;%d;%d;%dm",TEXTCOLR, TEXTCOLG, TEXTCOLB); //text see 38
    printf("\033[48;2;%d;%d;%dm",r,g,b); //background see 48
}

void setCol(int color) //just call that other color function
{
    if(color<0) //pass some dummy numbers for other parameters
    {
        setColRGB(color,-3,-3);
        return;
    }
    if(color >COLNUM) //color is not a valid one, use default
    {
        color = 0;
    }
    //pass that color's r,g,b along.
    setColRGB(colors[color*3],colors[color*3 + 1],colors[color*3 + 2]);
}

void renderShape(int type, int color, bool head) //calls other function
{
    if(color<0 || color >COLNUM) //invalid color, use default
    {
        color = 0;
    }
    //render shape with RGB
    renderShapeRGB(type,colors[color*3],colors[color*3 + 1],colors[color*3 + 2],head);
}
void renderShapeRGB(int type, int r, int g, int b, bool head)
{
    if(type == -1)
    {
        // printf("dot?");
        renderDot(r,g,b,false);
    }
    else if(type == -2)
    {
        renderDot(r,g,b,true);
    }
    else
    {
        for(int i = 0; i<3; i++)
        {
            renderShapeLineRGB(type, r,g,b,i);
            if(type != -1 && type != -2)
            {
                printf("\n");
            }
        }
    }
}
/*void renderShapeRGB(int type, int r, int g, int b, bool head) //this actually does shapes
//head -> render shape with *. This is a bunch of nonsense because of the bad rendering dynamics, I'm gonna refactor it one day.
{ //SHAPES
    if(type != -1 && MODCOL)
    {
        r -= BIGOFF;
        b -= BIGOFF;
        g -= BIGOFF;
    }
    setColRGB(r,g,b);
    switch (type) {
        case -1: //the dots in the field (no newline)
            if(head)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
            setCol(-1); //NO NEWLINE
            break;
        case 0: //regular dot
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
        case 2: //xxx
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
                // xx
                // xx
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
        case 4: //xx
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
        case 5: // x
                 // x
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
        case 6: //3x3 square
            printf("   ");
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2); //linebreak
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
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
            setCol(-2); //linebreak
            setColRGB(r,g,b);
            printf("   ");
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2);
            break;
        case 7: //cross
            setCol(-1);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            printf("   \n");
            setColRGB(r,g,b);
            printf("   ");
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            if(head)
            {
                printf(" * ");
            }
            else
                printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2);
            printf("   ");
            setColRGB(r,g,b);
            printf("   ");
            setCol(-1);
            printf("   \n");
            break;
        case 8: // xxx
                 // x
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
            setColRGB(r,g,b);
            printf("   ");
            setCol(-2);
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-2);
            break;
        case 9: // xxx
            //        x
            printf("   ");
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
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
            printf("      ");
            setColRGB(r-SMALLOFF, g-SMALLOFF,b-SMALLOFF);
            printf("   ");
            setCol(-2);
            break;
        case 1: //x
                // x
                // x
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
                printf("SOMETHING WENT WRONG OH NO\n"); //oh no :(
    }
}*/

void renderShapeLineRGB(int type, int r, int g, int b, int line) //all shapes have 3 lines
{
        switch(line){
            case 0:
                renderLine0(type,r,g,b);
                break;
            case 1:
                renderLine1(type,r,g,b);
                break;
            case 2:
                renderLine2(type,r,g,b);
                break;
            default:
                printf("Invalid shape line!\n");
                break;
        }
}
void renderShapeLine(int type, int color, int line)
{
    renderShapeLineRGB(type, colors[color*3],colors[color*3+1],colors[color*3+2],line);
}

