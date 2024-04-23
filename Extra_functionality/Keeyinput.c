#include <windows.h>
#include<stdio.h>
int main() {

    while(1){
        if(GetAsyncKeyState(VK_LEFT) & 0x8000){
            printf("\rL\n");
            continue;
        }
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
            printf("\rR\n");
            continue;
        }
        if(GetAsyncKeyState(VK_UP) & 0x8000){
            printf("\rU\n");
            continue;
        }
        if(GetAsyncKeyState(VK_DOWN) & 0x8000){
            printf("\rD\n");
            continue;
        }
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
            printf("\rE\n");
            break;
        }
        printf("\rN\n");
    }
  
  return 0;
}