#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>//using pdcurses
#include <windows.h>
#include <time.h>
#include <pthread.h>

// #define REFRESH_RATE 4000 // this in milli-second
#define SPC 32	 // ' '
#define DASH 219 // █
#define BALL 79	 // O
// #define BALL 254	 // ■
// #define DOT 254	 // ■
// #define DASH  220 // ▄
// #define BLOK 219 // █

#define VER_LINE 186 // ║
#define HOR_LINE 205 // ═
#define TL_COR 201	 // ╔
#define BL_COR 200	 // ╚
#define TR_COR 187	 // ╗
#define BR_COR 188	 // ╝
#define SPC 32		 // ' '

#define MV_LFT 'L'
#define MV_RYT 'R'
#define MV_UPP 'U'
#define MV_DWN 'D'
#define CONT 'c'
#define CLOSE 'x'


typedef struct game{
	WINDOW *win;
	int HYT;
	int WDT;
	int DashLoc;
	int DashSize;
	int ballX;
	int ballY;
	int ballDir;
	byte Speed; 
} Game;

DWORD SPEEDS[] = {1,5,35,85};
int nofSdp = sizeof(SPEEDS)/sizeof(DWORD);
char temp[20];


int keyIsPressed();
int initGame(Game* g);
int initWindow(Game *g);
int changeSpeed(Game* G,int ctrl);

int initDash(Game* g);
int MoveDash(Game* g);

int initBall(Game* g);
int moveBall(Game* g);

int main(){
	Game G;
	initGame(&G);
	char ctrl = CONT;
	while(ctrl != CLOSE){
		ctrl = keyIsPressed();

		// location checking purpose
		sprintf(temp, "%c|%3d|%3d",(char)ctrl,G.DashLoc,SPEEDS[G.Speed]);
		mvwprintw(G.win,1,1,temp);
		wrefresh(G.win);
		moveBall(&G);	
		if(ctrl == CONT){
			continue;
		}else if(ctrl == MV_LFT){
			G.DashLoc -= 1;
			MoveDash(&G);
		}else if(ctrl == MV_RYT){
			G.DashLoc += 1;
			MoveDash(&G);
		}else if(ctrl == MV_UPP || ctrl == MV_DWN){
			changeSpeed(&G,ctrl);
		}
		ctrl == CONT;
		Sleep(SPEEDS[G.Speed]);
	}
	endwin();
	return 0;
}


int moveBall(Game* g){
	sprintf(temp,"%c",(char)SPC);
	mvwprintw(g->win,g->ballY,g->ballX,temp);
	// g->ballX += rand()%3 - 1;
	// g->ballY += rand()%3 - 1;
	g->ballX -=  1;
	g->ballY -=  1;
	if(g->ballX >= g->WDT-1){
		g->ballX = g->WDT-2;
	}
	if(g->ballX <= 1){
		g->ballX = 1;
	}
	if(g->ballY >= g->HYT-2){
		g->ballY = g->HYT-3;
	}
	if(g->ballY <= 1){
		g->ballY = 1;
	}
	sprintf(temp, "%c",BALL);
	mvwprintw(g->win,g->ballY,g->ballX,temp);
	Sleep(50);
	return 0;
}

int initGame(Game* g){
	system("cls");
	g->Speed = 0;
	int maxx,maxy;
	g->win = initscr();
	if (g->win == NULL){
		printf("Error in creating Screen\n");
		return 1;
	}
	// g->WDT = 176 ;// 176
	// g->HYT = 55 ;// 55
	// g->win = newwin(g->HYT,g->WDT,0,0);
	g->WDT = getmaxx(g->win);
	g->HYT = getmaxy(g->win);
	initWindow(g);
	initDash(g);
	initBall(g);
	curs_set(0);
	wrefresh(g->win);
	return 0;
}

int initWindow(Game *g){
	for(int i = 0;i<g->HYT;i++){
		for(int j =0 ; j<g->WDT;j++){
			if(i == 0 || i == g->HYT-1){
				sprintf(temp, "%c",HOR_LINE);
				mvwprintw(g->win,i,j,temp);
			}
			else if(j == 0 || j == g->WDT-1){
				sprintf(temp, "%c",VER_LINE);
				mvwprintw(g->win,i,j,temp);
			}
		}
	}

	// corners
	sprintf(temp, "%c",TL_COR);
	mvwprintw(g->win,0,0,temp);
	sprintf(temp, "%c",TR_COR);
	mvwprintw(g->win,0,g->WDT-1,temp);
	sprintf(temp, "%c",BL_COR);
	mvwprintw(g->win,g->HYT-1,0,temp);
	sprintf(temp, "%c",BR_COR);
	mvwprintw(g->win,g->HYT-1,g->WDT-1,temp);

	wrefresh(g->win);

}


int initDash(Game* g){
	g->DashSize = 10;
	g->DashLoc = g->WDT/2;
	MoveDash(g);
	wrefresh(g->win);
	return 0;
}

int MoveDash(Game* g){
	if(g->DashLoc - g->DashSize < 1){
		g->DashLoc = 1 + g->DashSize ;
		return 0;
	}
	if(g->DashLoc + g->DashSize >= g->WDT){
		g->DashLoc = g->WDT - 2 - g->DashSize;
		return 0;
	}
	for(int i = 1;i<g->WDT-1;i++){
		sprintf(temp, "%c",SPC);
		mvwprintw(g->win,g->HYT-2,i,temp);
	}
	for(int i = g->DashLoc-g->DashSize; i<g->DashLoc+g->DashSize;i++){
		sprintf(temp, "%c",DASH);
		mvwprintw(g->win,g->HYT-2,i,temp);
	}
	wrefresh(g->win);
	return 0;
}

int keyIsPressed(){
	if (GetAsyncKeyState(VK_LEFT) & 0x8000){
		return MV_LFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
		return MV_RYT;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000){
		return MV_UPP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000){
		return MV_DWN;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000){
		return CLOSE;
	}
	return CONT;
}

int changeSpeed(Game* G,int ctrl){
	if(ctrl == MV_UPP){
		G->Speed += 1;
		if(G->Speed >= nofSdp){
			G->Speed = nofSdp-1;
		}
	}
	if(ctrl == MV_DWN){
		G->Speed -= 1;
		if(G->Speed <= 0){
			G->Speed = 0;
		}
		
	}
	Sleep(100);
	return 0;
}

int initBall(Game* g){
	g->ballX = g->WDT/2;
	g->ballY = g->HYT-2;
	sprintf(temp, "%c",BALL);
	mvwprintw(g->win,g->ballY,g->ballX,temp);
	return 0;
}