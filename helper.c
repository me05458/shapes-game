#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "settings.h"
#include "helper.h"
#include "shapes.h"
int field[SIZE][SIZE][5]; //field
int blocks[BLOCKNUM] = BLOCKS;
int colors[COLNUM+1][3] = COLORS;
int c_block;
int c_col;
int lastPlacedx = -1;
int lastPlacedy = -1;
int fullCount = 0;
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
    int rmod = 0;
    int gmod = 0;
    int bmod = 0;
    if(MODBLOCK)
    {
        rmod = RMOD;
        gmod = GMOD;
        bmod = BMOD;
    }
    if(xpos<0 || ypos<0 || xpos>9||ypos>9)
    {
        printf("\e[91msomething went wrong\e[0m\n");
        return;
    }
    int col = BASECOL;
    if(xpos%2 == ypos%2)
    {
            rmod-=SMALLOFF;
            gmod-=SMALLOFF;
            bmod-=SMALLOFF;
    }
    if((xpos/SUBDIV)%2 == (ypos/SUBDIV)%2)
    {
        rmod-=BIGOFF;
        gmod-=BIGOFF;
        bmod-=BIGOFF;
    }
    else
    {
        col = BASECOL;
    }
    field[xpos][ypos][0]=r+rmod;
    field[xpos][ypos][1]=g+gmod;
    field[xpos][ypos][2]=b+bmod;
}
void changeColor(int xpos, int ypos, int color)
{
    if(xpos<0 || ypos<0 || xpos>9||ypos>9)
    {
        printf("\e[91msomething went wrong\e[0m\n");
        return;
    }
    if(color<0 || color >COLNUM)
    {
        color = 0;
    }
    changeColorRGB(xpos,ypos,colors[color][0],colors[color][1],colors[color][2]);
}

//haha this function is back!
int charEater(char c)
{
    int result =  c - '0'; //the numbers are consecutive so subtract 0
    if(result > 9||result<0) //it's a letter/other character
        return -1;
    return result;
}
int blockToField(int x, int y, int block, int col)
{
    if(x<0 || y<0 || x>=SIZE||y>=SIZE)
    {
        return 1;
    }
    if(field[x][y][4]==true)
    {
        return 4;
    }
    switch(block){
        case(0):
            changeColor(x,y,col);
            fullCount++;
            break;
        case(1):
            if(x<1||x>=SIZE-1)
            {
                return 2;
            }
            if(field[x-1][y][4] == true ||field[x+1][y][4] == true)
            {
                return 4;
            }
            changeColor(x,y,col);
            field[x-1][y][4] = true;
            changeColor(x-1,y,col);
            field[x+1][y][4] = true;
            changeColor(x+1,y,col);
            fullCount += 3;
            break;
        case(2):
            if(y<1||y>=SIZE-1)
            {
                return 2;
            }
            if(field[x][y-1][4] == true ||field[x][y+1][4] == true)
            {
                return 4;
            }
            changeColor(x,y,col);
            field[x][y-1][4] = true;
            field[x][y+1][4] = true;
            changeColor(x,y-1,col);
            changeColor(x,y+1,col);
            fullCount+=3;
            break;
        default:
            return 3;

    }
    lastPlacedx = x;
    lastPlacedy = y;
    field[x][y][4] = true;
    return 0;
}
bool isFull()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE;j++)
        {
            if(field[i][j][4]==false)
            {
                return false;
            }
        }
    }
    return true;
}

int canPlace(int shape)
{
    switch(shape){
        case(0):
            for(int i = 0; i<SIZE; i++)
            {
                for(int j = 0; j<SIZE; j++)
                {
                    if(field[i][j][4] == false)
                    {
                        return i;
                    }
                }
            }
            return -1;
        case(2):
            int run=0;
            for(int i = 0; i<SIZE; i++)
            {
                for(int j = 0; j<SIZE; j++)
                {
                    if(field[i][j][4] == false)
                    {
                        run++;
                    }
                    else
                    {
                        run = 0;
                    }
                    if(run ==3)
                    {
                        return i;
                    }
                }
                run = 0;
            }
            return -1;
        case(1):
            for(int j = 0; j<SIZE; j++)
            {
                for(int i = 0; i<SIZE; i++)
                {
                    if(field[i][j][4] == false)
                    {
                        run++;
                    }
                    else
                    {
                        run = 0;
                    }
                    if(run ==3)
                    {
                        return i;
                    }
                }
                run = 0;
            }
            return -1;
        default:
            printf("\033[91mSomething went wrong\n\033[0m");
            break;
    }
}

void renderBoard()
{
    clearScreen();
    printf("  ");
    for(int i = 0; i<SIZE; i++)
    {
        printf(" %d ",i);
    }
    printf("\n");
    for(int i = 0; i<SIZE; i++)
    {
        printf("%d ",i);
        for(int j = 0; j<SIZE; j++)
        {
            renderShapeRGB(-1,field[i][j][0],field[i][j][1],field[i][j][2],(lastPlacedx==i&&lastPlacedy==j));
        }
        printf("\n");
    }
    setCol(-1);
    printf("\n");
    renderShape(c_block,c_col,true);
}
int init()
{
    char randString[32];
    if(sodium_init() <0){ //random library died! Oh no!
        printf("\e[91mA Catastrophic Faliure Occured (EXIT CODE 2)\e[0m\n");
        return 2;
    }
    int col = BASECOL;
    int rmod = 0;
    int gmod = 0;
    int bmod = 0;
    randombytes_buf(randString, 32);
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            if(i%2 == j%2)
            {
                rmod = RMOD-SMALLOFF;
                gmod = GMOD-SMALLOFF;
                bmod = BMOD-SMALLOFF;
            }
            else
            {
                rmod = RMOD;
                gmod = GMOD;
                bmod = BMOD;
            }
            if((i/SUBDIV)%2 == (j/SUBDIV)%2)
            {
                rmod-=BIGOFF;
                gmod-=BIGOFF;
                bmod-=BIGOFF;
            }
            else
            {
                col = BASECOL;
            }
            field[i][j][0] = col+rmod;
            field[i][j][1] = col+gmod;
            field[i][j][2] = col+bmod;
            field[i][j][3] = false;
            field[i][j][4] = false;

        }
    }
    return 0;
}
