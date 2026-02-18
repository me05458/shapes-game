#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "helper.h"
#include "shapes.h"
#include "file.h"
#include <time.h>
#include <stdbool.h>
void cleanChar() //classic cleanchar function.
{
    //just get all the characters until newline.
    while(getchar() != '\n')
        continue;
}

void clearScreen()
{
    //only clear if using it, mostly for debugging.
    if(USE_SYS == 1)
    {
        system("clear");
    }
}
void changeColorRGB(int xpos, int ypos, int r, int g, int b)
{ //sets an element of field to a color
    //classic mods
    int rmod = 0;
    int gmod = 0;
    int bmod = 0;
    if(MODBLOCK)
    {
        rmod = RMOD;
        gmod = GMOD;
        bmod = BMOD;
    }
    if(xpos<0 || ypos<0 || xpos>SIZE||ypos>SIZE) //deal with bad sizes
    {
        printf("\e[91msomething went wrong\e[0m\n");
        return;
    }
    if(xpos%2 == ypos%2) //every other checker
    {
            rmod-=SMALLOFF;
            gmod-=SMALLOFF;
            bmod-=SMALLOFF;
    }
    if(MODCOL)
    {
        if((xpos/SUBDIV)%2 == (ypos/SUBDIV)%2) //big sections of color
        {
            rmod-=BIGOFF;
            gmod-=BIGOFF;
            bmod-=BIGOFF;
        }
    }
    field[xpos][ypos][0]=r+rmod; //throw these guys in here
    field[xpos][ypos][1]=g+gmod;
    field[xpos][ypos][2]=b+bmod;
}
void changeColor(int xpos, int ypos, int color)
{ //chages color without RGB

    if(xpos<0 || ypos<0 || xpos>SIZE||ypos>SIZE)
    {
        printf("\e[91msomething went wrong\e[0m\n");
        return;
    }
    if(color == -1) //we're clearing/setting to field color
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
        field[xpos][ypos][0]=col+rmod; //go through and set these guys
        field[xpos][ypos][1]=col+gmod;
        field[xpos][ypos][2]=col+bmod;
        return;
    }
    else if(color<0 || color >COLNUM) //after ^ fix bad colors
    {
        color = 0;
    }
    //just call that other thing.
    changeColorRGB(xpos,ypos,colors[color*3],colors[color*3 + 1],colors[color*3+2]);
}

//haha this function is back!
int charEater(char c)
{
    int result =  c - '0'; //the numbers are consecutive so subtract 0
    if(result > 9||result<0) //it's a letter/other character
        return -1;
    return result; //I <3 this function
}
int blockToField(int x, int y, int block, int col) //place a block
{ //SHAPES
    //returns 1 == x,y not in field
    //returns 4 == elements of block are occupied
    //returns 2 == non-x,y blocks not in field (idk why)
    if(x<0 || y<0 || x>=SIZE||y>=SIZE) //CLEARLY bad x,y
    {
        return 1;
    }
    if(field[x][y][4]==true) //CLEARLY full
    {
        return 4;
    }
    switch(block){ //okay, render the blocks.
        case(0):
            //everything's already fine
            break;

        //each case has the following steps:
            //check specific x,y bad values
            //check if specific cells are full
            //if all good, set color & full
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
            break;
        case 6: //note that this guy sets x,y twice for elegance of code, sorry
            if(y<1||y>=SIZE-1 || x<1||x>=SIZE-1)
            {
                return 2;
            }
            //these bools are to make this a little cleaner because these guys have a lot of spots to check for ture:
            bool r1;
            bool r2;
            bool r3;
            r1 = field[x][y][4] == true || field[x][y+1][4] == true || field[x][y-1][4] == true;
            r2 = field[x+1][y][4] == true || field[x+1][y+1][4] == true || field[x+1][y-1][4] == true;
            r3 = field[x-1][y][4] == true || field[x-1][y+1][4] == true || field[x-1][y-1][4] == true;
            if(r1 || r2 || r3)
            {
                return 4;
            }
            for(int i = x-1; i<=x+1; i++)
            {
                for(int j = y-1; j<=y+1; j++)
                {
                    changeColor(i,j,col);
                    field[i][j][4] = true;
                }
            }
            break;
        case 7:
            if(y<1||y>=SIZE-1 || x<1||x>=SIZE-1)
            {
                return 2;
            }
            //this uses the bools from above
            r1 = field[x][y][4] == true || field[x][y+1][4] == true || field[x][y-1][4] == true;
            r2 = field[x+1][y][4] == true;
            r3 = field[x-1][y][4] == true;
            if(r1 || r2 || r3)
            {
                return 4;
            }
            changeColor(x,y+1,col);
            field[x][y+1][4]=true;

            changeColor(x,y-1,col);
            field[x][y-1][4]=true;

            changeColor(x+1,y,col);
            field[x+1][y][4]=true;
            changeColor(x-1,y,col);
            field[x-1][y][4]=true;
            break;
        case 8:
            if(y>=SIZE-2)
            {
                return 2;
            }
            if(x>=SIZE-1)
            {
                return 2;
            }
            if(field[x][y][4] == true || field[x][y+1][4] == true || field[x][y+2][4] == true || field[x+1][y][4] == true)
            {
                return 4;
            }
            changeColor(x,y+1,col);
            changeColor(x,y+2,col);
            changeColor(x+1,y,col);
            field[x][y+1][4] = true;
            field[x][y+2][4] = true;
            field[x+1][y][4] = true;
            break;
        case 9:
            if(y<=1)
            {
                printf("y");
                return 2;
            }
            if(x>=SIZE-1)
            {
                printf("e");
                return 2;
            }
            if(field[x][y][4] == true || field[x][y-1][4] == true || field[x][y-2][4] == true || field[x+1][y][4] == true)
            {
                return 4;
            }
            changeColor(x,y-1,col);
            changeColor(x,y-2,col);
            changeColor(x+1,y,col);
            field[x][y-1][4] = true;
            field[x][y-2][4] = true;
            field[x+1][y][4] = true;
            break;
        case 10:
            if(y>=SIZE-2 || x<1)
            {
                return 2;
            }
            if(field[x][y][4] == true || field[x][y+1][4] == true || field[x][y+2][4] == true||field[x-1][y][4]==true)
            {
                return 4;
            }
            changeColor(x,y+1,col);
            changeColor(x,y+2,col);
            changeColor(x-1,y,col);
            field[x][y+1][4] = true;
            field[x][y+2][4] = true;
            field[x-1][y][4] = true;
            break;
        default: //abnormal shape attempted!
            return 3;

    }
    //update last coordinates (for drawing)
    lastPlacedx = x;
    lastPlacedy = y;
    //change color and true for x,y
    changeColor(x,y,col);
    field[x][y][4] = true;
    // return 0 = good
    return 0;
}
bool isFull() //check if the whole thing's full (for winning in some modes)
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE;j++)
        {
            if(field[i][j][4]==false)
            {
                return false; //if anything's not full, return false
            }
        }
    }
    return true; //otherwise it's true
}

bool isEmpty() //check if the whole thing is empty (also sometimes for winning)
{ //literally the reverse of isFull()
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
{ //clear rows/cols that are full (doesn't include squares yet)
    printf("\e[?25l");
    //rows:
    int ri[SIZE]; //SIZE = max number of possible full i s
    int rinum = 0; //actual number of full i s
    bool full = true; //this is used to check fullness.
    for(int i = 0; i<SIZE; i++) //find full i s
    {
        full = true;
        for(int j = 0; j<SIZE; j++)
        {
            if(field[i][j][4]==false)
            {
                full = false; //oh, okay, it's not full
            }
        }
        if(full == true) //if it's full, add i to ri and increment rinum
        {
            ri[rinum] = i;
            rinum++;
        }
    }
    int rj[SIZE]; //same for j s
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
    if(rjnum != 0 || rinum !=0) //if at least 1 row/col is full
    {
        if(ANIMATE == 0) //just render * s
        {

            for(int i = 0; i<rinum; i++)
            {
                for(int j = 0; j<SIZE; j++)
                {
                    int q = ri[i]; //this line makes us only visit full i s
                    field[q][j][4] = false;
                    field[q][j][3] = true;
                }
            }
            for(int j = 0; j<rjnum; j++) //same thing
            {
                for(int i = 0; i<SIZE; i++)
                {
                    int q = rj[j];
                    if(field[i][q][4] == true) //only ones not already cleared
                    {
                        field[i][q][3] = true;
                        field[i][q][4] = false;
                    }
                }
            }

            //make the last one render too
            field[lastPlacedx][lastPlacedy][3] = true;
            renderBoardHead();

            waitMS(WAITTIME); //delay (customizable)

            //if last coordinates are part of the line to clear, should be cleared. else * should stay.
            bool lastImpacted;
            for(int i = 0; i<rinum; i++) //now we clear them (for i s)
            {
                for(int j = 0; j<SIZE; j++)
                {
                    int q = ri[i];
                    changeColor(q,j,-1);
                    field[q][j][3] = false;
                    if(q == lastPlacedx && j == lastPlacedy) //if we found last coord here.
                    {
                        lastImpacted = true;
                    }
                }
            }
            for(int j = 0; j<rjnum; j++) //same for j
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

            //there it's all supposed to be false:
            field[lastPlacedx][lastPlacedy][3] = false;
            if(lastImpacted){
                renderBoardHead(); //render to clear all
            }
            else
            {
                renderBoard(); //render including last coord
            }

        }
        else //animation, only changes rendering not looking for rows/cols
        {
            bool lastImpacted = false; //same thing
            bool changed = false;
            //good old inum and jnum
            for(int j = 0; j<SIZE; j++) //render through cols (all of the full ones at once)
            {
                for(int i = 0; i<rinum; i++) //i inside because up and down and have to render IN ORDER
                {
                    int q = ri[i];
                    field[q][j][4] = false;
                    field[q][j][3] = false;
                    changeColor(q,j,-1);
                    if(q == lastPlacedx && j == lastPlacedy)
                    {
                        lastImpacted = true;
                    }
                }
                if(rinum >0) //render (only if some i s are full, otherwise it would just be dumb delay)
                {
                    waitMS(WAITTIME/SIZE);
                    if(lastImpacted){
                        renderBoardHead();
                    }
                    else
                    {
                        renderBoard();
                    }
                }
            }
            for(int i = 0; i<SIZE; i++) //render through rows (all at once)
            {
                changed = false;
                for(int j = 0; j<rjnum; j++)
                {
                    int q = rj[j];
                    if(q == lastPlacedy && i == lastPlacedx)
                    {
                        lastImpacted = true;
                    }
                    if(field[i][q][4] == true) //only for ones that have not been cleared above
                    {

                        field[i][q][3] = false;
                        field[i][q][4] = false;
                        changeColor(i,q,-1);
                        changed = true;

                    }
                }
                if(changed) //only do waiting when legitimiately clearing squares
                {
                    waitMS(WAITTIME/SIZE);
                    if(lastImpacted){
                        renderBoardHead();
                    }
                    else
                    {
                        renderBoard();
                    }
                }
            }
        }
    }
    //count lines
    lineCount += rinum;
    lineCount += rjnum;
    printf("\e[?25h");
}

void waitMS(int ms) //this is such a funny way of sleeping this is what I shall do.
{
    struct timespec ts; //idk time stuff, too lazy to write comments
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
int canPlace(int shape) //CAN it go here?
//if no -> return -1. if yes -> return i value of first i where it can be placed.
{//SHAPES
    switch(shape){
        case(0): //just check all of the needed spots for each one
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
        case 6:
            bool r1 = false; //same r1, r2, r3 thing to check if the thing can be placed
            bool r2 = false;
            bool r3 = false;
            for(int i = 0; i<SIZE-2;i++)
            {
                for(int j = 0; j<SIZE-2; j++)
                {
                    r1 = field[i][j][4] == false && field[i][j+1][4] == false && field[i][j+2][4] == false;
                    r2 = field[i+1][j][4] == false && field[i+1][j+1][4] == false && field[i+1][j+2][4] == false;
                    r3 = field[i+2][j][4] == false && field[i+2][j+1][4] == false && field[i+2][j+2][4] == false;
                    if(r1&&r2&&r3)
                    {
                        return i;
                    }
                }
            }
            return -1;
        case 7:
            r1 = false;
            r2 = false;
            r3 = false;
            for(int i = 0; i<SIZE-2;i++)
            {
                for(int j = 0; j<SIZE-2; j++)
                {
                    r1 = field[i+1][j+1][4] == false && field[i][j+1][4] == false;
                    r2 = field[i+2][j+1][4] == false && field[i+1][j][4] == false;
                    r3 = field[i+1][j+2][4] == false;
                    if(r1&&r2&&r3)
                    {
                        return i;
                    }
                }
            }
            return -1;
        case 8:
            for(int i =0; i<SIZE-1; i++)
            {
                for(int j = 0; j<SIZE-2; j++)
                {
                    if(field[i][j][4] == false && field[i+1][j][4] == false && field[i][j+1][4] == false && field[i][j+2][4]==false)
                    {
                        return i;
                    }
                }
            }
            return -1;
        case 9:
            for(int i =0; i<SIZE-1; i++)
            {
                for(int j = 2; j<SIZE; j++)
                {
                    if(field[i][j][4] == false && field[i+1][j][4] == false && field[i][j-1][4] == false && field[i][j-2][4]==false)
                    {
                        return i;
                    }
                }
            }
            return -1;
        case 10:
            for(int i =0; i<SIZE-1; i++)
            {
                for(int j = 0; j<SIZE-2; j++)
                {
                    if(field[i][j][4] == false && field[i+1][j][4] == false && field[i+1][j+1][4] == false && field[i+1][j+2][4] == false)
                    {
                        return i;
                    }
                }
            }
            return -1;
        default: //wrong shape attempted
            printf("\033[91msomething went wrong\n\033[0m");
            break;
    }
}

void renderBoard() //draw the board
{
    clearScreen();
    printf("\n"); //a little spacing
    printf("   ");
    if(SIZE>=10) //a lot of odd formatting stuff
    {
        printf(" "); //extra space for the row shapes
    }
    for(int i = 0; i<SIZE; i++)
    {

        if(DOUBLEINT ==1 && SIZE>10) //if formatted in 02 form...
        {
            printf(" %02d",i); //that's what this is
        }
        else{ //otherwise
            if(i/10 != 0)
            {
                printf(" %d",i); //size is different if it's at least 10
            }
            else
            {
                printf(" %d ",i);
            }
        }
    }

    printf("\n"); //space after the numbers
    for(int i = 0; i<SIZE; i++) //print row by row
    {
        if(DOUBLEINT == 1&&SIZE>10) //again, formatting
        {
            printf(" %02d ",i);
        }
        else{ //more formatting, do you actually read comments? I don't.'
            if(SIZE >=10 && i/10 == 0)
            {
                printf("  %d ",i);
            }
            else
            {
                printf(" %d ",i);
            }
        }
        for(int j = 0; j<SIZE; j++) //now render the line of the field
        {
            if((lastPlacedx==i&&lastPlacedy==j))
            {
                renderShapeRGB(-2,field[i][j][0],field[i][j][1],field[i][j][2],(lastPlacedx==i&&lastPlacedy==j));
            }
            else
            {
                renderShapeRGB(-1,field[i][j][0],field[i][j][1],field[i][j][2],(lastPlacedx==i&&lastPlacedy==j));
            }
        }
        printf("\n");
    }
    setCol(-1); //normal colors now
    printf("\n"); //a bit more spacing
    renderShape(c_block,c_col,true); //draw the current block
    printf("\n");
}
void renderBoardHead() //same as renderBoard except stars are determined by field[foo][foo][3] (the one that determines if star)
{
    clearScreen();
    printf("\n");
    printf("   ");
    if(SIZE>=10)
    {
        printf(" ");
    }
    for(int i = 0; i<SIZE; i++)
    {

        if(DOUBLEINT ==1 && SIZE>10)
        {
            printf(" %02d",i);
        }
        else{
            if(i/10 != 0)
            {
                printf(" %d",i);
            }
            else
            {
                printf(" %d ",i);
            }
        }
    }

    printf("\n");
    for(int i = 0; i<SIZE; i++)
    {
        if(DOUBLEINT == 1&&SIZE>10)
        {
            printf(" %02d ",i);
        }
        else{
            if(SIZE >=10 && i/10 == 0)
            {
                printf("  %d ",i);
            }
            else
            {
                printf(" %d ",i);
            }
        }
        for(int j = 0; j<SIZE; j++)
        {
            if(field[i][j][3]) //here
            {
                renderShapeRGB(-2,field[i][j][0],field[i][j][1],field[i][j][2],(lastPlacedx==i&&lastPlacedy==j));
            }
            else
            {
                renderShapeRGB(-1,field[i][j][0],field[i][j][1],field[i][j][2],(lastPlacedx==i&&lastPlacedy==j));
            }
        }
        printf("\n");
    }
    setCol(-1);
    printf("\n");
    renderShape(c_block,c_col,true);
    printf("\n");
}
int init() //this is to start randomness and clear board
{
    int t = readFile();
    if(t == 1)
    {
        printf("Continue anyway (with defaults)? (Y/n)\n");
        int m = getchar();
        if (m == 'n' || m=='N' || m=='q' || m=='Q')
        {
            return 4;
        }
        if(m != '\n')
            cleanChar();
    }
    if(t == 2)
    {
        printf("\e[91mA Catastrophic settings error observed (EXIT CODE 8)\e[0m\n");
        return 8;
    }
    started = true;
    char randString[32];
    if(sodium_init() <0){ //random library died! Oh no!
        printf("\e[91mA Catastrophic Faliure Occured (EXIT CODE 2)\e[0m\n");
        return 2;
    } //yeah, I know doing this over and over is a little inelegant, leave me alone.
    randombytes_buf(randString, 32);
    lineCount = 0; //clear lines full
    int col = BASECOL;
    int rmod = 0;
    int gmod = 0;
    int bmod = 0;
    for(int i = 0; i<SIZE; i++)
        //set all of hte colors to normal
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
    return 0; //okay cool all set up.
}

void uninit()
{
    free(blocks);
}
