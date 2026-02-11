#include <stdio.h>
#include <stdlib.h>
#include "vars.h"
#include "helper.h"
#define CHECK if(e < 0){printf("Warning: settings file doesn't have enough entries!\n");return 1;}
#define READWORD while(c != ':'){ e=fscanf(ptr, "%c",&c); if(VERBOSE) { printf("%c",c); } CHECK; }
#define TOTALBLOCKS 10

int readFile()
{
    int bad = 0;
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
    if(RELOAD != 1 && RELOAD != 0)
    {
        printf("Invalid reload value.\n");
        RELOAD = 1;
        bad = 1;
    }
    if(VERBOSE)
        printf(" %d\n",RELOAD);


    READWORD
    e=fscanf(ptr, "%d",&CLEAR);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(CLEAR != 1 && CLEAR != 0)
    {
        printf("Invalid clear value.\n");
        CLEAR = 0;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",CLEAR);


    READWORD
    e=fscanf(ptr, "%d",&SUBDIV);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(SUBDIV == 0)
    {
        printf("Subdivision cannot be 0! Set BIGOFF to 0 instead to remove subdivisions.\n");
        SUBDIV = 3;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",SUBDIV);


    READWORD
    e=fscanf(ptr, "%d",&NORM_COORD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(NORM_COORD != 1 && NORM_COORD != 0)
    {
        printf("Invalid coordinates type value.\n");
        NORM_COORD = 1;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",NORM_COORD);


    READWORD
    e=fscanf(ptr, "%d",&DOUBLEINT);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(DOUBLEINT != 1 && DOUBLEINT != 0)
    {
        printf("Invalid number formatting value.\n");
        DOUBLEINT = 1;
        bad =  1;
    }
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
    if(ANIMATE != 1 && ANIMATE != 0)
    {
        printf("Invalid animate value.\n");
        ANIMATE = 0;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",ANIMATE);

    READWORD
    e=fscanf(ptr, "%d",&USE_SYS);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(USE_SYS != 1 && USE_SYS != 0)
    {
        printf("Invalid use system value.\n");
        USE_SYS = 1;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",USE_SYS);

    READWORD
    int t_blocks[TOTALBLOCKS];
    BLOCKNUM = 0;
    e=fscanf(ptr, "%c", &c);
    CHECK
    e = fscanf(ptr, "%c",&c);
    CHECK
    int q = charEater(c);
    if(q < 0)
    {
        printf("Invalid block sequence.\n");
        return 2;
    }
    else
    {
        t_blocks[BLOCKNUM] = q;
        BLOCKNUM++;
    }
    e = fscanf(ptr, "%c",&c);
    CHECK
    while (c != '\n')
    {
        if(c != ',')
        {
            printf("Invalid blocks formatting!\n");
            return 2;
        }
        e=fscanf(ptr, "%c", &c);
        CHECK
        int q = charEater(c);
        if(q < 0)
        {
            printf("Invalid block sequence.\n");
            return 2;
        }
        else
        {

            t_blocks[BLOCKNUM] = q;
            BLOCKNUM++;
        }
        e = fscanf(ptr, "%c", &c);
        CHECK
    }
    blocks = (int*)calloc(BLOCKNUM,sizeof(int));
    if(blocks == nullptr)
    {
        printf("Not enough memory!\n");
        return 2;
    }
    for(int i = 0; i< BLOCKNUM; i++)
    {
        blocks[i] = t_blocks[i];
        if(VERBOSE)
            printf("%d,",blocks[i]);
    }
    if(VERBOSE)
        printf("\n");


    READWORD
    e=fscanf(ptr, "%d",&TEXTCOLR);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(TEXTCOLR < 0 || TEXTCOLR > 225)
    {
        printf("Invalid text color red value.\n");
        TEXTCOLR = 0;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",TEXTCOLR);


    READWORD
    e=fscanf(ptr, "%d",&TEXTCOLG);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(TEXTCOLG < 0 || TEXTCOLG > 225)
    {
        printf("Invalid text color green value.\n");
        TEXTCOLG = 0;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",TEXTCOLG);


    READWORD
    e=fscanf(ptr, "%d",&TEXTCOLB);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(TEXTCOLB < 0 || TEXTCOLB > 225)
    {
        printf("Invalid text color blue value.\n");
        TEXTCOLB = 0;
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",TEXTCOLB);



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
    return bad;
}
