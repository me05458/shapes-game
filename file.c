#include <stdio.h>
extern int RELOAD;
extern int CLEAR;
extern int SUBDIV;
extern int NORM_COORD;
extern int DOUBLEINT;
extern int WAITTIME;
extern int ANIMATE;
extern int USE_SYS;
extern int SMALLOFF;
extern int BIGOFF;
extern int BASECOL;
extern int RMOD;
extern int GMOD;
extern int BMOD;
extern int MODBLOCK;
#define CHECK if(e < 0){printf("Warning: settings file does not contain all needed settings!\n");return 0;}
int readFile()
{
    FILE *ptr = fopen("settings.txt", "r");
    if (ptr == NULL) {
        ptr = fopen("settings.txt","w");
        fclose(ptr);
        ptr = fopen("settings.txt","r");
    }
    char occurence;
    int day;
    int month;
    int year;
    int e;

    e  = fscanf(ptr, "%d",&RELOAD);
    CHECK
    e = fscanf(ptr, "%d",&CLEAR);
    CHECK
    e = fscanf(ptr, "%d",&SUBDIV);
    CHECK
    e = fscanf(ptr, "%d",&NORM_COORD);
    CHECK
    e = fscanf(ptr, "%d",&DOUBLEINT);
    CHECK
    e = fscanf(ptr, "%d",&WAITTIME);
    CHECK
    e = fscanf(ptr, "%d",&ANIMATE);
    CHECK
    e = fscanf(ptr, "%d",&USE_SYS);
    CHECK
    e = fscanf(ptr, "%d",&SMALLOFF);
    CHECK
    e = fscanf(ptr, "%d",&BIGOFF);
    CHECK
    e = fscanf(ptr, "%d",&BASECOL);
    CHECK
    e = fscanf(ptr, "%d",&RMOD);
    CHECK
    e = fscanf(ptr, "%d",&GMOD);
    CHECK
    e = fscanf(ptr, "%d",&BMOD);
    CHECK
    e = fscanf(ptr, "%d",&MODBLOCK);
    CHECK
    fclose(ptr);
    return 0;
}
