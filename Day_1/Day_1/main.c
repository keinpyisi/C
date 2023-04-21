
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9
#define MAXSIZE 9

int main(void) {
	int row,col;
	int row_tbl[MAXSIZE],col_tbl[MAXSIZE];
	int loop;
	char* linegap = "+----+----+----+----+----+----+----+----+\n";
	
	for (loop = 0; loop < MAXSIZE; loop++) {
		col_tbl[loop] = loop+1;
		row_tbl[loop] = loop+1;
		
	}
	shuffle(col_tbl);
	shuffle(row_tbl);

	for (col = 0; col < COL+1; col++) {
		
		
		if (col == 0) {
			printf("%s", linegap);
		}
		else if (col > 1) {
			printf("%s", linegap);
		}

		if (col == 0) {
			printf("|   |");
		}
		else if(col>1) {
			printf("|%3d|", col_tbl[col-1]);
		}
	
		for (row = 0; row < ROW+1; row++) {
			
			
			if (col == 0) {
				if (row < 9) {
					printf("%3d|", row_tbl[row]);
				}
				
			}
			else if(col>1){
				if (row >= 1 && col >1) {
					printf("%3d|", row * col);
				}
				
			}
			
		}
		if (col == 0) {
			printf("\n");
		}
		else if (col > 1) {
			printf("\n");
		}

	
		
	}

	printf("%s", linegap);
	
	
}	

int shuffle(int array[MAXSIZE])       
{
	int lower = 0, upper = MAXSIZE-1;

	srand(time(0));
	

	int cnt, tmp, rndval;

	for (cnt = 0; cnt < MAXSIZE; cnt++) {
		tmp = array[cnt];
		rndval = (rand() % (upper - lower + 1)) + lower;
		array[cnt] = array[rndval];
		array[rndval] = tmp;
		
	}
	
	return array;
}
