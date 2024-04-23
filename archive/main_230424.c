#include "./Inbulit_types.h"

int prevGameState; 


int main(){
    // Intilalize the Display
    initscr();  // Initialize ncurses
    // system("cls");
    // printf("\e[?25l");// hiding the cursor
    
    
    struct Game G;
    G.GameState = 0;
    prevGameState = G.GameState; 
    initBoard(&G.board);
    char ctrl = CONT;

    printBoard(G.board.Board);
    while(ctrl != CLOSE){
        ctrl = keyIsPressed();
        if(ctrl != CONT){
            printf("%c\n",ctrl);
            updateGamestate(&G.GameState);
        }

        if(prevGameState != G.GameState){
            system("cls");
            printBoard(G.board.Board);
        }

        printf("\n------------------------\n%d\n------------------------\n",G.GameState);
    }
    
    // EXiting the Game
    system("cls");
    printf("\e[?25h"); // Show the cursor again
    return 0;
}

void updateGamestate(int* curState){
    prevGameState = *curState;
    *curState += 1;
}