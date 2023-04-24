#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 12
int shuffle(int array[MAX_SIZE], int max_size);
void str_append(char** s, char ch);
void printline(char line[], int count);
void main_program(int max_size);
int main(void) {

	while (-1) {
		int max_size = 0;
		printf("Enter a Number Between 2 and %d: ", (MAX_SIZE + 1));
		(void)scanf("%d", &max_size);
		if (max_size == 0) {
			break;
		}
		if (max_size < 2) {
			printf("Please Input Between 2 and %d ", (MAX_SIZE + 1));
		}
		
		if (max_size > MAX_SIZE) {
			printf("Please Dont Put Number Greater than %d \n", (MAX_SIZE + 1));
			break;
		}
		if (max_size >= 2) {
			
			printf("The Programming Will Be Generating %d x %d \n", max_size, max_size);
			main_program(max_size);
			break;
		}
		
		
	}
	
}

void main_program(int max_size) {
	int tate, yoko, temp;
	int row_tbl[MAX_SIZE], col_tbl[MAX_SIZE];

	char hline[] = "+----";




	printline(hline, max_size);

	for (temp = 0; temp < max_size; temp++) {

		row_tbl[temp] = temp + 1;
		col_tbl[temp] = temp + 1;
	}
	shuffle(row_tbl, max_size);
	shuffle(col_tbl, max_size);

	printf("| @ ");

	for (yoko = 0; yoko < max_size; yoko++) {
		printf("|%3d ", row_tbl[yoko]);
	}

	printf("|\n");

	printline(hline, max_size);

	for (tate = 1; tate <= max_size; tate++) {

		printf("|%3d ", col_tbl[tate - 1]);

		for (yoko = 1; yoko <= max_size; yoko++) {
			printf("|%3d ", col_tbl[tate - 1] * row_tbl[yoko - 1]);
		}

		printf("|\n");
		printline(hline, max_size);

	}
}

int shuffle(int array[10],int MAXSIZE)
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

void printline(char line[], int count) {

	for (int num = 0; num <= count; num++) {
		printf("%s", line);
	}
	printf("%c\n",line[0]);

}