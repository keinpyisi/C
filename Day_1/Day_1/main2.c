#include <stdio.h>
#define MAXSIZE 9


char* hline = "+----+----+----+----+----+----+----+----+";
int main(void) {

	int tate, yoko,temp;
	int row_tbl[MAXSIZE], col_tbl[MAXSIZE];
	for (temp = 0; temp < MAXSIZE; temp++) {
		row_tbl[temp] = temp + 1;
		col_tbl[temp] = temp + 1;
	}
	shuffle(row_tbl);
	shuffle(col_tbl);
	printf("%s\n", hline);
	
	printf("|@ ");
	
	for (yoko = 0; yoko < MAXSIZE; yoko++) {
		printf("|%3d", row_tbl[yoko]);
	}

	printf("|\n");

	printf("%s\n", hline);
	for (tate = 1; tate <= MAXSIZE; tate++) {

		printf("|%3d", col_tbl[tate-1]);

		for (yoko = 1; yoko <= MAXSIZE; yoko++) {
			printf("|%3d", col_tbl[tate-1] * row_tbl[yoko-1]);
		}

		printf("|\n");
		printf("%s\n", hline);
	}
}

int shuffle(int array[MAXSIZE])
{
	int lower = 0, upper = MAXSIZE - 1;

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
