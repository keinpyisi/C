#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ROW 36
#define COL 72
#define LIVE '@'
#define DEAD '.'

void init(int map[ROW][COL]);
void showmap(int map[ROW][COL]);
void copy2DimensioalArray(int source[ROW][COL], int target[ROW][COL]);
void evolve(int map[ROW][COL]);
int getSurviveCount(int temp[ROW][COL], int ypos, int xpos);
void readfile();
int main(void) {

    printf("Press any numbers: ");
    int c = getc(stdin);
    srand(c);

   // readfile();
    printf("\033[2J"); // 画面を消す
    
    //init map
    int map[ROW][COL];
    init(map);
   
    int gen=1;
    //Generation
    for (gen = 1; gen < 1000; gen++) {

        printf("\033[2;1H");
        printf("世代 = %d \n", gen);
        showmap(map);
        evolve(map);
    } 
    
    
    
    return 0;
}

void readfile() {
    int c;
    FILE* fp;
    float array[ROW][COL];

    if ((fp = fopen("sample_data1.txt", "r")) != NULL) {
       
        
        

    }
    
}

//Initialize Data
void init(int map[ROW][COL]) {
    //generate matrix canvas with random values (live and dead cells)
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            int num = rand() % 10;
            if (num < 7) {
                map[row][col] = 0;
            }
            else {
                map[row][col] = 1;
            }
            
                //
        }
    }
    
    
}

//Show Map
void showmap(int map[ROW][COL]) { 
    //Displaying array elements
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (map[row][col] == 1) {
                printf("%c", LIVE);
            }
            else  {
                printf("%c", DEAD);
            }

        }
        printf("\n");
    }
}

//Evolve Cells
void evolve(int map[ROW][COL]) {
    int temp[ROW][COL];
    int sum;
    copy2DimensioalArray(map, temp);
    

    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {

            sum = getSurviveCount(temp, row, col);

            if (temp[row][col] == 0 && sum ==  3) {
                //If Sum of the cell is 3 , New Cell
                map[row][col] = 1;
            }
            else if(temp[row][col] == 1 && (sum<=1 || sum>=4)) {
                //If Sum of the cell is 4 or greather than 4 , Dead
                map[row][col] = 0;
            }
           
        }
    }
    

}



// copy one two-dimensional array to another
void copy2DimensioalArray(int source[ROW][COL], int target[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            target[row][col] = source[row][col];
        }
    }
}


//Check Survived Cell
int getSurviveCount(int temp[ROW][COL],int row,int col) {
    int sum = 0;

    if ( (row > 0) && (col > 0)) {
        sum+= temp[row - 1][col - 1]; //Left Up
    }

    if (row > 0) {
        sum += temp[row - 1][col]; //Left
    }

    if ((row > 0) && (col < COL - 1) ) {
        sum += temp[row - 1][col + 1]; //Left Down
    }
    
    if ((row > 0) && (col < COL -1)) {
        sum += temp[row][col + 1]; //Down X=0 y= 1
    }

    if ((row < ROW - 1) && (col < COL - 1) ) {
        sum += temp[row + 1][col + 1]; //Right Down
    }

    if ((row < ROW - 1) && (col > 0)) {
        sum += temp[row + 1][col]; //Right
    }

    if ((row < ROW - 1) && (col > 0)) {
        sum += temp[row + 1][col - 1]; //Right Up
    }

    if ((row < ROW - 1) && (col < COL - 1)) {
        sum += temp[row + 1][col + 1]; //Up
    }

    return sum;
}


