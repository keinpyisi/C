#include <stdio.h>
#define ROW 36
#define COL 36

void init();
void showmap(int map[COL][ROW]);
void copy2DimensioalArray(int source[ROW][COL], int target[ROW][COL]);
void evolve(int map[COL][ROW]);
int checkMap(int source[COL][ROW], int destination[COL][ROW]);
int getSurviveCount(int source[COL][ROW]);
/* 2D array declaration*/
int map[COL][ROW];
int temp[COL][ROW];
int dead[COL][ROW];
FILE* fp;

int main(void) {
 
    
    printf("\033[2J");
    
    //init map
    init();
    copy2DimensioalArray(map, temp);
    int gen=1;
    //Generation
    while(-1) {
       
        
        showmap(map); 
        evolve(map);
        printf("世代 = % d\n", gen);
        printf("生存数 = % d\n", getSurviveCount(map));
        //printf("\n");
        printf("\033[2;1H"); // カーソル位置を、高さ2行目、横1文字目に移動　⇒ 正しく動作しない場合は最終ページを参照してください。
        if (checkDeadMap(dead, map) == 0) {
            printf("EVERYONE IS DEAD. \n");
            break;
        }
      
        gen += 1;

    }
    
    
    return 0;
}

//Initialize Data
void init() {
    //generate matrix canvas with random values (live and dead cells)
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (rand() % 2 == 0) {
                map[row][col] = '.';
            }
            else {
                //map[row][col] = '@';
                map[row][col] = '@';
            }
            dead[row][col] = '@';

        }
    }
    
}
//Show Map
void showmap(int map[COL][ROW]) { 
    //Displaying array elements
    for (int col = 0; col < COL; col++) {
        for (int row = 0; row < ROW; row++) {
            printf("%c ", map[col][row]);

        }
        printf("\n");
    }
}

//Evolve Cells
void evolve(int map[COL][ROW]) {
    //False
    if (checkMap(temp, map) != 1) {
        
        
        copy2DimensioalArray(map, temp);
        int neighbors = 0;
        
        //Check 2D Map If it equal or not

        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++) {
               
                neighbors = 0;

                 if (row > 0 && col > 0 && map[row - 1][col - 1] == '.')
                 {
                     neighbors++;
                 }
                 if (col > 0 && map[row][col - 1] == '.')
                 {
                     neighbors++;
                 }

                 if (col > 0 && row < ROW - 1 && map[row + 1][col - 1] == '.')
                 {
                     neighbors++;
                 }

                 if (row > 0 && map[row - 1][col] == '.')
                 {
                     neighbors++;
                 }

                 if (col < 0 && row < ROW - 1 && map[row + 1][row - 1] == '.')
                 {
                     neighbors++;
                 }

                 if (row > 0 && col < COL - 1 && map[row - 1][col + 1] == '.')
                 {
                     neighbors++;
                 }

                 if (col < COL - 1 && map[row][col + 1] == '.')
                 {
                     neighbors++;
                 }

                 if (row < ROW - 1 && col < COL - 1 && map[row + 1][col + 1] == '.')
                 {
                     neighbors++;
                 }

                 if (neighbors < 2 || neighbors > 3) {
                     // 1. Any live cell with fewer than two live neighbours dies
                     // 3. Any live cell with more than three live neighbours dies
                     map[row][col] = '@';
                 }
                 else if (neighbors == 4) {
                     // 4. Any dead cell with exactly three live neighbours becomes a live cell.
                     map[row][col] = '.';
                 }
                 
                 
                


            }
           


        }
        
       
 
    }
    else {
    
        init();
       //True
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

//Check 2D Map If it equal or not
int checkMap(int source[COL][ROW], int destination[COL][ROW]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (destination[row][col] != source[row][col]) {
                return 0;
            }
        }
    }
    return 1;
}

//Check Survived Cell
int getSurviveCount(int source[COL][ROW]) {
    int survive = 0;
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (source[row][col] == '.') {
                survive += 1;
            }
        }
    }
    return survive;
}

//Check 2D Map If it equal or not
int checkDeadMap(int source[COL][ROW], int destination[COL][ROW]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (destination[row][col] != source[row][col]) {
                return 1;
            }
        }
    }
    return 0;
}
