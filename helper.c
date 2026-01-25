#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "helper.h"
int field[10][10][4]; //field
int blocks[BLOCKNUM] = BLOCKS;
int colors[COLNUM+1][3] = COLORS;
void cleanChar()
{
    while(getchar() != '\n')
        continue;
}

void clearScreen()
{
    if(USE_SYS == 1)
    {
        system("clear");
    }
}
void changeColorRGB(int xpos, int ypos, int r, int g, int b)
{
    if((xpos+ypos)%2==0)
    {
        r-=50;
        g-=50;
        b-=50;
    }
    field[xpos][ypos][0]=r;
    field[xpos][ypos][1]=g;
    field[xpos][ypos][2]=b;
}
void changeColor(int xpos, int ypos, int color)
{
    if(color<0 || color >COLNUM)
    {
        color = 0;
    }
    changeColorRGB(xpos,ypos,colors[color][0],colors[color][1],colors[color][2]);
}
void init()
{
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            if((i+j)%2==0)
            {
                field[i][j][0] = 150;
                field[i][j][1] = 150;
                field[i][j][2] = 150;
                field[i][j][3] = -1;
            }
            else
            {
                field[i][j][0] = 200;
                field[i][j][1] = 200;
                field[i][j][2] = 200;
                field[i][j][3] = -1;
            }
        }
    }
}
