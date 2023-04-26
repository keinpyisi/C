#include <stdio.h>
#define col 8
#define row 8

int main(void) {

	char tb[col][row];
	int temp = 0;
	
	for (int x = 0; x < row; x++) {

		
	
		for (int y = 0; y < col; y++) {
			temp = temp + 1;
			tb[x][y] = temp;
			printf("%3d", temp);
			
				
		}
		printf("\n");
	
	}
	

}
