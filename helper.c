#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
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
    printf("clear\n");
    printf("%d\n",USE_SYS);
}
void init()
{
    //nothing here
}
