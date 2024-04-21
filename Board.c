#include "./Inbulit_types.h"


int DrawBoard(struct Game G){
    char Board[HYT][WDT];
    for(int i = 0;i<WDT;i++){   
        Board[0][i] = '*';
        Board[WDT-1][i] = '*';
    }
    // for(int i =1 ;i<HYT-1;i++){
    //     for(int j =0 ;j<WDT;j++){
    //         if(j == 0  || j == WDT-1){
    //             Board[i][j] = '*';
    //         }else{
    //             Board[i][j] = 32;
    //         }
    //     }
    // }
    for(int i = 0 ;i<HYT;i++){
        for(int j = 0;j<WDT;j++){
            printf("%c",Board[i][j]);
        }
        printf("\n");
    }
    return 0;
}