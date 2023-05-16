#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#define COLSIZE 16
#define TBLSIZE 256

#define H_PRT 0x02
#define C_PRT 0x01
#define HELP_PRT 0x03
#define A_PRT 0x04



typedef struct {
	char* infileName;
	char h_prt;
	char c_prt;
	char help_prt;
	char offset;
	char address;
}opts_t;


void dump(unsigned char* staddr, int dsize, opts_t* opts);
int opts_analisys(int argc, char* argv[], opts_t* opts);
void print_help();

int main(int argc,char *argv[]) {

	int result;
	opts_t opts;
	//Init OPTS
	opts.c_prt = NULL;
	opts.help_prt = NULL;
	opts.h_prt = NULL;
	opts.infileName = NULL;
	opts.offset = NULL;
	opts.address = 0;
	//Checking User Command
	result = opts_analisys(argc, argv, &opts);


	FILE* fp;
	/* Open file for both reading and writing */
	if (opts.infileName != NULL) {
		
		fp = fopen(opts.infileName, "rb");
	}
	else {
		//Reading From Stdin ( C pipeline but more efficient)
		fp = stdin;
	
	}


	//If there is No Command or pressed helped , Help show
	if (result!=0 || opts.help_prt == HELP_PRT) {
		fprintf(stderr, "%s \n", "Command Not Found", 30);
		fprintf(stderr, "%s \n", "If No File , Please Specify 16 char String: ", 30);
		print_help();
	}
	else {
		
		unsigned char buffer[16];
		int dsize;
		
		if (fp != NULL) {
			//Seek Via Command if /o is added
			fseek(fp, opts.offset, SEEK_SET);
		
			
			/* Read and display data */
			//Read Dsize Every Time
			while ((dsize = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0)
			{
				dump(buffer, dsize, &opts);
			}
			if (opts.infileName != NULL) {
				fclose(fp);
			}
			
		}
		else {
			//No File Found on Reading and Show Help
			fprintf(stderr, "%s \n", "No File Found", 30);
			print_help();
			
		}

	}


	return 0;
}
//Help Function
void print_help() {
	printf("Usages - <Filename.txt> <options>\n");
	printf("Options- \n");
	printf("/h   Add Header via 16byte \n");
	printf("/c   Add User Understandable Characters \n");
	printf("/o[=]1000  See File from the point of 1000 \n");
	printf("/a[=]1000  Show Absolute Memory Bank of 1000 \n");
	printf("/? Show Help\n");
	printf("Non Command  Show Help \n");
}
//Analyzing Command and if the command exist return 0 , no command return 1
int opts_analisys(int argc,char* argv[], opts_t* opts) {
	int flag = 1;
	for (int cnd = 1; cnd < argc; cnd++) {
		
		//If Command Start with /
		if ((*argv[cnd]) == '/') {
			
			//If Command start with char after /
			switch (*(argv[cnd] + 1)) {
				//Header Show and 16 bit
				case 'h':
					
					opts->h_prt = H_PRT;
					flag = 0;
					break;
				//User Known Character Show 
				case 'c':
					
					opts->c_prt = C_PRT;
					flag = 0;
					break;
				//Start Reading File from /o Bit.
				case 'o':
					//If There is Digit on after /o2000
					if(*(argv[cnd] + 2) != '=' && *(argv[cnd] + 2) > 0) {

						opts->offset = strtol((argv[cnd] + 2), NULL, 16);
						flag = 0;
					}
					//If there is Digit on after /o=2000
					else if (*(argv[cnd] + 3)!= '=' && *(argv[cnd] + 3) > 0) {

						opts->offset = strtol((argv[cnd] + 3), NULL, 16);
						flag = 0;
					}
					// No Digit Found -> Error
					else {
						flag = 1;
					}

					break;
				//Show Absolute Bank
				case 'a':

					opts->address = A_PRT;
					flag = 0;
					break;
				//No Command or Error Show Help
				default: 
					opts->help_prt = HELP_PRT;
					flag = 1;
					break;
			}

		}
		else {
			//Read Only One File. Another File found = Return Flag 1 -> Cant be used with stdin
			/*if (opts->infileName!= NULL) {
				flag = 1;
			}
			else {
				opts->infileName = argv[cnd];
				flag = 0;
			}*/
			//Just Getting File From Command
			opts->infileName = argv[cnd];
			flag = 0;

		}
		
		
	}
	//Return Error Flag . 0= Working Properly, 1= Error
	return flag;
}

void dump( unsigned char* staddr,int dsize, opts_t* opts) {
	/*
	
		unsigned char *staddr = ダンプをするバッファへのポインタ
		int dsize = ダンプをするバイト数
		opts_s *opts = オプション (ヘッダ表示のオン/オフ、文字列表示のオン/オフ)
		*/

	int bytecnt = 0;
	int col;
	static int address;
	int temp;
	static unsigned char ch;
	static unsigned char sjis1;
	static int row;
	static int flag;

	//If There is /a flag show Address
	if (flag==0 && opts->address == A_PRT) {
		//Show Address with Offset
		address =address+ opts->offset;
		//First Time Checking and working only
		flag = 1;
	}
	
	//Printing Address
	while (bytecnt < dsize) {

		//If Sjis have, its means that there is a kanji coming
		if (sjis1 != NULL) {
			printf("%c%c\n", sjis1, staddr[bytecnt]);

		}
		
		//If Option Have H_PRT
		if (opts->h_prt == H_PRT) {
			//Only First Time
			if (row == 0) {
				//If Option Have C_PRT
				if (opts->c_prt ==C_PRT) {
					//if options have /a
					if (opts->address == A_PRT) {
						printf("\n");
						printf("  Addr     ");
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("-------- ---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
					else {
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}

				}
				else {
					//if options have /a
					if (opts->address == A_PRT) {
						printf("\n");
						printf("  Addr     ");
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("-------- ---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
					else {
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
				}

			}

		}
		else {

			if (row % 16 == 0) {
				//Print 1 times in 16 count
				//If opt have only C_PRT
				if (opts->c_prt == C_PRT) {
					//if options have /a
					if (opts->address == A_PRT) {
						printf("\n");
						printf("  Addr     ");
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("-------- ---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
					else {
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
				

				}
				//If opt have H_PRT Only
				else {
					//if options have /a
					if (opts->address == A_PRT) {
						printf("\n");
						printf("  Addr     ");
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("-------- ---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
					else {
						printf("0 1  2 3  4 5  6 7  8 9  A B  C D  E F     0 2 4 6 8 A C E ");
						printf("\n");
						printf("---- ---- ---- ---- ---- ---- ---- ----     ----------------");
						printf("\n");
					}
				}
			}
		}
	
		//	//if options have /a print Memory Address here
		if (opts->address == A_PRT) {

			printf("  %08x", address);
			printf(" ");
		}
		


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
		//If Opt have H_PRT print characters but not C_PRT
		if (opts->h_prt == H_PRT) {
			if ((opts->c_prt)!= C_PRT) {
				printf("\n");
			}


		}


		////Printing Words
		//Reseting bytecnt to the first word of the row
		//If Opt have CPRT print characters
		if (opts->c_prt==C_PRT) {
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
					if (((ch = staddr[bytecnt]) >= 0x81 && ch <= 0x9F) || (ch >= 0xE0 && ch <= 0xEF)) {
						//Print Until the last -1
						if (col < (COLSIZE - 1)) {

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
			//If there is no Temp chara for kanji, skip a line
			if (sjis1 == NULL) {
				printf("\n");
			}
		}
		//New Memory Address
		address = address + 16;
		//New Row
		row = row + 1;
	}



}