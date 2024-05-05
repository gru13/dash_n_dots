#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<curses.h>
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


char temp[100];

typedef struct point{
    int x;
    int y;
}Point;

typedef struct dash{
    Point Loc;
    int Size;
    byte Speed;
    pthread_t thread;
}Dash;

typedef struct ball{
    Point Loc;
    Point BaseLoc;
    short Speed;
    int direction;
}Ball;

typedef struct game{
    WINDOW* win;
    int hyt;
    int wdt;
    Dash dsh;
    Ball Bal;
}Game;

DWORD dashSPEEDS[] = {1,5,35,85};
int nofSdp = sizeof(dashSPEEDS)/sizeof(DWORD);
char ctrl = CONT;// this will act as a muthex lock like mechanism

int keyIsPressed();
int initGame(Game* g);
int initWindow(Game *g);
int changedashSpeed(Game* G,int ctrl);

int initDash(Game* g);
void* MoveDash(void* arg);
int changedashSpeed(Game* G,int ctrl);


int initBall(Game* g);
void* moveBall(void* g);
double angle(int degree);
int moveInX(Game* g);
int nearestPoint(Game* g);

int main(){
    Game G;
    initGame(&G);
    pthread_create(&G.dsh.thread,NULL,MoveDash,(void*)&G);

    pthread_join(G.dsh.thread,NULL);
    delwin(G.win);
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


int initGame(Game* g){
	system("cls");
	g->win = initscr();
	if (g->win == NULL){
		printf("Error in creating Screen\n");
		return 1;
	}
	g->wdt = getmaxx(g->win);
	g->hyt = getmaxy(g->win);
	initWindow(g);
	initDash(g);
	// initBall(g);
	curs_set(0);
	wrefresh(g->win);
	return 0;
}

int initWindow(Game *g){
	for(int i = 0;i<g->hyt;i++){
		for(int j =0 ; j<g->wdt;j++){
			if(i == 0 || i == g->hyt-1){
				sprintf(temp, "%c",HOR_LINE);
				mvwprintw(g->win,i,j,temp);
			}
			else if(j == 0 || j == g->wdt-1){
				sprintf(temp, "%c",VER_LINE);
				mvwprintw(g->win,i,j,temp);
			}
		}
	}

	// corners
	sprintf(temp, "%c",TL_COR);
	mvwprintw(g->win,0,0,temp);
	sprintf(temp, "%c",TR_COR);
	mvwprintw(g->win,0,g->wdt-1,temp);
	sprintf(temp, "%c",BL_COR);
	mvwprintw(g->win,g->hyt-1,0,temp);
	sprintf(temp, "%c",BR_COR);
	mvwprintw(g->win,g->hyt-1,g->wdt-1,temp);

	wrefresh(g->win);

}

int initDash(Game* g){
	g->dsh.Size = 10;
	g->dsh.Loc.x = g->wdt/2;
	g->dsh.Loc.y = g->hyt-2;
	g->dsh.Speed = 0;
    for(int i = g->dsh.Loc.x-g->dsh.Size; i < g->dsh.Loc.x+g->dsh.Size;i++){
		sprintf(temp, "%c",DASH);
		mvwprintw(g->win,g->dsh.Loc.y,i,temp);
    }
	wrefresh(g->win);
	return 0;
}

void* MoveDash(void* arg){
    Game* g = (Game*)arg;
	ctrl = keyIsPressed();
	while(ctrl != CLOSE){
		ctrl = keyIsPressed();
        int x = g->dsh.Loc.x;
        int y = g->dsh.Loc.y;
        int s = g->dsh.Size;
		// location checking purpose
		sprintf(temp, "%c|(%3d,%3d)|%3d",(char)ctrl,x,y,dashSPEEDS[g->dsh.Speed]);
		mvwprintw(g->win,1,1,temp);	
		if(ctrl == CONT){
			continue;
		}else if(ctrl == MV_LFT && x - s > 1){
			sprintf(temp, "%c",SPC);
			mvwprintw(g->win,y,x+s,temp);
			sprintf(temp, "%c",DASH);
			mvwprintw(g->win,y,x-s-1,temp);
			g->dsh.Loc.x -=1;
			ctrl = CONT;
		}else if(ctrl == MV_RYT && x + s < g->wdt-2){
			sprintf(temp, "%c",SPC);
			mvwprintw(g->win, y,x-s, temp);
			sprintf(temp, "%c",DASH);
			mvwprintw(g->win,y,x+s+1,temp);
			g->dsh.Loc.x += 1;
		}else if(ctrl == MV_UPP || ctrl == MV_DWN){
			changedashSpeed(g,ctrl);
		}else if(ctrl == CLOSE){
            break;
        }
		ctrl = CONT;
		Sleep(dashSPEEDS[g->dsh.Speed]);
		wrefresh(g->win);
	}
	return NULL;
    
}

int changedashSpeed(Game* G,int ctrl){
	if(ctrl == MV_UPP){
		G->dsh.Speed += 1;
		if(G->dsh.Speed >= nofSdp){
			G->dsh.Speed = nofSdp-1;
		}
	}
	if(ctrl == MV_DWN){
		G->dsh.Speed -= 1;
		if(G->dsh.Speed <= 0){
			G->dsh.Speed = 0;
		}
		
	}
	Sleep(100);
	return 0;
}