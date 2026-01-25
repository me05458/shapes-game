#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "settings.h"
#include "helper.h"
extern int field[10][10][4]; //field
extern int blocks[BLOCKNUM];
extern int colors[COLNUM+1][3];
void renderBoard()
{
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            renderShapeRGB(-1,field[i][j][0],field[i][j][1],field[i][j][2],field[i][j][3]);
        }
        printf("\n");
    }
    setCol(-1);
}

int main()
{
    clearScreen();
    init();
    renderBoard();
    changeColor(0,0,1);
    changeColor(1,0,1);
    field[2][0][3]=0;
    field[1][0][3]=0;
    printf("\n");
    renderBoard();
    return 0;
}
