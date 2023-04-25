#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 12

int shuffle(int array[MAX_SIZE], int max_size);
void printline(char line[], int count);
void main_program(int max_size);

int main(void) {
	//How to Use Pointer
	const char *test = "JTECHABCDE";
	char test1 = *test;
	char test2 = *(test + 1);
	printf("%c\n", test1);
	printf("%c\n", test2);

	/*
	Function: Infinity Loop
	*/
	while (-1) {
		int max_size = 0;
		/*
			Function: Getting User Input
		*/
		printf("Enter a Number Between 2 and %d: ", (MAX_SIZE + 1));
		(void)scanf("%d", &max_size);

		/*
		Function: Checking User Input Conditions 
		*/
		if (max_size == 0) {
			/*
			Function: If User Input 0 , the program will exit
			*/
			break;
		}
		if (max_size < 2) {
			/*
			Function: If User Input 1 , the program will ask again
			*/
			printf("Please Input Between 2 and %d ", (MAX_SIZE + 1));
		}
		
		if (max_size > MAX_SIZE) {
			/*
			Function: If User Input Number Greater Than MAX_SIZE , the program will angry and Exit
			*/
			printf("Please Dont Put Number Greater than %d \n", (MAX_SIZE + 1));
			break;
		}
		if (max_size >= 2) {
			/*
			Function: If User Input Number Greater Than 1 and Less than MAX_SIZE , the program will work.
			*/
			printf("The Programming Will Be Generating %d x %d \n", max_size, max_size);
			main_program(max_size);
			break;
		}
		
		
	}
	
}
/*
Function: Generating Table And Calculating From User Input
Param : max_size
return : void
*/
void main_program(int max_size) {
	int tate, yoko, temp;
	int row_tbl[MAX_SIZE], col_tbl[MAX_SIZE];

	char hline[] = "+----";

	printline(hline, max_size);

	/*
		Function: Filling Generated Numbers Inside Row and Col
	*/
	for (temp = 0; temp < max_size; temp++) {

		row_tbl[temp] = temp + 1;
		col_tbl[temp] = temp + 1;
	}
	/*
		Function: Shuffle Array
	*/
	shuffle(row_tbl, max_size);
	shuffle(col_tbl, max_size);

	printf("| @ ");
	/*
		Function: Printing Index
	*/
	for (yoko = 0; yoko < max_size; yoko++) {
		printf("|%3d ", row_tbl[yoko]);
	}

	printf("|\n");

	printline(hline, max_size);
	/*
		Function: Printing Calculated Ints of Rows and Cols
	*/
	for (tate = 1; tate <= max_size; tate++) {

		printf("|%3d ", col_tbl[tate - 1]);

		for (yoko = 1; yoko <= max_size; yoko++) {
			printf("|%3d ", col_tbl[tate - 1] * row_tbl[yoko - 1]);
		}

		printf("|\n");
		printline(hline, max_size);

	}
}
/*
Function: Shuffling Int Inside Array
Param : array , maxsize which is User Input
return : Shuffled Int Array
*/
int shuffle(int array[MAX_SIZE],int maxsize)
{
	int lower = 0, upper = maxsize - 1;

	srand(time(0));


	int cnt, tmp, rndval;

	for (cnt = 0; cnt < maxsize; cnt++) {
		tmp = array[cnt];
		rndval = (rand() % (upper - lower + 1)) + lower;
		array[cnt] = array[rndval];
		array[rndval] = tmp;

	}

	return array;
}
/*
Function: Print +----- As User Defined Count
Param : line[] , count
return : Void
*/
void printline(char line[], int count) {

	for (int num = 0; num <= count; num++) {
		printf("%s", line);
	}
	printf("%c\n",line[0]);

}