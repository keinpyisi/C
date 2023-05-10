//KEINPYI SI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MONTH 12
#define WEEKS 6
#define N_WEEK 7
#define MAX_HOLI_TBL 4
#define SPRING_EQ 0
#define FALL_EQ 1
#define BIRTH_MARK 0x80 // 誕生日マーク
#define TRANS_MARK 0x40 // 振替祝日マーク
#define HOLI_MARK 0x20 // 祝日マーク
#define MAX_COL 4
#define COLOR_RED		"\033[31m"	// 赤色
#define COLOR_BLUE		"\033[34m"	// 青色
#define COLOR_WHITE		"\033[37m"	// 白色
#pragma warning(disable:4996)

enum  M_LIST { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
enum W_LIST { SUN, MON, TUE, WED, THU, FRI, SAT };
//Per month day
char mdays[N_MONTH] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//Calender Table
char cal_tbl[N_MONTH][WEEKS][N_WEEK];

// 祝日のデータテーブル
char holidays[N_MONTH][MAX_HOLI_TBL] = {
		{1,-2, 0,0},		//  1月、元旦、成人の日
		{11,23,0,0},		//  2月、建国記念日、令和天皇誕生日
		{21,0,0,0},		//  3月、春分の日(計算で算出)
		{29,0,0,0},		//  4月、昭和の日
		{3,4,5,0},		//  5月、憲法記念日、みどりの日、子供の日
		{ 0,0,0,0},		//  6月、なし
		{-3,0,0,0},		//  7月、海の日
		{11,0,0,0},		//  8月、山の日
		{-3,23,0,0},	//  9月、敬老の日、秋分の日(計算で算出)
		{-2,0,0,0},		// 10月、体育の日
		{3,23,0,0},		// 11月、文化の日、勤労感謝の日
		{ 0,0,0,0}		// 12月、なし(23日の平成天皇誕生日はなし)
};

void init();
void make_calendar(char cal_tbl[N_MONTH][WEEKS][N_WEEK], int youbi);
void print_cal(char cal_tbl[N_MONTH][WEEKS][N_WEEK], int yobi, int year);
int CumulativeDays(int year);
int leap_year(int year);
void put_char(char* space, int num);
void vernal_autumnal(int year);





int main(void) {

	int year;
	printf("Enter A Year To Show: ");
	scanf("%d", &year);
	
	//Initialze Calender
	init();

	/* Calculating Days Up to Last Year  */
	int cumulativedays = CumulativeDays(year);

	/*If Year is leap year , */
	mdays[FEB] = leap_year(year) ? 29 : 28;

	/* Autumn Day */
	vernal_autumnal(year);

	/* Make Calender */
	make_calendar(cal_tbl, (cumulativedays + 1) % 7);

	/* Show Calender*/
	print_cal(cal_tbl, (cumulativedays + 1) % 7,year);

	return 0;
}


void init() {
	int cnt1, cnt2, cnt3;
	/* Init Calender to 0 */
	for (cnt1 = 0; cnt1 < N_MONTH; cnt1++) {
		for (cnt2 = 0; cnt2 < WEEKS; cnt2++) {
			for (cnt3 = 0; cnt3 < N_WEEK; cnt3++) {
				cal_tbl[cnt1][cnt2][cnt3] = 0;
			}
		}
	}
}

void make_calendar(char cal_tbl[N_MONTH][WEEKS][N_WEEK], int youbi) {
	int month, day, line, holiday, monday;

	for (month = JAN; month <= DEC; month++) {
		day = 1; //Day Will be 1
		line = 0; // Line 0
		holiday = 0; //Count Holiday
		monday = 0; //Count Monday

		//Getting Day of the month
		while (day <= mdays[month]) {

			//Counting Monday
			if (youbi == MON) {
				monday++;
			}
			cal_tbl[month][line][youbi] |= day;

			//If Holiday
			if (holidays[month][holiday] == day) {
				//Add Holiday Mark
				cal_tbl[month][line][youbi] |= HOLI_MARK;
				//If Sunday or Consective Holiday
				if (youbi == SUN || cal_tbl[month][line][youbi] & TRANS_MARK) {
					//Make Next Day a Holiday
					cal_tbl[month][line][youbi + 1] |= TRANS_MARK;
				}

				//If Wednedday and The 2nd front of Wed is Holiday
				else if (youbi >= WED && cal_tbl[month][line][youbi - 2] & HOLI_MARK) {

					cal_tbl[month][line][youbi - 1] |= HOLI_MARK;
				}
				//If Wednedday and The 2nd back of Wed is Holiday
				else if (youbi >= WED && cal_tbl[month][line][youbi + 2] & HOLI_MARK) {

					cal_tbl[month][line][youbi + 1] |= HOLI_MARK;
				}

				holiday++;  // Count Holiday
			}
			else {
				//If Today is Monday , Happy Monday 
				if (youbi == MON && monday == abs(holidays[month][holiday])) {

					cal_tbl[month][line][youbi] |= HOLI_MARK;
					holiday++;
				}
			}
			day++; // Next Day
			youbi++; // Next Youbi
			if (youbi > SAT) // If Today is Sat
			{
				youbi = SUN; // Make it Sunday

				line++; //Next Line
			}
		}
	}
}

void print_cal(char cal_tbl[N_MONTH][WEEKS][N_WEEK], int yobi,int year) {
	int month, line, dow, cnt;
	int col = MAX_COL;

	char buf[64];
	int len = 0;
	char* space = " ";
	int val = 0;

	for (month = JAN; month <= DEC; month += col) {

		for (line = -2; line < WEEKS; line++) {

			for (col = 0; col < MAX_COL; col++) {
				// Show Monthly
				if (line == -2) {
					printf(COLOR_WHITE);
					sprintf(buf, "%d/%d", year, month + col + 1);
					printf("%s", buf);

					len = strlen(buf);
					// -1 Adjusting...
					val = 4 * N_WEEK - len - 1;
					//Putting Space 
					put_char(space, val);

				}
				else if (line == -1) {
					// Show youbi
					for (cnt = 0; cnt <= WEEKS; cnt++)
					{
						//Header
						switch (cnt)
						{
						case SUN:
							printf(COLOR_RED);
							printf("  日");
							break;
						case MON:
							printf(COLOR_WHITE);
							printf("  月");
							break;
						case TUE:
							printf("  火");
							break;
						case WED:
							printf("  水");
							break;
						case THU:
							printf("  木");
							break;
						case FRI:
							printf("  金");
							break;
						case SAT:
							printf(COLOR_BLUE);
							printf("  土");
							break;
						default:
							break;
						}
					}
				}
				else {
					//Showing Day
					for (dow = 0; dow <= SAT; dow++) {


						printf(COLOR_WHITE);
						//Sunday is Red
						if (dow == SUN) {
							printf(COLOR_RED);
						}
						//Sat is Blue
						else if (dow == SAT)
						{
							printf(COLOR_BLUE);
						}

						//Skipping 0
						if (cal_tbl[month + col][line][dow] == 0) {
							printf("    ");
						}
						else
						{
							//If Holiday
							if (cal_tbl[month + col][line][dow] & HOLI_MARK)
							{
								printf(COLOR_RED);
								if (cal_tbl[month + col][line][dow] & TRANS_MARK) {
									//If Consective Holiday
									printf("%4d", cal_tbl[month + col][line][dow] ^ HOLI_MARK ^ TRANS_MARK);
								}
								else {
									//If Holiday
									printf("%4d", cal_tbl[month + col][line][dow] ^ HOLI_MARK);
								}
							}
							//Fixed Holiday
							else if (cal_tbl[month + col][line][dow] & TRANS_MARK)
							{
								//If Consective Holiday
								if (cal_tbl[month + col][line][dow] & HOLI_MARK) {
									printf("%4d", cal_tbl[month + col][line][dow] ^ HOLI_MARK ^ TRANS_MARK);
								}
								else {
									printf("%4d", cal_tbl[month + col][line][dow] ^ TRANS_MARK);
								}
							}
							//Normal Day
							else
							{
								printf("%4d", cal_tbl[month + col][line][dow]);
							}
						}
					}
				}
				printf("    ");
			}
			printf("\n");
		}
		printf("\n");
	}

	printf(COLOR_WHITE);
}

int CumulativeDays(int year) {
	int total;
	year = year - 1; //Move to Past Year
	total = year * 365;
	total += year / 4;
	total -= year / 100;
	total += year / 400;
	return total;
}


int leap_year(int year) {
	int result = 0; //Not Leap
	if (year % 4 == 0) {
		result = 1; //Leap
	}
	if (year % 100 == 0) {
		result = 0; // Not Leap
	}
	if (year % 400 == 0) {
		result = 1; //Leap
	}
	return result;
}

//How Many Space will be Printed
void put_char(char* space, int num) {
	int cnt;
	for (cnt = 0; cnt <= num; cnt++) {
		printf("%s", space);
	}
}

/* Calculating Autumn Holiday... Just Copy Paste */
void vernal_autumnal(int year) {

	int springEQ;	// 求める春分の日
	int fallEQ;		// 求める秋分の日

	if (year <= 1899) {
		springEQ = (int)(19.8277 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
		fallEQ = (int)(22.2588 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
	}
	else if (year >= 1900 && year <= 1979) {
		springEQ = (int)(20.8357 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
		fallEQ = (int)(23.2588 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
	}
	else if (year >= 1980 && year <= 2099) {
		springEQ = (int)(20.8431 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
		fallEQ = (int)(23.2488 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
	}
	else if (year >= 2100) {
		springEQ = (int)(21.851 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
		fallEQ = (int)(24.2488 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
	}
	holidays[MAR][SPRING_EQ] = springEQ;	// 春分の日を入れる
	holidays[SEP][FALL_EQ] = fallEQ;		// 秋分の日を入れる
}
