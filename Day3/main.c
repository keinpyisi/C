#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ROW 38
#define COL 76
#define LIVE 1
#define DEAD 0

void init(int map[ROW][COL]);
void showmap(int map[ROW][COL]);
void copy2DimensioalArray(int source[ROW][COL], int target[ROW][COL]);
void evolve(int map[ROW][COL]);
int getSurviveCount(int temp[ROW][COL], int row, int col);
void readfile(int map[ROW][COL], char* filename);
int main(void) {

    printf("Press File Name or Number : ");

    int user;
    //init map
    int map[ROW][COL];
    //Get User Input Variable and check if it is char or int
   
    char buffer[CHAR_MAX];
    (void)scanf("%s", buffer);

    //Check If the first word is digit or not
    if (isdigit(buffer[0])) {
        srand(buffer);
        init(map);
    }
    else {
        readfile(map, buffer);
    }


    printf("\033[2J"); // 画面を消す
    
    int gen = 1;
    //Generation
    while(-1) {

        printf("\033[2;1H");
        printf("世代 = %d \n", gen);
        showmap(map);
        evolve(map);
        gen += 1;
    } 
    
    return 0;
}

void readfile(int map[ROW][COL],char *filename) {
    FILE* fp;
    char buffer[CHAR_MAX];
    int row = 0;
    //Open File and Put it in Filepointer
    if ((fp = fopen(filename, "r")) != NULL) {
       //Put File Line by Line in buffer
        while (fgets(buffer, CHAR_MAX, fp)) {
          //Making Map Defined
            for (int col = 0; col < COL; col++) {
                //If One Word in One Life is 1
                if (buffer[col] == '1') {

                    if (col < (strlen(buffer)+1)) {
                        map[row][col] = LIVE;
                    }
                }
                else {
                    map[row][col] = DEAD;
                }
              
            }
            row = row + 1;
           
        }
  
    }
    
}

//Initialize Data
void init(int map[ROW][COL]) {
    //generate matrix canvas with random values (live and dead cells)
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            int num = rand() % 10;
            if (num < 7) {
                map[row][col] = DEAD;
            }
            else {
                map[row][col] = LIVE;
            }

        }
    }
    
    
}

//Show Map
void showmap(int map[ROW][COL]) { 
    //Displaying array elements
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (map[row][col] == LIVE) {
                printf("%c", '@');
            }
            else  {
                printf("%c", '.');
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
int getSurviveCount(int temp[ROW][COL], int row, int col) {
    int sum = 0;
    //row y , col x WORLD_h = ROW
    if ( (row > 0) && (col > 0)) {
        sum+= temp[row - 1][col - 1]; //Left Up
    }

    if (col > 0) {
        sum += temp[row][col-1]; //Left
    }

    if ((row < ROW -1) && (col >0) ) {
        sum += temp[row + 1][col - 1]; //Left Down
    }
    
    if ((row < ROW -1)) {
        sum += temp[row + 1][col]; //Down 
    }

    if ((row < (ROW - 1)) && (col < (COL - 1)) ) {
        sum += temp[row + 1][col + 1]; //Right Down
    }

    if ((col < (COL - 1))) {
        sum += temp[row][col + 1]; //Right
    }

    if ((row >0) && (col < COL -1 )) {
        sum += temp[row - 1][col + 1]; //Right Up
    }

    if (row > 0) {
        sum += temp[row - 1][col]; //Up
    }

    return sum;
}


