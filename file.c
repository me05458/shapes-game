#include <stdio.h>
#include <stdlib.h>
#include "vars.h"
#include "file.h"
#include "helper.h"
//CHECK is for if something goes really wrong while getting data from the file. (fscanf will return <0)
#define CHECK if(e < 0){printf("Warning: settings file doesn't have enough entries!\n");return 1;}
//this will just get everything until a : is found.
#define READWORD while(c != ':'){ e=fscanf(ptr, "%c",&c); if(VERBOSE) { printf("%c",c); } CHECK; }
//this is the total number of possible blocks, and it's used when determining the max possible amount of user inputted blocks. Don't worry about the define, it's only changed when a new block is added, so it's fiiiine
#define TOTALBLOCKS 11

//fyi file can't use values < 0

int readFile() //so far, we only read the file. Soon, we will also write it.
{
    int bad = 0; //check that everything went okay (returned at the end, used to track errors)
    FILE *ptr = fopen("settings.txt", "r"); //slurp up the file
    if (ptr == NULL) { //oh no file doesn't exist
        ptr = fopen("settings.txt","w"); //make it exist
        fclose(ptr); //all done with that
        ptr = fopen("settings.txt","r"); //okay now slurp up the file
    }

    int e; //this will be our reading success tracker (not like books, like files)

    char c; //just a random character
    int d; //just a random int

    //get the line at the begining of the file.
    while(c != '\n') //there's like a line there, you know?
    {
        fscanf(ptr, "%c",&c);
    }

    //verbose:
    //goes first so that it can influence the others
    READWORD //okay first word...
    e=fscanf(ptr, "%d",&d);
    CHECK;
    e=fscanf(ptr, "%c",&c); //this will (hopefully) get the newline
    //I don't actually know what it does, but the code breaks without it, so...
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
        printf("verbose: true\n"); //obviously we haven't used verbose in the READWORD because it's false by default for obvious reasons
    }


    //reload
    READWORD
    e=fscanf(ptr, "%d",&RELOAD);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(RELOAD != 1 && RELOAD != 0)
    {
        printf("Invalid reload value.\n");
        RELOAD = 1;
        bad = 1; //error! We don't return now so all errors can be revealed at once.
    }
    if(VERBOSE)
        printf(" %d\n",RELOAD); //just print them out.


    //clear
    READWORD
    e=fscanf(ptr, "%d",&CLEAR);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(CLEAR != 1 && CLEAR != 0)
    {
        printf("Invalid clear value.\n");
        CLEAR = 0; //default
        bad =  1;
    }
    if(VERBOSE)
        printf(" %d\n",CLEAR);


    //subdivision
    READWORD
    e=fscanf(ptr, "%d",&SUBDIV);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(SUBDIV == 0)
    { //this means division by 0! Bad!
        printf("Subdivision cannot be 0! Set BIGOFF to 0 instead to remove subdivisions.\n");
        SUBDIV = 3; //do a default instead
        bad =  1; //see? bad
    }
    if(VERBOSE)
        printf(" %d\n",SUBDIV);


    //coordinate type
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


    //number formatting
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


    //wait time
    READWORD
    e=fscanf(ptr, "%d",&WAITTIME);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK; //any wait time will do :)
    if(VERBOSE)
        printf(" %d\n",WAITTIME);


    //animation?
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

    //use_sys? (honestly my most used setting :P )
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


    //blocks:
    ////-----

    READWORD
    int t_blocks[TOTALBLOCKS]; //this is what I need TOTALBLOCKS for
    // ^ this will safely contain all possible blocks unless I really messed things up
    BLOCKNUM = 0; //actual number of blocks (variable)
    e=fscanf(ptr, "%c", &c); //shnork up that space
    CHECK
    e=fscanf(ptr, "%d", &t_blocks[0]); //slurp that block up
    CHECK
    BLOCKNUM = 1; //okay I found one block, I think, don't really remember how this works tbh
    if(t_blocks[0] < 0 || t_blocks[0] >= TOTALBLOCKS)
    {
        printf("\nInvalid block type!\n"); //oh no!
        return 2;
    }
    if(VERBOSE)
    {
        printf("\n%d",t_blocks[0]); //we print blocks as they're added to help with error hunting
    }
    e = fscanf(ptr, "%c",&c);
    CHECK
    while(c != '\n') //until end of line
    {
        if(BLOCKNUM >= TOTALBLOCKS) //they won't fit in the array!!
        {
            printf("\nToo many blocks!\n");
            goto blockending; //just skip the while (can still use other blocks)
        }
        if(c!= ',')
        {
            printf("\nInvalid blocks formatting!\n"); //comma separarated variables!!!
            return 1;
        }
        e=fscanf(ptr, "%d", &t_blocks[BLOCKNUM]); //okay slurp up the block number
        CHECK
        if(t_blocks[BLOCKNUM] < 0 || t_blocks[BLOCKNUM] >= TOTALBLOCKS) //oh no it's a bad block
        {
            printf("\nInvalid block type!\n");
            return 1;
        }
        if(VERBOSE) //just report block
        {
            printf(",%d",t_blocks[BLOCKNUM]);
        }
        BLOCKNUM++; //there are more blocks now
        e = fscanf(ptr, "%c",&c); //get next character (newline or , hopefully)
        CHECK
    }
    blockending: //this is the memory allocating bit
    blocks = (int*)calloc(BLOCKNUM,sizeof(int)); //bunch of memory (new block array, basically)
    if(blocks == nullptr)
    {
        printf("Not enough memory!\n");
        return 2;
    }
    for(int i = 0; i< BLOCKNUM; i++)
    {
        blocks[i] = t_blocks[i];
    }
    if(VERBOSE)
        printf("\n");

    ////-----


    READWORD
    e=fscanf(ptr, "%d",&TEXTCOLR);
    CHECK;
    e=fscanf(ptr,"%c",&c);
    CHECK;
    if(TEXTCOLR < 0 || TEXTCOLR > 255)
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
    if(TEXTCOLG < 0 || TEXTCOLG > 255)
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
    if(TEXTCOLB < 0 || TEXTCOLB > 255)
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

    READWORD
    e=fscanf(ptr, "%d",&d);
    CHECK;
    e=fscanf(ptr, "%c",&c);
    CHECK;
    if(d == 1)
    {
        MODCOL = true;
    }
    else
    {
        MODCOL = false;
    }
    if(VERBOSE)
    {
        if(MODCOL)
        {
            printf(" true\n");
        }
        else
        {
            printf(" false\n");
        }
    }

    //COLORS

    if(VERBOSE)
    {
        printf("colors:\n");
    }
    fclose(ptr);
    ptr = fopen("color.txt", "r");
    if (ptr == NULL) {
        ptr = fopen("color.txt","w");
        fclose(ptr);
        ptr = fopen("color.txt","r");
    }
    //e = fscanf(ptr, "%c",&c);
    //CHECK
    int coltmp;
    int moretmp;
    int m = 0;
    int colarr[100][3]; //you can't have more than 100 colors, I think this is reasonable enough!
    COLNUM = 0;
    e = fscanf(ptr, "%d",&coltmp);
    CHECK

    while(coltmp!= 298)
    {
        if(coltmp < 0 || coltmp > 255)
        {
            printf("Invalid color r value\n");
            bad = 1;
            coltmp = 0;
        }
        colarr[COLNUM][0] = coltmp;
        e = fscanf(ptr, "%c",&c);
        if(e <0)
        {
            printf("nownownow");
            goto end;
        }
        if(c != ',')
        {
            printf("Invalid color formatting!\n");
            return 2;
        }
        e = fscanf(ptr, "%d",&coltmp);
        CHECK
        if(coltmp < 0 || coltmp > 255)
        {
            printf("Invalid color g value\n");
            bad = 1;
            coltmp = 0;
        }
        colarr[COLNUM][1] = coltmp;
        e = fscanf(ptr, "%c",&c);
        CHECK
        if(c != ',')
        {
            printf("Invalid color formatting!\n");
            return 2;
        }
        e = fscanf(ptr, "%d",&coltmp);
        CHECK
        if(coltmp < 0 || coltmp > 255)
        {
            printf("Invalid color b value\n");
            bad = 1;
            coltmp = 0;
        }
        colarr[COLNUM][2] = coltmp;
        e = fscanf(ptr, "%c",&c);
        CHECK
        if(c != '\n')
        {
            printf("Invalid color formatting!\n");
            return 2;
        }
        COLNUM++;
        e = fscanf(ptr, "%d",&coltmp);
        if(e<0)
        {
            goto end;
        }
    }
    end:
    colors = (int*)calloc(COLNUM*3,sizeof(int));
    if(colors == nullptr)
    {
        printf("Not enough memory!\n");
        return 2;
    }
    for(int i = 0; i<COLNUM; i++)
    {
        if(VERBOSE)
            printf("%d: ",i);
        for(int j = 0; j<3; j++)
        {
            colors[i*3+j] = colarr[i][j];
            if(VERBOSE)
            {
                printf("%d ",colarr[i][j]);
            }
        }
        if(VERBOSE)
            printf("\n");
    }
    COLNUM--;





    fclose(ptr);
    return bad;
}
