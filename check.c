#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "settings.h"
#include "helper.h"
extern int field[10][10][4]; //field
extern int blocks[BLOCKNUM];
extern int colors[COLNUM+1][3];
void printCols()
{
    printf("colors: \n");
    for(int i = 0; i<10;i++)
    {
        printf("%d:       ",i);
        renderShape(blocks[0],1,-1);
    }
    printf("DEFAULT: ");
    renderShape(0,11,-1);
}

void printBlocks()
{
    for(int i = 0; i<BLOCKNUM-1; i++)
    {
        printf("%d:\n",i);
        renderShape(blocks[i],i%10,-1);
        printf("\n");
    }
    printf("%d:\n",BLOCKNUM-1);
    renderShape(blocks[BLOCKNUM-1],(BLOCKNUM-1)%10,-1);

}

int main()
{
    clearScreen();
    printCols();
    printf("----------------------------\n----------------------------\n");
    printBlocks();
    return 0;
}
