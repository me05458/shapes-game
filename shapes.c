#include <stdio.h>
#include "settings.h"

void setCol(int color) //your friendly formatting function
{
    switch(color){
        case -1: //reset
            printf("\033[0m");
            break;
        case -2: //reset with new line
            printf("\033[0m\n");
            break;
        case 0:
            printf("\033[48;2;%d;%d;%dm",ZERO);
            break;
        case 1:
            printf("\033[48;2;%d;%d;%dm",ONE);
            break;
        case 2:
            printf("\033[48;2;%d;%d;%dm",TWO);
            break;
        case 3:
            printf("\033[48;2;%d;%d;%dm",THREE);
            break;
        case 4:
            printf("\033[48;2;%d;%d;%dm",FOUR);
            break;
        case 5:
            printf("\033[48;2;%d;%d;%dm",FIVE);
            break;
        case 6:
            printf("\033[48;2;%d;%d;%dm",SIX);
            break;
        case 7:
            printf("\033[48;2;%d;%d;%dm",SEVEN);
            break;
        case 8:
            printf("\033[48;2;%d;%d;%dm",EIGHT);
            break;
        case 9:
            printf("\033[48;2;%d;%d;%dm",NINE);
            break;
        default:
            printf("\033[48;2;%d;%d;%dm",BACKUP);
    }
}

void renderShape(int type, int color)
{
    setCol(color);
    switch (type) {
        case 0:
            printf("  ");
            setCol(-2);
            break;
        case 1:
            printf("      ");
            setCol(-2);
            break;
        case 2:
            for(int i = 0; i<3; i++)
            {
                setCol(color);
                printf("  ");
                setCol(-2);
            }
            break;
        default:
            printf("SOMETHING WENT WRONG OH NO");
    }
}
