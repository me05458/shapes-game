#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "helper.h"
#include <time.h>
#include <unistd.h>
#include "vars.h"
#include "file.h"
#define return uninit(); return //I was too lazy to rewrite the returns to uninitialize...

int reloadCount = 0; //how many times we reloaded
int hintCount = 0;//hints used
int blockCount = 0; //blocks placed

void debug() //just print out full or not for debuggery
//I left it in because why not?
//easter egg ig
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
    //are the colors right?
    //printf("more stupid problems: |%c|\n",298);
    int a = init(); //check if library works?
    if(a != 0)
    {
        return a;
    }
    int tmp1 = BIGOFF; //a stupid solution, I know.
    if(!MODCOL)
    {
        BIGOFF = 0;
    }
    bool fieldCol = BASECOL+RMOD-SMALLOFF-BIGOFF<0||BASECOL+BMOD-SMALLOFF-BIGOFF<0||BASECOL+GMOD-SMALLOFF-BIGOFF<0;
    bool fieldCol2 = BASECOL+RMOD>255||BASECOL+BMOD>255||BASECOL+GMOD>255;
    bool otherCol = false;
    if(MODBLOCK) //check mods if that's a thing
    {
        for(int i = 0; i<COLNUM+1; i++)
        {
            if(colors[i*3]+RMOD-SMALLOFF-BIGOFF<0 || colors[i*3+1]+GMOD-SMALLOFF-BIGOFF<0 || colors[i*3+2]+BMOD-SMALLOFF-BIGOFF<0)
            {
                otherCol = true;
            }
            if(colors[i*3]+RMOD>255 || colors[i*3+1]+GMOD>255 || colors[i*+2]+BMOD>255)
            {
                otherCol = true;
            }
        }
    }
    else
    {
        for(int i = 0; i<COLNUM+1; i++)
        {
            if(colors[i*3]-SMALLOFF-BIGOFF<0 || colors[i*3+1]-SMALLOFF-BIGOFF<0 || colors[i*3+2]-SMALLOFF-BIGOFF<0)
                otherCol = true;
            if(colors[i*3]>255 || colors[i*3+11]>255 || colors[i*3+2]>255)
            {
                otherCol = true;
            }
        }
    }
    BIGOFF = tmp1;
    if(fieldCol || otherCol || fieldCol2) //if colors bad
    {
        printf("\033[91mALERT! Color values have not passed checksums. In order to propperly view board, it is recommended to modify color settings.\033[0m\n");
        printf("Proceed anyway? (Y/N)\n"); //warn but can keep going
        char tmp = getchar();
        if(tmp == 'n' || tmp =='N'|| tmp == '\n')
        {
            return 0; //default is to continue
        }
        cleanChar();
    }
    int keepgo = 1; //I don't know if this matters?
    clearScreen();
    //generate first block
    c_block = blocks[randombytes_uniform(BLOCKNUM)];
    c_col = randombytes_uniform(COLNUM)+1;
    renderBoard(); //first render
    while(keepgo) //I don't know if this matters?
    {
        whilestart:
        if(CLEAR==1) //if clear lines...
        {
            clearFull();
            if(!started&&isEmpty())
            {
                //you win when the thing's empty, except it's empty at the start, so ignore that case!
                if(RELOAD)
                {
                    printf("Congradulations! You win!\n"
                    "You used %d hints, placed %d blocks, used %d reloads, and cleared %d lines\n",hintCount,blockCount,reloadCount,lineCount
                    );
                }
                else
                {
                    printf("Congradulations! You win!\n"
                    "You used %d hints, placed %d blocks, and cleared %d lines\n",hintCount,blockCount,lineCount
                    );
                }
                goto playagain; //ask to play again (see bellow)
            }
        }
        if(canPlace(c_block) == -1) //if can't place...
        {
            if(RELOAD) //if allowed to, ask to reload
            {
                printf("Nowhere to place this piece! Get a new one? (Y/n)\n");
                char tmp = getchar();
                if(tmp == 'n' || tmp == 'N')
                {
                    cleanChar();
                    goto lost;
                }
                else //default = new.
                {
                    if(tmp != '\n')
                    {
                        cleanChar();
                    }
                    reloadCount++; //oooo reloads
                    //just make a new one
                    c_block = randombytes_uniform(BLOCKNUM);
                    c_col = randombytes_uniform(COLNUM)+1;
                    renderBoard();
                    goto whilestart; //start at start
                }
            }
            else //if no reloads, loose.
            {
                lost: //go here to play lost sequence.
                if(RELOAD)
                {
                    printf("Oh no! You loose!\n"
                    "You used %d hints, placed %d blocks, used %d reloads, and cleared %d lines.\n",hintCount,blockCount,reloadCount,lineCount);
                }
                else
                {
                    printf("Oh no! You loose!\n"
                    "You used %d hints, placed %d blocks, and cleared %d lines.\n",hintCount,blockCount,lineCount);
                }
                goto playagain; //play again.
            }
        }
        printf("enter coordinates to place: "); //okay let's place one
        char xtmp = getchar(); //first only the first digit.
        if(xtmp == 'q' || xtmp=='Q') //oh, quit
        {
            keepgo=0;
            break;
        }
        if(xtmp == 'm') //I mistype make in here often enough to justify this.
        {
            xtmp = getchar();
            if(xtmp == 'a')
            {
                xtmp = getchar();
                if(xtmp == 'k')
                {
                    xtmp = getchar();
                    if(xtmp == 'e')
                    {
                        printf("\e[91mYou're still in the program!\e[0m\n");
                        cleanChar();
                        goto whilestart;
                    }
                }
            }
        } //same with ./game
        if(xtmp == '.')
        {
            xtmp = getchar();
            if(xtmp == '/')
            {
                xtmp = getchar();
                if(xtmp == 'g')
                {
                    xtmp = getchar();
                    if(xtmp == 'a')
                    {
                        xtmp = getchar();
                        if(xtmp == 'm')
                        {
                            xtmp = getchar();
                            if(xtmp == 'e')
                            {
                                printf("\e[91mYou're still in the program!\e[0m\n");
                                cleanChar();
                                goto whilestart;
                            }
                        }
                    }
                }
            }
        }
        if(xtmp == 'h' || xtmp == 'H') //hint
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
        if(xtmp == 'D' || xtmp == 'd') //debug
        {
            cleanChar();
            debug();
            goto whilestart;
        }
        if(xtmp == '\n') //tell person how to play, depending on the doubleint and coordinate types.
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
            goto whilestart; //go to begining
        }
        if(charEater(xtmp) < 0)
        {
            printf("\e[91mletters are not coordinates\e[0m\n");
            cleanChar();
            goto whilestart;
        }
        char x2tmp = getchar(); //okay, next character
        if(x2tmp == '\n') //clearly not enough numbers
        {
            printf("\e[91mincomplete coordinates\e[0m\n");
            goto endhere; //to end
        }
        if(x2tmp == ','&&DOUBLEINT != 1) //comma coordinates used, all good.
        {
            if(SIZE>10) //only single digits used.
            {
                x2tmp = xtmp;
                xtmp = '0';
            }
        }
        if(x2tmp == ',' && DOUBLEINT == 1){
            printf("\e[91mincorrect coordinate formatting.\e[0m"); //we're not doing , coordinates
            cleanChar();
            goto endhere;
        }
        if(charEater(x2tmp) < 0)
        {
            printf("\e[91mletters are not coordinates\e[0m\n");
            cleanChar();
            goto whilestart;
        }
        int y = 0; //it's time to start some spot checking.
        int x = 0;
        if(SIZE<=10 && DOUBLEINT == 1) //if less than 10 and no commas
        {
            cleanChar();
            if(NORM_COORD != 0) //just which one do you check fist.
            {
                x = charEater(x2tmp);
                y = charEater(xtmp);
            }
            else
            {
                y = charEater(x2tmp);
                x = charEater(xtmp);
            }
            goto placetime; //place it (see later)
        }
        char ytmp = getchar(); //okay let's get more things because we need more of them
        if(ytmp == '\n') //not enough coordinates at this point.
        {
            printf("\e[91mincomplete coordinates\e[0m\n");
            goto endhere; //end
        }
        if(charEater(ytmp) < 0)
        {
            printf("\e[91mletters are not coordinates\e[0m\n");
            cleanChar();
            goto whilestart;
        }
        if(SIZE<=10) //okay, we've done a,b with single digits. just set x,y
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
        char y2tmp = getchar(); //okay, double digits...
        if(y2tmp == '\n')
        {
            if(charEater(y2tmp) < 0)
            {
                printf("\e[91mletters are not coordinates\e[0m\n");
                cleanChar();
                goto whilestart;
            }
            if(DOUBLEINT == 1) //we need that second digit!!
            {
                    printf("\e[91mincomplete coordinates\e[0m\n");
                    goto endhere;
            }
                y2tmp = ytmp;
                ytmp = '0';
        }
        else //all done :)
        {
            cleanChar();
        }
        if(NORM_COORD==0) //final coordinate setting
        {
                y = charEater(ytmp)*10 + charEater(y2tmp);
                x = charEater(xtmp)*10 + charEater(x2tmp);
        }
        else
        {
                y = charEater(xtmp)*10 + charEater(x2tmp);
                x = charEater(ytmp)*10 + charEater(y2tmp);
        }
        placetime: //time to actually set it
        int l = blockToField(x,y,c_block,c_col); //try putting it in field
        if(l == 1) //if invalid coordinates
        {
            printf("\e[91mnot valid coordinates\e[0m\n");
        }
        else if(l == 2 || l==4) //if block doesn't fit'
        {
            printf("\e[91mblock doesn't fit here\e[0m\n");
        }
        else if(l==3) //if a bad block (I guess) was done.
        { //shouldn't happen.'
            printf("\e[91msomething weird happened!\e[0m\n");
        }
        else //place.
        {
            blockCount++; //only now do we increment here.
            c_block = blocks[randombytes_uniform(BLOCKNUM)];
            c_col = randombytes_uniform(COLNUM)+1;
            started = false;
            renderBoard();

        }
        endhere: //this is the end.
        if(isFull()) //if filled it all, we won! (only happens in the case where winning via filling is possible)
        {
            printf("Congradulations! You win!\n"
                "You used %d hints, placed %d blocks, used %d reloads, and cleared %d lines\n",hintCount,blockCount,reloadCount, lineCount
            );
            playagain: //play again time
            printf("Play again? (Y/n)\n"); //default == y
            char tmp = getchar();
            if(tmp == 'n' || tmp == 'N'||tmp=='q'||tmp=='Q') //quit
            {
                printf("goodbye!\n");
                return 0;
            }
            else
            {
                //reset all the numbers
                reloadCount = 0;
                blockCount = 0;
                hintCount = 0;
                init(); //reinitialize
                renderBoardHead(); //render cleared
                if(tmp !='\n')
                {
                    cleanChar();
                }
            }
        }

    }
    return 0; //done
}
