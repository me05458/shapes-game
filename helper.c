#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "settings.h"
#include "helper.h"
#include "shapes.h"
#include <time.h>
#include <stdbool.h>

int field[SIZE][SIZE][5]; //field
int blocks[BLOCKNUM] = BLOCKS;
int colors[COLNUM+1][3] = COLORS;
int c_block;
int c_col;
int lastPlacedx = -1;
int lastPlacedy = -1;
int fullCount = 0;
bool started = true;
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
    if(color == -1)
    {
        int col = BASECOL;
        int rmod = RMOD;
        int gmod = GMOD;
        int bmod = BMOD;
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
        field[xpos][ypos][0]=col+rmod;
        field[xpos][ypos][1]=col+gmod;
        field[xpos][ypos][2]=col+bmod;
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
{ //SHAPES
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
            field[x][y-1][4] = true;
            field[x][y+1][4] = true;
            changeColor(x,y-1,col);
            changeColor(x,y+1,col);
            fullCount+=3;
            break;
        case 3:
            if(y>=SIZE-1 || x>=SIZE-1)
            {
                return 2;
            }
            if(field[x][y+1][4] == true ||field[x+1][y+1][4] == true || field[x+1][y][4] == true)
            {
                return 4;
            }
            changeColor(x+1,y+1,col);
            changeColor(x+1,y,col);
            changeColor(x,y+1,col);
            field[x+1][y+1][4] = true;
            field[x][y+1][4] = true;
            field[x][y][4] = true;
            field[x+1][y][4] = true;
            fullCount+=4;
            break;
        case 4:
            if(y>=SIZE-1)
            {
                return 2;
            }
            if(field[x][y+1][4] == true)
            {
                return 4;
            }
            changeColor(x,y+1,col);
            field[x][y+1][4] = true;
            fullCount+=2;
            break;
        case 5:
            if(x>=SIZE-1)
            {
                return 2;
            }
            if(field[x+1][y][4]==true)
            {
                return 4;
            }
            changeColor(x+1,y,col);
            field[x+1][y][4]=true;
            fullCount+=2;
            break;
        default:
            return 3;

    }
    lastPlacedx = x;
    lastPlacedy = y;
    changeColor(x,y,col);
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

bool isEmpty()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE;j++)
        {
            if(field[i][j][4]==true)
            {
                return false;
            }
        }
    }
    return true;
}


void clearFull()
{
    //rows:
    int ri[SIZE];
    int rinum = 0;
    bool full = true;
    for(int i = 0; i<SIZE; i++)
    {
        full = true;
        for(int j = 0; j<SIZE; j++)
        {
            if(field[i][j][4]==false)
            {
                full = false;
            }
        }
        if(full == true)
        {
            ri[rinum] = i;
            rinum++;
        }
    }
    int rj[SIZE];
    int rjnum = 0;
    for(int j = 0; j<SIZE; j++)
    {
        full = true;
        for(int i = 0; i<SIZE; i++)
        {
            if(field[i][j][4]==false)
            {
                full = false;
            }
            field[i][j][3] = false;
        }
        if(full == true)
        {
            rj[rjnum] = j;
            rjnum++;
        }
    }
    if(rjnum != 0 || rinum !=0)
    {

        for(int i = 0; i<rinum; i++)
        {
            for(int j = 0; j<SIZE; j++)
            {
                int q = ri[i];
                field[q][j][4] = false;
                field[q][j][3] = true;
            }
        }
        for(int j = 0; j<rjnum; j++)
        {
            for(int i = 0; i<SIZE; i++)
            {
                int q = rj[j];
                if(field[i][q][4] == true)
                {
                    field[i][q][3] = true;
                    field[i][q][4] = false;
                }
            }
        }
        field[lastPlacedx][lastPlacedy][3] = true;
        waitMS(500);
        renderBoardHead();
        waitMS(500);
        bool lastImpacted;
        for(int i = 0; i<rinum; i++)
        {
            for(int j = 0; j<SIZE; j++)
            {
                int q = ri[i];
                changeColor(q,j,-1);
                field[q][j][3] = false;
                if(q == lastPlacedx && j == lastPlacedy)
                {
                    lastImpacted = true;
                }
            }
        }
        for(int j = 0; j<rjnum; j++)
        {
            for(int i = 0; i<SIZE; i++)
            {
                int q = rj[j];
                changeColor(i,q,-1);
                field[i][q][3] = false;
                if(q == lastPlacedy && i == lastPlacedx)
                {
                    lastImpacted = true;
                }
            }
        }
        field[lastPlacedx][lastPlacedy][3] = false;
        if(lastImpacted){
            renderBoardHead();
        }
        else
        {
            renderBoard();
        }
    }
}

void waitMS(int ms) //this is such a funny way of sleeping this is what I shall do.
{
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
int canPlace(int shape)
{//SHAPE
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
        case 3:
            for(int i = 0; i<SIZE-1;i++)
            {
                for(int j = 0; j<SIZE-1; j++)
                {
                    if(field[i][j][4] == false && field[i][j+1][4] == false && field[i+1][j][4] == false&&field[i+1][j+1][4] == false)
                    {
                        return i;
                    }
                }
            }
            return -1;
        case 4:
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
                    if(run ==2)
                    {
                        return i;
                    }
                }
                run = 0;
            }
            return -1;
        case 5:
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
                    if(run ==2)
                    {
                        return i;
                    }
                }
                run = 0;
            }
            return -1;
        default:
            printf("\033[91msomething went wrong\n\033[0m");
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
void renderBoardHead()
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
            renderShapeRGB(-1,field[i][j][0],field[i][j][1],field[i][j][2],field[i][j][3]);
        }
        printf("\n");
    }
    setCol(-1);
    printf("\n");
    renderShape(c_block,c_col,true);
}
int init()
{
    started = true;
    char randString[32];
    if(sodium_init() <0){ //random library died! Oh no!
        printf("\e[91mA Catastrophic Faliure Occured (EXIT CODE 2)\e[0m\n");
        return 2;
    }
    fullCount = 0;
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
