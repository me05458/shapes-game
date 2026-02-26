#include "helper_big.h"
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


//haha this function is back!
int charEater(char c)
{
    int result =  c - '0'; //the numbers are consecutive so subtract 0
    if(result > 9||result<0) //it's a letter/other character
        return -1;
    return result; //I <3 this function
}

void waitMS(int ms) //this is such a funny way of sleeping this is what I shall do.
{
    struct timespec ts; //idk time stuff, too lazy to write comments
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, nullptr);
}
