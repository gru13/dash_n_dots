#include "./Inbulit_types.h"

int main(){
    // Intilalize the Display
    // system("cls");
    // printf("\e[?25l");// hiding the cursor
    struct Game G;


    DrawBoard(G);
    Sleep(3000);
    
    // // EXiting the Game
    // system("cls");
    // printf("\e[?25h"); // Show the cursor again
    return 0;
}