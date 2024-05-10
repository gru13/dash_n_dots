#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<curses.h>
#include <pthread.h>


#define PI 3.14159265358979323846
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
    pthread_t thread;
}Ball;

typedef struct game{
    WINDOW* win;
    int hyt;
    int wdt;
    Dash dash;
    Ball ball;
}Game;

DWORD dashSPEEDS[] = {1,5,35,85};
int nofSdp = sizeof(dashSPEEDS)/sizeof(DWORD);
char ctrl = CONT;// this will act as a muthex lock like mechanism
char finsh = CONT;

int keyIsPressed();
int initGame(Game* g);
int initWindow(Game *g);
int changedashSpeed(Game* G,int ctrl);

int initDash(Game* g);
void* moveDash(void* arg);
int changedashSpeed(Game* G,int ctrl);


int initBall(Game* g);
void* moveBall(void* g);
double angle(int degree);
int moveInX(Game* g);
int moveInY(Game* g);
int nearestPoint(Game* g);

int main(){
    Game G;
    initGame(&G);
    pthread_create(&G.dash.thread,NULL,moveDash,(void*)&G);
    // pthread_create(&G.ball.thread,NULL,moveBall,(void*)&G);

    // pthread_join(G.ball.thread,NULL);
    pthread_join(G.dash.thread,NULL);
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
	initBall(g);
	initDash(g);
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
	g->dash.Size = 10;
	g->dash.Loc.x = g->wdt/2;
	g->dash.Loc.y = g->hyt-2;
	g->dash.Speed = 0;
    for(int i = g->dash.Loc.x-g->dash.Size; i < g->dash.Loc.x+g->dash.Size;i++){
		sprintf(temp, "%c",DASH);
		mvwprintw(g->win,g->dash.Loc.y,i,temp);
    }
	wrefresh(g->win);
	return 0;
}

void* moveDash(void* arg){
    Game* g = (Game*)arg;
	while(ctrl != CLOSE){
        ctrl = keyIsPressed();
        int x = g->dash.Loc.x;
        int y = g->dash.Loc.y;
        int s = g->dash.Size;
		if(ctrl == CONT){
			continue;
		}else if(ctrl == MV_LFT && x - s > 1){
			sprintf(temp, "%c",SPC);
			mvwprintw(g->win,y,x+s,temp);
			sprintf(temp, "%c",DASH);
			mvwprintw(g->win,y,x-s-1,temp);
			g->dash.Loc.x -=1;
			ctrl = CONT;
		}else if(ctrl == MV_RYT && x + s < g->wdt-2){
			sprintf(temp, "%c",SPC);
			mvwprintw(g->win, y,x-s, temp);
			sprintf(temp, "%c",DASH);
			mvwprintw(g->win,y,x+s+1,temp);
			g->dash.Loc.x += 1;
		}else if(ctrl == MV_UPP || ctrl == MV_DWN){
			changedashSpeed(g,ctrl);
		}else if(ctrl == CLOSE){
            break;
        }
		ctrl = CONT;
		Sleep(dashSPEEDS[g->dash.Speed]);
		wrefresh(g->win);
	}
	finsh = CLOSE;
	return NULL;
}

int changedashSpeed(Game* G,int ctrl){
	if(ctrl == MV_UPP){
		G->dash.Speed += 1;
		if(G->dash.Speed >= nofSdp){
			G->dash.Speed = nofSdp-1;
		}
	}
	if(ctrl == MV_DWN){
		G->dash.Speed -= 1;
		if(G->dash.Speed <= 0){
			G->dash.Speed = 0;
		}

	}
	Sleep(100);
	return 0;
}

void* moveBall(void* arg){
    Game* g = (Game*)arg;
    while(finsh != CLOSE){
        Point next;
        next.x = g->ball.Loc.x + moveInX(g);
        next.y = g->ball.Loc.y + moveInY(g);
        mvwprintw(g->win,1,4,"Angle(%3d)|cur=>(%3d <-> %3d)|base=>(%3d <-> %3d)|move=>(%3d || %3d)",
                    g->ball.direction,g->ball.Loc.x,g->ball.Loc.y,g->ball.BaseLoc.x,g->ball.BaseLoc.y,moveInX(g),moveInY(g));
	    if(next.x < g->wdt-1 && next.x > 0 && next.y < g->hyt-2 && next.y > 0){
            sprintf(temp,"%c",SPC);
            mvwprintw(g->win,g->ball.Loc.y,g->ball.Loc.x,temp);
            g->ball.Loc.x = next.x;
            g->ball.Loc.y = next.y;
            sprintf(temp,"%c",BALL);
            mvwprintw(g->win,g->ball.Loc.y,g->ball.Loc.x,temp);
            wrefresh(g->win);
            continue;
        }
        mvwprintw(g->win,2,1,"ouut");
        wrefresh(g->win);
        Sleep(300);
        break;
    }
    return NULL;
}


int moveInX(Game* g){
	if(g->ball.direction >= 0 && g->ball.direction <= 80){
		return 2;
	}else if(g->ball.direction > 80 && g->ball.direction <= 100){
		return 0;
	}else if(g->ball.direction > 100 && g->ball.direction <= 260){
		return -2;
	}else if(g->ball.direction > 260 && g->ball.direction <= 280){
		return 0;
	}else if(g->ball.direction > 280 && g->ball.direction <=360){
		return 2;
	}
}

int moveInY(Game* g){
	if(g->ball.direction >= 0 && g->ball.direction <= 80){
		return -(int)(2*angle(g->ball.direction));
	}else if(g->ball.direction > 80 && g->ball.direction <= 100){
		return -2;
	}else if(g->ball.direction > 100 && g->ball.direction <= 260){
		return -(int)(2*angle(g->ball.direction));
	}else if(g->ball.direction > 260 && g->ball.direction <= 280){
		return 0;
	}else if(g->ball.direction > 280 && g->ball.direction <=360){
		return -(int)(2*angle(g->ball.direction));
	}
}

double angle(int degree){
    return degree*PI/180;
}

int initBall(Game* g){
	g->ball.direction = 90;
	g->ball.Speed = 3;
	g->ball.BaseLoc.x = g->wdt/2; 
	g->ball.BaseLoc.y = g->hyt-3; 
	g->ball.Loc.x = g->ball.BaseLoc.x; 
	g->ball.Loc.y = g->ball.BaseLoc.y;
	sprintf(temp,"%c",BALL);
	mvwprintw(g->win,g->ball.Loc.y,g->ball.Loc.x,temp);
	wrefresh(g->win);
	return 0;
}

