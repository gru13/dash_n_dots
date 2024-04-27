#include<math.h>
#include<stdio.h>

#define star '0'

int X = 10;
int Y = 10;

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
    return degree*M_PI/180;
}
int move(char matrix[X][Y], int* direction,int x, int y, PATH*);

int main(){
    char matrix[X][Y];
    int Max_X = X-1;
    int Min_X = 0;
    int Max_Y = Y-1;
    int Min_Y = 0;
    int direction = 45;
    printf("\n%lf\n",tan(angle(direction)));
    for(int i =0 ;i<X;i++){
        for (int j = 0; j < Y; j++){
            matrix[i][j] = '|';
        }
    }
    int x = Max_X;
    int y = Max_Y/2;
    matrix[x][y] = star;
    printMat(matrix);
    int way[200];
    int len = 0;
    for(int i = 1;i<=Max_Y-y;i++){
        printf("%d\t",i);
        
        way[len] = Max_X - (int)round((i*tan(angle(direction))));
        matrix[way[len]][y+i]= star;
        // printf("(%d - %d)\t",way[len],y+i);
        len++;
    } 
    printf("\nguu\n");
    printMat(matrix);

}

int move(char matrix[X][Y], int* direction, int x,int y, PATH* path){
    if(direction == 90){
        
    }
}