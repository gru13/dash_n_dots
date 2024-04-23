#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<curses.h>

#define WDT 190
#define HYT 55
#define MAX_LINE 12000

#define DASH 220 // ▄
#define BLOK 219 // █
#define DOT 254 // ■

#define VER_LINE 186 // ║
#define HOR_LINE 205 // ═
#define TL_COR 201 // ╔
#define BL_COR 200 // ╚
#define TR_COR 187 // ╗
#define BR_COR 186 // ╝
#define SPC 32 // ' '

// #define MV_LFT '←' 
// #define MV_RYT '→'
// #define MV_UPP '↑'
// #define MV_DWN '↓'
// #define CLOSE '\e'

#define MV_LFT 'L' 
#define MV_RYT 'R'
#define MV_UPP 'U'
#define MV_DWN 'D'
#define CLOSE 'X'
#define CONT 'c'






struct Game {
    WINDOW* board;
    int GameState;
};


// function of Board.c
void initBoard( );
void printBoard(char Board[HYT][WDT]);
char keyIsPressed();

// function in main
int main();
void updateGamestate(int* curState);
