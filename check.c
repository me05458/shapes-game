#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "settings.h"
#include "helper.h"
#include <stdbool.h>
//this helps us see if the settings are good.
//these things are described at some other point (in helper?)
extern int field[SIZE][SIZE][5]; //field
extern int blocks[BLOCKNUM];
extern int colors[COLNUM+1][3];
extern int lastPlacedx;
extern int lastPlacedy;
//this makes the color output stuff more
bool verbose = false; //this should start as FALSE
void printCols() //this just runs through all the colors
{
    printf("colors: \n");
    if(MODBLOCK) //if the colors are modified...
    {
        if(verbose) //shows what they are for developers
        {
            printf("color value   color MOD   SMALLOFF   BIGOFF   BOTHOFF\n");
        }
        printf("DEFAULT: "); //the first color is default.
        if(verbose)
        {
            printf("        ");
        }
        //this is just the first color in all of its combinations.
        renderShape(-1,0,true);
        renderShapeRGB(-1,colors[0][0]+RMOD, colors[0][1]+GMOD, colors[0][2]+BMOD, true);
        renderShapeRGB(-1,colors[0][0]+RMOD-SMALLOFF, colors[0][1]+GMOD-SMALLOFF, colors[0][2]+BMOD-SMALLOFF, true);
        renderShapeRGB(-1,colors[0][0]+RMOD-BIGOFF, colors[0][1]+GMOD-BIGOFF, colors[0][2]+BMOD-BIGOFF, true);
        renderShapeRGB(blocks[0],colors[0][0]+RMOD-SMALLOFF-BIGOFF, colors[0][1]+GMOD-SMALLOFF-BIGOFF, colors[0][2]+BMOD-SMALLOFF-BIGOFF, true);
        for(int i = 1; i<COLNUM;i++) //now run through all of them
        {
            printf("%d:       ",i);
            if(verbose)
            {
                printf("        "); //accomodates for extra spacing.
            }
            renderShape(-1,i,true);
            renderShapeRGB(-1,colors[i][0]+RMOD, colors[i][1]+GMOD, colors[i][2]+BMOD, true);
            renderShapeRGB(-1,colors[i][0]+RMOD-SMALLOFF, colors[i][1]+GMOD-SMALLOFF, colors[i][2]+BMOD-SMALLOFF, true);
            renderShapeRGB(-1,colors[i][0]+RMOD-BIGOFF, colors[i][1]+GMOD-BIGOFF, colors[i][2]+BMOD-BIGOFF, true);
            renderShapeRGB(blocks[0],colors[i][0]+RMOD-SMALLOFF-BIGOFF, colors[i][1]+GMOD-SMALLOFF-BIGOFF, colors[i][2]+BMOD-SMALLOFF-BIGOFF, true);
        }
    }
    else //otherwise still show 4 types but no RMOD etc
    {
        if(verbose) //exactly what it looks like
        {
            printf("color value    color   SMALLOFF   BIGOFF   BOTHOFF\n");
        }
        printf("DEFAULT: ");
        if(verbose)
        {
            printf("        ");
        }
        renderShape(-1,0,true);
        renderShapeRGB(-1,colors[0][0]-SMALLOFF, colors[0][1]-SMALLOFF, colors[0][2]-SMALLOFF, true);
        renderShapeRGB(-1,colors[0][0]-BIGOFF, colors[0][1]-BIGOFF, colors[0][2]-BIGOFF, true);
        renderShapeRGB(blocks[0],colors[0][0]-SMALLOFF-BIGOFF, colors[0][1]-SMALLOFF-BIGOFF, colors[0][2]-SMALLOFF-BIGOFF, true);
        for(int i = 1; i<COLNUM+1;i++) //through all the colors
        {
            printf("%d:       ",i);
            if(verbose)
            {
                printf("        ");
            }
            renderShape(-1,i,true);
            renderShapeRGB(-1,colors[i][0]-SMALLOFF, colors[i][1]-SMALLOFF, colors[i][2]-SMALLOFF, true);
            renderShapeRGB(-1,colors[i][0]-BIGOFF, colors[i][1]-BIGOFF, colors[i][2]-BIGOFF, true);
            renderShapeRGB(blocks[0],colors[i][0]-SMALLOFF-BIGOFF, colors[i][1]-SMALLOFF-BIGOFF, colors[i][2]-SMALLOFF-BIGOFF, true);
        }
    }
}

void printBlocks() //this shows each type of shape
{
    for(int i = 0; i<BLOCKNUM-1; i++) //run through all shapes
    {
        //note that the values to print/render are not i but blocks[i]
        //that's how the numbers work
        printf("%d:\n",blocks[i]);
        renderShape(blocks[i],i%10,-1);
        printf("\n");
    }
    printf("%d:\n",blocks[BLOCKNUM-1]); //this is the last one.
    renderShape(blocks[BLOCKNUM-1],(BLOCKNUM-1)%10,-1);

}

void diagnoseColor() //this is used to show which colors are bad
{
    bool fieldCol = BASECOL+RMOD-SMALLOFF-BIGOFF<0||BASECOL+BMOD-SMALLOFF-BIGOFF<0||BASECOL+GMOD-SMALLOFF-BIGOFF<0; //something's wrong with the field
    //just report for each r,g,b of basecol.
    if(BASECOL+RMOD-SMALLOFF-BIGOFF<0)
    {
        printf("BASECOL \033[91mred\033[0m too \033[95msmall\033[0m\n");
    }
    if(BASECOL+BMOD-SMALLOFF-BIGOFF<0)
    {
        printf("BASECOL \033[95mblue\033[0m too \033[95msmall\033[0m\n");
    }
    if(BASECOL+GMOD-SMALLOFF-BIGOFF<0)
    {
        printf("BASECOL \033[92mgreen\033[0m too \033[95msmall\033[0m\n");
    }
    bool fieldCol2 = BASECOL+RMOD>255||BASECOL+BMOD>255||BASECOL+GMOD>255;
    //this is if the field colors are too big.
    if(BASECOL+RMOD>255)
    {
        printf("BASECOL \033[91mred\033[0m too \033[96mbig\033[0m\n");
    }
    if(BASECOL+BMOD>255)
    {
        printf("BASECOL \033[95mblue\033[0m too \033[96mbig\033[0m\n");
    }
    if(BASECOL+GMOD>255)
    {
        printf("BASECOL \033[92mgreen\033[0m too \033[96mbig\033[0m\n");
    }
    bool otherCol = false;
    if(MODBLOCK) //only matters if we mod the blocks.
    {
        for(int i = 0; i<COLNUM+1; i++) //check each color, r,g,b
        {
            if(colors[i][0]+RMOD-SMALLOFF-BIGOFF<0)
            {
                printf("color %d \033[91mred\033[0m too \033[95msmall\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][1]+GMOD-SMALLOFF-BIGOFF<0)
            {
                printf("color %d \033[92mgreen\033[0m too \033[95msmall\033[0m\b\n",i);
                otherCol = true;
            }
            if(colors[i][2]+BMOD-SMALLOFF-BIGOFF<0)
            {
                printf("color %d \033[95mblue\033[0m too \033[95msmall\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][0]+RMOD>255)
            {
                printf("color %d \033[91mred\033[0m too \033[96mbig\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][1]+GMOD>255)
            {
                printf("color %d \033[92mgreen\033[0m too \033[96mbig\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][2]+BMOD>255)
            {
                printf("color %d \033[94mblue\033[0m too \033[96mbig\033[0m\n",i);
                otherCol = true;
            }
        }
    }
    else //still check with the OFFs, but not MODs
    {
        for(int i = 0; i<COLNUM+1; i++)
        {
            if(colors[i][0]-SMALLOFF-BIGOFF<0)
            {
                printf("color %d \033[91mred\033[0m too \033[95msmall\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][1]-SMALLOFF-BIGOFF<0)
            {
                printf("color %d \033[92mgreen\033[0m too \033[95msmall\033[0m\b",i);
                otherCol = true;
            }
            if(colors[i][2]-SMALLOFF-BIGOFF<0)
            {
                printf("color %d \033[95mblue\033[0m too \033[95msmall\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][0]>255)
            {
                printf("color %d \033[91mred\033[0m too \033[96mbig\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][1]>255)
            {
                printf("color %d \033[92mgreen\033[0m too \033[96mbig\033[0m\n",i);
                otherCol = true;
            }
            if(colors[i][2]>255)
            {
                printf("color %d \033[94mblue\033[0m too \033[96mbig\033[0m\n",i);
                otherCol = true;
            }
        }
    }
    printf("MODBLOCK: %d\n", MODBLOCK); //show modblock
    if(!otherCol && !fieldCol && !fieldCol2) //if none of the above...
    {
        printf("\033[92mAll good!\033[0m\n"); //don't just be blank
    }
}

int main() //we're gonna run through the dialogue here
{
    bool firstRun = true; //we need this to show help menu, etc.
    char input; //this will be our user input
    clearScreen(); //see helper
    printf("0. Help\n"
    "1. Diagnose color issues\n"
    "2. View set colors\n"
    "3. View set blocks\n"
    "4. View board\n"
    "5. Developer settings (advanced)\n"
    "Q. quit\n"
    "Choose action:\n"
    ); // ^ help menu
    input = getchar();

    while(true) //FOREVER
    {
        start: //it's very goto based, as always.
        if(input != '\n')
        {
            cleanChar();
        }
        switch(input){

            case '1': //these gusy are what they look like
                clearScreen();
                diagnoseColor();
                break;
            case '2':
                clearScreen();
                printCols();
                break;
            case '3':
                clearScreen();
                printBlocks();
                break;
            case '4':
                clearScreen();
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
                renderBoard();
                //cleanChar();
                break;
            case '5':
                clearScreen();
                if(firstRun) //only show this stuff the first time
                {
                    help:
                    clearScreen();
                    printf("Developer settings:\n"
                        "0. Help\n"
                        "1. Verbose mode\n"
                        "2. View value of clear screen\n"
                        "E. Escape developer settings\n"
                        "Q. Quit settings application\n");
                    firstRun = false;
                }
                normal: // for non-help
                printf("Choose developer action:\n");
                char tmp = getchar();
                if(tmp == '\n'||tmp=='0') //new line always just causes help menu
                {
                    goto help;
                }
                else if(tmp == '1')
                {
                    cleanChar();
                    clearScreen();
                    if(verbose)
                    {
                        printf("Verbose turned OFF\n");
                        verbose = false;
                    }
                    else
                    {
                        printf("Verbose turned ON\n");
                        verbose = true;
                    }
                }
                else if(tmp == '2')
                {
                    cleanChar();
                    clearScreen();
                    if(USE_SYS == 1)
                    {
                        printf("USE_SYS = 1 and game will clear screen.\n");
                    }
                    else
                    {
                        printf("USE_SYS = %d and game will NOT clear screen.\n",USE_SYS);
                    }
                }
                else if(tmp == 'Q' || tmp == 'q')
                { //if 'q' is entered here, leave instantly
                    cleanChar();
                    return 0;
                }
                else if(tmp == 'E' || tmp == 'e')
                {
                    //if 'e' only leave developer settings.
                    break;
                }
                else
                {
                    cleanChar();
                    goto help; //as usual, run help thing
                }
                goto normal;
                break;
            case 'Q': //these two cases go together.
            case 'q':
                return 0; //exit
            case '\n': //these three cases go together
            case '0':
            default: //default = help
                clearScreen();
                printf("0. Help\n"
                "1. Diagnose color issues\n"
                "2. View set colors\n"
                "3. View set blocks\n"
                "4. View board\n"
                "5. Developer settings (advanced)\n"
                "Q. quit\n"

                );
                printf("Choose action:\n");
                input = getchar();
                goto start;
                break;


        }
        printf("Choose action:\n"); //get next input
        input = getchar();
    }
    //shouldn't get here but just in case
    return 0;
}
