#ifndef HELPER1_H
#define HELPER1_H
#include <stdbool.h>
#include <stdio.h>
#include "vars.h"
#include <time.h>
#include <stdlib.h>

//reset the character input area
//I finally figured out how it works!!
void cleanChar(); //cleans surplus stdin input
void clearScreen(); //just clears everything off the terminal.
int charEater(char c); //turns chars to ints
void waitMS(int ms); //wait
#endif
