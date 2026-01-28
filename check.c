#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include "settings.h"
#include "helper.h"
#include <stdbool.h>
extern int field[SIZE][SIZE][5]; //field
extern int blocks[BLOCKNUM];
extern int colors[COLNUM+1][3];
extern int lastPlacedx;
extern int lastPlacedy;
bool verbose = true;
void printCols()
{
    printf("colors: \n");
    if(MODBLOCK)
    {
        if(verbose)
        {
            printf("color value   color MOD   SMALLOFF   BIGOFF   BOTHOFF\n");
        }
        printf("DEFAULT: ");
        if(verbose)
        {
            printf("        ");
        }
        renderShape(-1,0,true);
        renderShapeRGB(-1,colors[0][0]+RMOD, colors[0][1]+GMOD, colors[0][2]+BMOD, true);
        renderShapeRGB(-1,colors[0][0]+RMOD-SMALLOFF, colors[0][1]+GMOD-SMALLOFF, colors[0][2]+BMOD-SMALLOFF, true);
        renderShapeRGB(-1,colors[0][0]+RMOD-BIGOFF, colors[0][1]+GMOD-BIGOFF, colors[0][2]+BMOD-BIGOFF, true);
        renderShapeRGB(blocks[0],colors[0][0]+RMOD-SMALLOFF-BIGOFF, colors[0][1]+GMOD-SMALLOFF-BIGOFF, colors[0][2]+BMOD-SMALLOFF-BIGOFF, true);
        for(int i = 1; i<COLNUM;i++)
        {
            printf("%d:       ",i);
            if(verbose)
            {
                printf("        ");
            }
            renderShape(-1,i,true);
            renderShapeRGB(-1,colors[i][0]+RMOD, colors[i][1]+GMOD, colors[i][2]+BMOD, true);
            renderShapeRGB(-1,colors[i][0]+RMOD-SMALLOFF, colors[i][1]+GMOD-SMALLOFF, colors[i][2]+BMOD-SMALLOFF, true);
            renderShapeRGB(-1,colors[i][0]+RMOD-BIGOFF, colors[i][1]+GMOD-BIGOFF, colors[i][2]+BMOD-BIGOFF, true);
            renderShapeRGB(blocks[0],colors[i][0]+RMOD-SMALLOFF-BIGOFF, colors[i][1]+GMOD-SMALLOFF-BIGOFF, colors[i][2]+BMOD-SMALLOFF-BIGOFF, true);
        }
    }
    else
    {
        if(verbose)
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
        for(int i = 1; i<COLNUM+1;i++)
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

void diagnoseColor()
{
    bool fieldCol = BASECOL+RMOD-SMALLOFF-BIGOFF<0||BASECOL+BMOD-SMALLOFF-BIGOFF<0||BASECOL+GMOD-SMALLOFF-BIGOFF<0;
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
    if(MODBLOCK)
    {
    for(int i = 0; i<COLNUM+1; i++)
    {
        if(colors[i][0]+RMOD-SMALLOFF-BIGOFF<0)
        {
            printf("color %d \033[91mred\033[0m too \033[95msmall\033[0m\n",i);
            otherCol = true;
        }
        if(colors[i][1]+GMOD-SMALLOFF-BIGOFF<0)
        {
            printf("color %d \033[92mgreen\033[0m too \033[95msmall\033[0m\b",i);
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
    else
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
    printf("MODBLOCK: %d\n", MODBLOCK);
    if(!otherCol && !fieldCol && !fieldCol2)
    {
        printf("\033[92mAll good!\033[0m\n");
    }
}

int main()
{
    bool firstRun = true;
    char input;
    clearScreen();
    printf("0. Help\n"
    "1. Diagnose color issues\n"
    "2. View set colors\n"
    "3. View set blocks\n"
    "4. View board\n"
    "5. Developer settings (advanced)\n"
    "Q. quit\n"
    "Choose action:\n"
    );
    input = getchar();

    while(true)
    {
        start:
        if(input != '\n')
        {
            cleanChar();
        }
        switch(input){

            case '1':
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
                renderBoard();
                break;
            case '5':
                clearScreen();
                if(firstRun)
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
                normal:
                printf("Choose developer action:\n");
                char tmp = getchar();
                if(tmp == '\n'||tmp=='0')
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
                {
                    cleanChar();
                    return 0;
                }
                else if(tmp == 'E' || tmp == 'e')
                {
                    break;
                }
                else
                {
                    cleanChar();
                    goto help;
                }
                goto normal;
                break;
            case 'Q':
            case 'q':
                return 0;
            case '\n':
            case '0':
            default:
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
        printf("Choose action:\n");
        input = getchar();
    }
    printCols();
    printf("----------------------------\n----------------------------\n");
    printBlocks();
    printf("----------------------------\n----------------------------\n");
    renderBoard();
    return 0;
}
