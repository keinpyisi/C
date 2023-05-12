#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#define COLSIZE 16
#define TBLSIZE 256

#define H_PRT 0x02
#define C_PRT 0x01

void dump(char* title, unsigned char* staddr, int offset, int dsize, char opt);
void dump_0(unsigned char *staddr, int dsize);

int main(void) {

//Step 0
/*
		unsigned char staddr[TBLSIZE];
		for (int cnt = 0; cnt < TBLSIZE; cnt++) {
			staddr[cnt] = cnt;
		}
		printf("256 Words \n");
		dump_0(staddr, 256);

		printf("100 Words \n");
		dump_0(staddr, 100);
*/



	FILE* fp;
	unsigned char buffer[16];
	int dsize;
	char name[] = "s-jis2.txt";
	//char name[] = "test.txt";

	/* Open file for both reading and writing */
	fp = fopen(name, "rb");

	if (fp != NULL) {
		/* Read and display data */
		//Read Dsize Every Time
		while((dsize = fread(buffer, sizeof(char), sizeof(buffer), fp)) >0)
		 {
			dump(name, buffer, 0, dsize, C_PRT);
		}
		fclose(fp);
	}
	else {
		unsigned char bin_data[512];
		unsigned char asc_data[] = "01234567809 ABCあいうえおかきくけこDEFGHIJKLMNOPQRSTUVWXYZ 漢字表示のテスト abcdefghijklmnopqrstuvwxyz01234567809ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";

		//Filling With Dummy Data
		for (int filcnt = 0; filcnt < 512; filcnt++) {
			bin_data[filcnt] = filcnt & 0xff;
		}

		dump("Have ASCII", asc_data, 0, strlen(asc_data), H_PRT + C_PRT);
		dump("Have BINARY", bin_data, 0, 512, C_PRT);
	}
	

	return 0;
}


void dump(char* title, unsigned char *staddr, int offset, int dsize, char opt) {
/*
	char *title = タイトル文字列へのポインタで、最初の1回だけ実行します。
	unsigned char *staddr = ダンプをするバッファへのポインタ
	int offset = バッファポインタからオフセットで、最初の1回だけ、staddrに加算しておきます。
	int dsize = ダンプをするバイト数
	char opt = オプション (ヘッダ表示のオン/オフ、文字列表示のオン/オフ)
	*/

	int bytecnt = 0;
	int col;
	static int address;
	int temp;
	static unsigned char ch;
	static unsigned char sjis1;


	//printf("%s \n\n",title);
	

	//Printing Address
	while (bytecnt < dsize) {

		//If Sjis have, its means that there is a kanji coming
		if (sjis1 != NULL) {
			printf("%c%c\n",  sjis1, staddr[bytecnt]);

		}
		if (address % 16 == 0) {
			//Printing Header
			printf("\n");
			printf("  Addr     0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E");
			printf("\n");
			printf("-------- ---- ---- ---- ---- ---- ---- ---- ----     ----------------");
			printf("\n");

		}
		
		//Address
		printf("  %07X0", address);
		printf(" ");

	
		temp = bytecnt;
		for (col = 0; col < COLSIZE; col++) {

			if (bytecnt < dsize) {
				//Printing HEX
				printf("%02X", staddr[bytecnt]);
				
				bytecnt = bytecnt + 1;
			}
			else {
				printf("  ");
			}

			if (col % 2 != 0) {
				printf(" ");
			}
		}
		printf("   ");

		////Printing Words
		//Reseting bytecnt to the first word of the row
		bytecnt = temp;
		
		for (col = 0; col < COLSIZE; col++) {
			//If there is sjis
			if (sjis1 != NULL) {
				printf(" ");
				sjis1 = NULL;
				//Since we printed kanji we have to adjust the place again
				bytecnt += 1;
				col += 1;
			}

			if (bytecnt < dsize) {
				
				//2 byte Kanji Check
				if(((ch = staddr[bytecnt])>=0x81 && ch<=0x9F) || (ch>= 0xE0 && ch<= 0xEF) ){
					//Print Until the last -1
					if (col< (COLSIZE - 1)) {
							
							printf("%c%c", ch, staddr[bytecnt + 1]);
							//Since there is bytecnt+1 we have to adjust the place again
							bytecnt += 1;
							col += 1;
						
					}
					//Save Last Char (1Byte <-Save this +1Byte Kanji)
					else {
						
						sjis1 = ch;
					}
					
				}
				//Just CHecking Word if 1 byte kanji print
				else if (ch >= ' ' && ch < 0x7f ||
					ch >0xA1 && ch <= 0xDF)
				{
					printf("%c", ch);
				}
				else {
					printf(".");
				}
			

				bytecnt = bytecnt + 1;
			}
			else {
				printf(" ");
			}

		}
		if (sjis1 == NULL) {
			printf("\n");
		}
		address = address + 1;
	}
	

	
}

//void dump_0(unsigned char *staddr,int dsize) {
//
//	int bytecnt = 0;
//	int col;
//
//	while (bytecnt < dsize) {
//
//		for (col = 0; col < COLSIZE; col++) {
//			
//			if (bytecnt < dsize) {
//
//				printf("%02X", staddr[bytecnt]);
//				printf(" ");
//				bytecnt = bytecnt + 1;
//			}
//			else {
//				printf("%s%s%s", " ", " ", " ");
//			}
//		}
//		printf("\n");
//
//	}
//
//
//}