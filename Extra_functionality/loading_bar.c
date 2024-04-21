#include<stdio.h>
#include<stdlib.h>

int main(){
    for (int i = 0; i < 20; i++){
        system("cls");
        printf("\t\t\t\tIntializing : ");
        for(int j =0 ; j<i;j++){
            printf("%c",219);
        }
        for(int j =0 ; j<i+18;j++){
            printf("\r");
        }
        Sleep(1000);
    }
}