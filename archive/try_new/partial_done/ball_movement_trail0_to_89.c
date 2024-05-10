#include<math.h>
#include<stdio.h>

void printMat(char matrix[10][10]){
    for(int i =0 ;i<10;i++){
        for (int j = 0; j < 10; j++){
            printf(" %c ",matrix[i][j]);
        }
        printf("\n");
    }
}

double angle(int degree){
    return degree*M_PI/180;
}

int main(){
    char matrix[10][10];
    int Max_X = 9;
    int Min_X = 0;
    int Max_Y = 9;
    int Min_Y = 0;
    int direction = 50;
    printf("\n%lf\n",tan(angle(direction)));
    for(int i =0 ;i<10;i++){
        for (int j = 0; j < 10; j++){
            matrix[i][j] = '0';
        }
    }
    int x = 9;
    int y = 9/2;
    matrix[x][y] = '+';
    printMat(matrix);
    int way[200];
    int len = 0;
    for(int i = 1;i<=Max_Y-y;i++){
        printf("%d\t",i);
        
        way[len] = Max_X - (int)round((i*tan(angle(direction))));
        matrix[way[len]][y+i]= '+';
        // printf("(%d - %d)\t",way[len],y+i);
        len++;
    } 
    printf("\nguu\n");
    printMat(matrix);

}