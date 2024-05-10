#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<curses.h>


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


char temp[10000];




typedef struct game{
	WINDOW *win;
	int HYT;
	int WDT;
	int DashLoc;
	int DashSize;
	int ballX;
	int ballY;
	int initBallX;
	int initBallY;
	int ballDir;
	byte dashSpeed; 
	short ballSpeed;
	int direction; 
} Game;


int initGame(Game* g);
int initBall(Game* g);
int initWindow(Game *g);
int moveball(Game* g);
double angle(int degree);
int moveInX(Game* g);
int moveInY(Game* g);
int nearestPoint(Game* g);


int main(){
    Game G;
	initGame(&G);
	// mvwprintw(G.win,1,1,"cur=>(%3d<->%3d)base=>(%3d,%3d)move=>(%d||%d)",g->ballX,g->ballY,g->initBallX,g->initBallY,0,0);
	// Sleep(1000);
	int i = 100;
	while(i--){
		mvwprintw(G.win,1,1,"%d",100-i);
		int out = moveball(&G);
		wrefresh(G.win);
		Sleep(100);
		if(out){break;}
	}
	
    return 0;
}

int moveInX(Game* g){
	if(g->direction >= 0 && g->direction <= 80){
		return 2;
	}else if(g->direction > 80 && g->direction <= 100){
		return 0;
	}else if(g->direction > 100 && g->direction <= 260){
		return -2;
	}else if(g->direction > 260 && g->direction <= 280){
		return 0;
	}else if(g->direction > 280 && g->direction <=360){
		return 2;
	}
}

int moveInY(Game* g){
	if(g->direction >= 0 && g->direction <= 80){
		return -(int)(2*angle(g->direction));
	}else if(g->direction > 80 && g->direction <= 100){
		return -2;
	}else if(g->direction > 100 && g->direction <= 260){
		return -(int)(2*angle(g->direction));
	}else if(g->direction > 260 && g->direction <= 280){
		return 0;
	}else if(g->direction > 280 && g->direction <=360){
		return -(int)(2*angle(g->direction));
	}
}

int moveball(Game* g){
	int nextX,nextY;
	nextX = g->ballX + moveInX(g);
	nextY = g->ballY + moveInY(g);
	mvwprintw(g->win,1,4,"Angle(%3d)|cur=>(%3d <-> %3d)|base=>(%3d <-> %3d)|move=>(%3d || %3d)",g->direction,g->ballX,g->ballY,g->initBallX,g->initBallY,moveInX(g),moveInY(g));
	if(nextX < g->WDT-1 && nextX > 0 && nextY < g->HYT-2 && nextY > 0){
		sprintf(temp,"%c",SPC);
		mvwprintw(g->win,g->ballY,g->ballX,temp);
		g->ballX = nextX;
		g->ballY = nextY;
		sprintf(temp,"%c",BALL);
		mvwprintw(g->win,g->ballY,g->ballX,temp);
		wrefresh(g->win);
		return 0;
	}
	mvwprintw(g->win,2,1,"ouut");
	wrefresh(g->win);
	Sleep(300);
	return 1;
}

int initGame(Game* g){
	system("cls");
	g->dashSpeed = 0;
	g->ballSpeed = 50;
	g->direction = 70;
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
	// initDash(g);
	initBall(g);
	curs_set(0);
	wrefresh(g->win);
	return 0;
}

int initBall(Game* g){
	g->ballX = g->WDT/2;
	g->ballY = g->HYT/2;
	g->initBallX = g->ballX;
	g->initBallY = g->ballY;
	sprintf(temp, "%c",BALL);
	mvwprintw(g->win,g->ballY,g->ballX,temp);
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

double angle(int degree){
	return round(tan(degree*M_PI/180));
}

int nearestPoint(Game* g){
	int x1,x2,y1,y2,
	if(g->ballY <= 0 && g->ballX < g->WDT-1 && g->ballX >= 1){
		return 1;
	}
	return 0;
}