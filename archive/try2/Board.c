#include "./dash_n_dots.h"

void initBoard(WINDOW* win){
    win = newwin(HYT,WDT,0,0);
    for(int i = 0 ;i<HYT;i++){
        for(int j = 0;j<WDT;j++){
            if(i = 0 || i == HYT-1){
                mvwprintw(win,i,j,(char)HOR_LINE);
            }else if(j = 0 || j == WDT-1 ){
                mvwprintw(win,i,j,(char)VER_LINE);
            }else{
                mvwprintw(win,i,j,(char)SPC);
            }
        }
    }
    wrefresh(win); // Refresh the window
}

char keyIsPressed(){
    if(GetAsyncKeyState(VK_LEFT) & 0x8000){
        return MV_LFT;
    }
    if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
        return MV_RYT;
    }
    if(GetAsyncKeyState(VK_UP) & 0x8000){
        return MV_UPP;
    }
    if(GetAsyncKeyState(VK_DOWN) & 0x8000){
        return MV_DWN;
    }
    if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
        return CLOSE;
    }
    return CONT;
}