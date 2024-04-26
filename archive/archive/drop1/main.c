#include "./Inbulit_types.h"

int prevGameState; 

int main(){
    initscr();
    curs_set(0);
    struct Game G;
    G.GameState = 0;
    prevGameState = G.GameState; 
    initBoard(G.board);
    Sleep(3000);
    delwin(G.board);
    endwin();
    return 0;
}