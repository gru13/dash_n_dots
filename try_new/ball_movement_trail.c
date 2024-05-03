#include<math.h>
#include<stdio.h>

#define star '0'
#define PI		3.14159265358979323846
int X = 10;
int Y = 10;
char matrix[X][Y];

typedef struct path{
    int x;
    int y;
    struct path* next;
} PATH;


void printMat(char matrix[X][Y]){
    for(int i =0 ;i<X;i++){
        for (int j = 0; j < Y; j++){
            printf(" %c ",matrix[i][j]);
        }
        printf("\n");
    }
}

double angle(int degree){
    return degree*PI/180;
}

void initBoard(){
    for(int i =0 ;i<X;i++){
        for (int j = 0; j < Y; j++){
            matrix[i][j] = '|';
        }
    }
    matrix[X/2][Y-1] = star;
}

int main(){
    int direction = 45, baseX = X/2 ,baseY = Y-2;
    // printf("\n%lf\n",tan(angle(direction)));
    initBoard();printMat(matrix);
    

    printf("\nguu\n");
    printMat(matrix);
    return 0;
}
way[len] = X-1 - (int)round((i*tan(angle(direction))));