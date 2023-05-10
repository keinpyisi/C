// C program to store temperature of two cities of a week and display it.
#include <stdio.h>

#define DAY 31
#define BIRTH_MARK 0x80 // 誕生日マーク
#define TRANS_MARK 0x40 // 振替祝日マーク
#define HOLI_MARK 0x20 // 祝日マーク

enum M_LIST { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC,N_MONTH };
char mdays[N_MONTH] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
enum W_LIST { SUN, MON, TUE, WED, THU, FRI, SAT, N_WEEK };
char* getMonth(int month);
char* getDay(int index);
int calculateYear(int year);
int leap_step1(int year);
int leap_step2(int year);
int leap_step3(int year);

int totaldays(int year);
void red();
void reset();
void blue();
int main()
{

    int calender[N_MONTH][DAY];


    //Starting Point of the year
    int startpoint = totaldays(2022);
    int days = 1;

    //Loop 12 Months In A Year
    for (int month = JAN; month < N_MONTH; month++) {
      
        printf("%d年%d月\n", 2022,month+1);
        //Adding Index of the Day
        for (int index = SUN; index < N_WEEK; index++) {
            reset();
            if (index == SUN) {
                red();
                printf("%3s ", getDay(index));
            }
            else if (index == SAT) {
                blue();
                printf("%3s ", getDay(index));
            }
            else {
                printf("%3s ", getDay(index));
            }
        
        }

        printf("\n");
        //Making Starting Point of the per year 1日1月.
        for (int da = 0; da < startpoint; da++) {
            printf("    ");
        }
       
        //Adding Days
            for (int day = 0; day < mdays[month]; day++)
            {
                calender[month][day] = days;
                reset();
                if (startpoint == 6) {
                    blue();
                    printf("%3d ", calender[month][day]);

                }
                else if (startpoint == 0) {
                    red();
                    printf("%3d ", calender[month][day]);

                }
                else {
                    printf("%3d ", calender[month][day]);

                }
                reset();

                
                //if the start point is less than 7
                if (startpoint  < N_WEEK) {
                    startpoint += 1;
                   
                }
                //if the start point is equal 7
                if (startpoint == N_WEEK) {
                    //Break a line
                    printf("\n");
                    //Move the Pointer to the start point
                    startpoint = 0;
                }
                //Adding Days Up to the month
                days += 1;
                
            }
            //Reset the day to 1 for new month
            days = 1;
            printf("\n\n");

        
    }
    
    return 0;
}

//Getting Day Name
char* getDay(int index) {
    switch (index) {
        case SUN:
            return "日";
            break;
        case MON:
            return "月";
            break;
        case TUE:
            return "火";
            break;
        case WED:
            return "水";
            break;
        case THU:
            return "木";
            break;
        case FRI:
            return "金";
            break;
        case SAT:
            return "土";
            break;
    
    }
}
void red() {
    printf("\033[1;31m");
}
void reset() {
    printf("\033[0m");
}
void blue(){
  printf("\033[1;34m");
}

//Getting Month Name
char* getMonth(int month) {
    switch (month) {
        case JAN:
            return "JANUARY";
            break;

        case FEB:
            return "FEBURARY";
            break;

        case MAR:
            return "MARCH";
            break;

        case APR:
            return "APRIL";
            break;

        case MAY:
            return "MAY";
            break;

        case JUN:
            return "JUNE";
            break;

        case JUL:
            return "JULY";
            break;

        case AUG:
            return "AUGUST";
            break;

        case SEP:
            return "SEPTEMBER";
            break;

        case OCT:
            return "OCTOBER";
            break;

        case NOV:
            return "NOVEMBER";
            break;

        case DEC:
            return "DECEMBER";
            break;

        default:
            return "No Months";
            break;
    }
    
}

int totaldays(int year) {

    //求める年の前年の12/31日までの累積日数
    // 
    //求める年-1に、365日を掛け、累積日数を求める
    int cumulative = (year - 1) + 365;
    //int cumulative = (year) + 365;

    ////// 求める年-1 を4で割った数を、累積日数に足す 
    //    int leap_year = ((year - 1) / 4);
    int leap_year = ((year ) / 4);
    cumulative = cumulative + leap_year;
   /* if (cumulative % 4 == 0) {
        printf("LEAP YEAR \n");
    }*/

    //////求める年-1を100で割った数を、累積日数から引く
    //int normal = ((year - 1) / 100);
    int normal = ((year) / 100);
    cumulative = cumulative - normal;
   /* if (cumulative % 100 == 0) {
        printf("NORMAL YEAR \n");
    }*/

    ////求める年-1を400で割った数を、累積日数に足す 
    //int leap = ((year - 1) / 400);
    int leap = ((year) / 400);
    cumulative = cumulative+ leap;
   /* if (cumulative % 400 == 0) {
        printf("LEAP YEAR \n");
    }*/

    //累積日数に、1を加えると、求める年の1/1日までの日数になる
    //int next_year = cumulative + 1;
    int next_year = cumulative;

    // 求めた累積日数を7で割り余りが曜日
    //(西暦1年1月1日は、月曜日)
    //0 = 日、1 = 月、2 = 火、3 = 水、4 = 木、5 = 金、6 = 土
    int day_here = next_year % 7;
    if (calculateYear(year) > 0) {
        if (day_here > 0) {
            day_here -= 1;
        }
     
        if (day_here == 6) {
            day_here = SUN;
        }
        if (day_here == 0) {
            day_here = SAT;
        }
  
    }
    printf("Start Point of Year %d is %s \n", year, getDay(day_here));
    return day_here;

}


//Calculating Leap Year Step by Step
int calculateYear(int year)
{
    return leap_step1(year);
}

int leap_step1(int year) {
    if (year % 4 == 0) {
        return  leap_step2(year);
    }
    //Not Leap Year
    return 0;
}

int leap_step2(int year) {
    if (year % 100 == 0) {
        return leap_step3(year);
    }
    //Leap Year
    return 1;

}

int leap_step3(int year) {
    if (year % 400 == 0) {
        //Leap Year
        return 1;
    }
    //Not Leap Year
    return 0;
}


