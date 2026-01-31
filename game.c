#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "settings.h"
#include "helper.h"
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
extern int field[SIZE][SIZE][5]; //field
extern int blocks[BLOCKNUM];
extern int colors[COLNUM+1][3];
extern int lastPlacedx;
extern int lastPlacedy;
extern int c_block;
extern int c_col;
extern bool started;
int reloadCount = 0;
int hintCount = 0;
extern int fullCount;
int blockCount = 0;

void debug()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            printf(" %d ",field[i][j][4]);
        }
        printf("\n");
    }
}

int main()
{
    //this is some initialization nonsense
    bool fieldCol = BASECOL+RMOD-SMALLOFF-BIGOFF<0||BASECOL+BMOD-SMALLOFF-BIGOFF<0||BASECOL+GMOD-SMALLOFF-BIGOFF<0;
    bool fieldCol2 = BASECOL+RMOD>255||BASECOL+BMOD>255||BASECOL+GMOD>255;
    bool otherCol = false;
    if(MODBLOCK)
    {
        for(int i = 0; i<COLNUM+1; i++)
        {
            if(colors[i][0]+RMOD-SMALLOFF-BIGOFF<0 || colors[i][1]+GMOD-SMALLOFF-BIGOFF<0 || colors[i][2]+BMOD-SMALLOFF-BIGOFF<0)
            {
                otherCol = true;
            }
            if(colors[i][0]+RMOD>255 || colors[i][1]+GMOD>255 || colors[i][2]+BMOD>255)
            {
                otherCol = true;
            }
        }
    }
    else
    {
        for(int i = 0; i<COLNUM+1; i++)
        {
            if(colors[i][0]-SMALLOFF-BIGOFF<0 || colors[i][1]-SMALLOFF-BIGOFF<0 || colors[i][2]-SMALLOFF-BIGOFF<0)
                otherCol = true;
            if(colors[i][0]>255 || colors[i][1]>255 || colors[i][2]>255)
            {
                otherCol = true;
            }
        }
    }
    if(fieldCol || otherCol || fieldCol2)
    {
        printf("\033[91mALERT! Color values have not passed checksums. In order to propperly view board, it is recommended to modify color settings. Running ./settings can help diagnose the problem.\033[0m\n");
        printf("Proceed anyway? (Y/N)\n");
        char tmp = getchar();
        if(tmp == 'n' || tmp =='N'|| tmp == '\n')
        {
            return 0;
        }
        cleanChar();
    }
    int keepgo = 1;
    clearScreen();
    int a = init();
    if(a != 0)
    {
        return a;
    }
    /*printf("enter char: ");
    char input;
    input = getchar();
    cleanChar();*/
    c_block = blocks[randombytes_uniform(BLOCKNUM)];
    c_col = randombytes_uniform(COLNUM)+1;
    renderBoard();
    while(keepgo)
    {
        whilestart:
        if(canPlace(c_block) == -1)
        {
            if(RELOAD)
            {
                printf("Nowhere to place this piece! Get a new one? (Y/n)\n");
                char tmp = getchar();
                if(tmp == 'n' || tmp == 'N')
                {
                    goto lost;
                }
                else
                {
                    reloadCount++;
                    c_block = randombytes_uniform(BLOCKNUM);
                    c_col = randombytes_uniform(COLNUM)+1;
                    renderBoard();
                    if(tmp != '\n')
                    {
                        cleanChar();
                    }
                    goto whilestart;
                }
            }
            else
            {
                lost:
                printf("Oh no! You loose!\n"
                    "You used %d hints, placed %d blocks, used %d reloads, and covered %d squares.\n",hintCount,blockCount,reloadCount,fullCount);
                cleanChar();
                goto playagain;
            }
        }
        if(CLEAR==1)
        {
            clearFull();
            if(!started&&isEmpty())
            {
                printf("Congradulations! You win!\n"
                "You used %d hints, placed %d blocks, and used %d reloads\n",hintCount,blockCount,reloadCount
                );
                goto playagain;
            }
        }
        printf("enter coordinates to place: ");
        char xtmp = getchar();
        if(xtmp == 'q' || xtmp=='Q')
        {
            keepgo=0;
            break;
        }
        if(xtmp == 'h' || xtmp == 'H')
        {
            cleanChar();
            int q = canPlace(c_block);
            hintCount++;
            if(q == -1)
            {
                printf("Oh no! There is nowhere to place this shape!\n");
            }
            else
            {
                printf("Look in row %d.\n", q);
                goto whilestart;
            }
        }
        if(xtmp == 'D' || xtmp == 'd')
        {
            cleanChar();
            debug();
            goto whilestart;
        }
        if(xtmp == '\n')
        {
            if(NORM_COORD ==0)
            {
                if(DOUBLEINT == 1 && SIZE > 10)
                    printf("To select coordinates, enter the row value and column value like this: 0305 to put at row 3 and column 5. Or 1001 to put at row 10 and column 1 Use 'h' to get a hint.\n");
                else if(DOUBLEINT == 1)
                    printf("To select coordinates, enter the row value and column value like this: 35 to put at row 3 and column 5. Use 'h' to get a hint.\n");
                else
                {
                    printf("To select coordinates, enter the row value and column value like this: 3,5 to put at row 3 and column 5. Use 'h' to get a hint.\n");
                }
            }
            else
            {
                if(DOUBLEINT == 1 && SIZE > 10)
                    printf("To select coordinates, enter the row value and column value like this: 0305 to put at column 3 and row 5. Or 1001 to put at column 10 and row 1 Use 'h' to get a hint.\n");
                else if(DOUBLEINT == 1)
                    printf("To select coordinates, enter the row value and column value like this: 35 to put at column 3 and row 5. Use 'h' to get a hint.\n");
                else
                {
                    printf("To select coordinates, enter the row value and column value like this: 3,5 to put at column 3 and row 5. Use 'h' to get a hint.\n");
                }
            }
            goto whilestart;
        }
        char x2tmp = getchar();
        if(x2tmp == '\n')
        {
            printf("incomplete coordinates\n");
            goto endhere;
        }
        if(x2tmp == ','&&DOUBLEINT != 1)
        {
            if(SIZE>10)
            {
                x2tmp = xtmp;
                xtmp = '0';
            }
        }
        if(x2tmp == ',' && DOUBLEINT == 1){
            printf("incorrect coordinate formatting.");
            cleanChar();
            goto endhere;
        }
        int y = 0;
        int x = 0;
        if(SIZE<=10 && DOUBLEINT == 1)
        {
            cleanChar();
            if(NORM_COORD != 0)
            {
                x = charEater(x2tmp);
                y = charEater(xtmp);
            }
            else
            {
                y = charEater(x2tmp);
                x = charEater(xtmp);
            }
            goto placetime;
        }
        char ytmp = getchar();
        if(ytmp == '\n')
        {
            printf("incomplete coordinates\n");
            goto endhere;
        }
        if(SIZE<=10)
        {
            cleanChar();
            if(NORM_COORD != 0)
            {
                x = charEater(ytmp);
                y = charEater(xtmp);
            }
            else
            {
                y = charEater(ytmp);
                x = charEater(xtmp);
            }
            goto placetime;
        }
        char y2tmp = getchar();
        if(y2tmp == '\n')
        {
            if(DOUBLEINT == 1)
            {
                    printf("incomplete coordinates\n");
                    goto endhere;
            }
                y2tmp = ytmp;
                ytmp = '0';
        }
        else
        {
            cleanChar();
        }
        if(NORM_COORD==0)
        {
                y = charEater(ytmp)*10 + charEater(y2tmp);
                x = charEater(xtmp)*10 + charEater(x2tmp);
        }
        else
        {
                y = charEater(xtmp)*10 + charEater(x2tmp);
                x = charEater(ytmp)*10 + charEater(y2tmp);
        }
        placetime:
        int l = blockToField(x,y,c_block,c_col);
        if(l == 1)
        {
            printf("\e[91mnot valid coordinates\e[0m\n");
        }
        else if(l == 2 || l==4)
        {
            printf("\e[91mblock doesn't fit here\e[0m\n");
        }
        else if(l==3)
        {
            printf("\e[91msomething weird happened!\e[0m\n");
        }
        else
        {
            blockCount++;
            c_block = blocks[randombytes_uniform(BLOCKNUM)];
            c_col = randombytes_uniform(COLNUM)+1;
            started = false;
            renderBoard();

        }
        endhere:
        if(isFull())
        {
            printf("Congradulations! You win!\n"
                "You used %d hints, placed %d blocks, and used %d reloads\n",hintCount,blockCount,reloadCount
            );
            playagain:
            printf("Play again? (Y/n)\n");
            char tmp = getchar();
            if(tmp == 'n' || tmp == 'N'||tmp=='q'||tmp=='Q')
            {
                printf("goodbye!\n");
                return 0;
            }
            else
            {
                reloadCount = 0;
                blockCount = 0;
                hintCount = 0;
                init();
                renderBoard();
                cleanChar();
            }
        }

    }
    return 0;
}
