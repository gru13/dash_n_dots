#include "./Inbulit_types.h"


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
}

// void initBoard(struct Board *b){ 
//     for(int i = 0 ;i<HYT;i++){
//         for(int j = 0;j<WDT;j++){
//             b->Board[i][j] = SPC;
//         }
//     }
//     for(int i = 0;i<WDT;i++){   
//         b->Board[0][i] = HOR_LINE;
//         b->Board[HYT-1][i] = HOR_LINE;
//     }
//     for(int i = 0; i < HYT; i++){
//         b->Board[i][0] = VER_LINE;
//         b->Board[i][WDT-1] = VER_LINE;
//     }
//     b->Board[0][0] = TL_COR;
//     b->Board[0][WDT-1] = TR_COR;
//     b->Board[HYT-1][0] = BL_COR;
//     b->Board[HYT-1][WDT-1] = BR_COR;
// }

// void printBoard(char Board[HYT][WDT]){
//     char TotalBoard[MAX_LINE];
//     int l = 0;
//     for(int i = 0 ;i<HYT;i++){
//         for(int j = 0;j<WDT;j++){
//             TotalBoard[l] = Board[i][j];
//             l++;
//         }
//         TotalBoard[l] = '\n';
//         l++;
//     }
//     TotalBoard[l] = '\0';
//     // printf("%s",TotalBoard);
// }


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