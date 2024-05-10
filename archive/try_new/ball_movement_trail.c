#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define star '0'
long double PI = 3.14159265358;
// #define PI	3.14159265358979323846
#define emt ' ' 

int X = 50;
int Y = 160;


char temp[10000];

void printMat(char matrix[X][Y]){
    system("cls");
    int qx,qy,c = 0;
    for(int i =0 ;i<X;i++){
        for (int j = 0; j < Y; j++){
            temp[c] = matrix[i][j];
            c++;
            if(matrix[i][j] == star){
                qx = i;
                qy = j;
            }
        }
        temp[c] = '\n';
        c++;
    }
    sprintf(&temp[c],"%d-%d",qx,qy);
    // temp[c] = '\0';
    // c++;
    printf("%s",temp);
    
}

double angle(int degree){
    return degree*PI/180;
}

void initBoard(char matrix[X][Y]){
    for(int i =0 ;i<X;i++){
        for (int j = 0; j < Y; j++){
            if(i == 0 || j == 0 || i == X -1 || j == Y-1){
                matrix[i][j] = '*';
            }else{
                matrix[i][j] = (char)emt;
            }
        }
    }
    matrix[X-2][Y/2] = (char)star;
}


int towards(int direction){
    if(direction == 90 || direction == 270){
        return 0;
    }else if(direction >= 0 && direction < 90 || direction > 270 && direction <=360){
        return 1;
    }else if(direction > 90 && direction <=270){
        return -1;
    }
}

int ifInRange(int x, int y){
    if(x <=1 || x >= X-2){
        return 0;
    }
    if(y <=1 || y >= Y-1){
        return 0;
    }
    return 1;
}

int main(){
    char matrix[X][Y];
    int direction = 40, baseX = X-2 ,baseY = Y/2;
    int curX = baseX;
    int curY = baseY;
    // printf("\n%lf\n",tan(angle(direction)));
    // Sleep(2000);
    initBoard(matrix);printMat(matrix);
    while(1){
        matrix[curX][curY] = emt;
        int tempY = curY + towards(direction);
        int tempX = baseX + (int)round((curX - baseX)*tan(angle(direction)));
        printf("\n(%d - %d)=>(%d - %d)(direction => %d)\n",curX,curY,tempX,tempX,towards(direction));
        // Sleep(200);
        if(ifInRange(tempX,tempY) == 0){
            curX = tempX;
            curY = tempY;
        }else{
            printf("\nrwsedtghijkl;,ljbvfdxresarxdgjkbhfctdrsxedtfghbjnbfcdxesardtfygh\n");
            direction += 90;
            direction %= 360;
            baseX = curX;
            baseY = curY;
            Sleep(200);
        }
        matrix[curX][curY] = star;
        printMat(matrix);
        Sleep(200);
    }
    
    


    printf("\nguu\n");
    printMat(matrix);
    return 0;
}
// way[len] = X-1 - (int)round((i*tan(angle(direction))));

