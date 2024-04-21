#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define WDT 100
#define HYT 40
 

struct Board{
    int dash_loc;
};


struct Game {
    struct Board board;
};


// function of Board.c
int DrawBoard(struct Game G);