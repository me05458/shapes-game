#include <stdio.h>
#include "vars.h"
#define CHECK if(e < 0){printf("Warning: settings file doesn't have enough entries!\n");return 1;}
#define READWORD while(c != ':'){ e=fscanf(ptr, "%c",&c); if(VERBOSE) { printf("%c",c); } CHECK; }

int readFile()
{
    FILE *ptr = fopen("settings.txt", "r");
    if (ptr == NULL) {
        ptr = fopen("settings.txt","w");
        fclose(ptr);
        ptr = fopen("settings.txt","r");
    }

    int e;

    char c;
    int d;

    //get the line at the begining of the file.
    while(c != '\n')
    {
        fscanf(ptr, "%c",&c);
    }

    READWORD
    e=fscanf(ptr, "%d",&d);
    CHECK;
    e=fscanf(ptr, "%c",&c);
    CHECK;
    if(d == 1)
    {
        VERBOSE = true;
    }
    else
    {
        VERBOSE = false;
    }
    if(VERBOSE)
    {
        printf("verbose: true\n");
    }


    READWORD
    e=fscanf(ptr, "%d",&RELOAD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",RELOAD);


    READWORD
    e=fscanf(ptr, "%d",&CLEAR);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",CLEAR);


    READWORD
    e=fscanf(ptr, "%d",&SUBDIV);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",SUBDIV);


    READWORD
    e=fscanf(ptr, "%d",&NORM_COORD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",NORM_COORD);


    READWORD
    e=fscanf(ptr, "%d",&DOUBLEINT);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",DOUBLEINT);


    READWORD
    e=fscanf(ptr, "%d",&WAITTIME);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",WAITTIME);


    READWORD
    e=fscanf(ptr, "%d",&ANIMATE);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",ANIMATE);

    READWORD
    e=fscanf(ptr, "%d",&USE_SYS);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",USE_SYS);



    READWORD
    e=fscanf(ptr, "%d",&SMALLOFF);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",SMALLOFF);


    READWORD
    e=fscanf(ptr, "%d",&BIGOFF);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",BIGOFF);


    READWORD
    e=fscanf(ptr, "%d",&BASECOL);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",BASECOL);


    READWORD
    e=fscanf(ptr, "%d",&RMOD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",RMOD);


    READWORD
    e=fscanf(ptr, "%d",&GMOD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",GMOD);


    READWORD
    e=fscanf(ptr, "%d",&BMOD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(VERBOSE)
        printf(" %d\n",BMOD);


    READWORD
    e=fscanf(ptr, "%d",&d);
    CHECK;
    e=fscanf(ptr, "%c",&c);
    CHECK;
    if(d == 1)
    {
        MODBLOCK = true;
    }
    else
    {
        MODBLOCK = false;
    }
    if(VERBOSE)
    {
        if(MODBLOCK)
        {
            printf(" true\n");
        }
        else
        {
            printf(" false\n");
        }
    }




    fclose(ptr);
    return 0;
}
