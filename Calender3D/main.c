//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define DAY 31
//#define BIRTH_MARK 0x80 // 誕生日マーク
//#define TRANS_MARK 0x40 // 振替祝日マーク
//#define HOLI_MARK 0x20 // 祝日マーク
//#define WEEKS 6 // 最大行数の定義
//#define holi_month 10
//#define holi_day 10
//#define BIRTH_MARK 0x80 // 誕生日マーク
//#define TRANS_MARK 0x40 // 振替祝日マーク
//#define HOLI_MARK 0x20 // 祝日マーク
//
//enum M_LIST { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, N_MONTH };
//char mdays[N_MONTH] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//enum W_LIST { SUN, MON, TUE, WED, THU, FRI, SAT, N_WEEK };
//
//char cal_tbl[N_MONTH][WEEKS][N_WEEK];
//char* getDay(int index);
//char* getMonth(int month);
//int totaldays(int year);
//int leapYear(int year);
//void makeCalender(int year);
//void showCalender(int year);
//void red();
//void reset();
//void blue();
//void cyan();
//int holiday(int month, int day);
//int count_monday_holiday(int mondaycount, int month);
//int haruday(int month, int day);
//int birthday(int month, int day);
//
//int main(void) {
//    int year = 2015;
//    makeCalender(year);
//    showCalender(year);
//  
//
//}
//
//
//void showCalender(int year) {
//   
//    int totalyear = totaldays(year) + 1;
//
//    //If Else Leap Year
//    mdays[FEB] = leapYear(year) ? 29 : 28;
//   
//    //Mon , Tues or Wed
//    int dayyoubi = totalyear % 7;
//
//    //Getting Birthday
//   /* int birthday = totaldays(year) + mdays[JAN] + mdays[FEB] + mdays[MAR] + 5;*/
//    printf("Year : %4d Calender \n", year);
//    for (int month = JAN; month <= DEC; month++) {
//
//        // 月初め
//        int day = 1;
//        int count = 1;
//        int row = 0;
//        int controller = 0;
//
//      
//        printf("%4s", getMonth(month));
//        printf("\n");
//        for (int name = 0; name < N_WEEK; name++) {
//            if (name == SUN) {
//                red();
//            }
//            if (name == SAT) {
//                blue();
//            }
//            printf("%4s", getDay(name));
//            reset();
//        }
//
//        /*・行を0にする*/
//        printf("\n");
//        while (day <= mdays[month]) {
//            //Seperating 0 and Space
//            if (count <= dayyoubi) {
//               
//                if (cal_tbl[month][row][controller] == 0) {
//                    printf("%4c", ' ');
//                }
//                //Changing Field in a row
//                controller += 1;
//            }
//            //Adding Day Numbers on a Row 
//            if (count > dayyoubi) {
//                //If Print Pointer is Sat or Sun 
//            /*    if (dayyoubi == SUN) {
//                    red();
//                }
//                if (dayyoubi == SAT) {
//                    blue();
//                }*/
//                //If Holiday , Remove Holi Mark Bit
//                if ((cal_tbl[month][row][controller] & HOLI_MARK) != 0) {
//                    red();
//                    printf("%4d", cal_tbl[month][row][controller] & ~HOLI_MARK & ~TRANS_MARK);
//                }
//                else if ((cal_tbl[month][row][controller] & BIRTH_MARK) != 0) {
//                    cyan();
//                    printf("%4d", cal_tbl[month][row][controller] &= ~BIRTH_MARK  );
//                }
//                else {
//                    printf("%4d", cal_tbl[month][row][controller] );
//                }
//              
//                reset();
//                //For Moving Print Pointer 
//                dayyoubi += 1;
//               
//                day = day + 1;
//                //Changing Field in a row
//                controller += 1;
//
//            }
//            //Next Line
//            if (count % 7 == 0) {
//               printf("\n");
//                //Reseting To Sunday After One Row 
//                dayyoubi = SUN;
//                if (row < 7) {
//                    row = row + 1;
//                }
//
//            }
//            //Controlling A Row... 1 Row = 7 Fields(Controller)
//            if (controller > 6) {
//                controller = 0;
//            }
//            count = count + 1;
//
//        }
//        printf("\n");
//    }
//
//}
//
//
//
//
//void makeCalender(int year) {
//  
//    int totalyear = totaldays(year)+1;
//    //If Else Leap Year
//    mdays[FEB] = leapYear(year) ? 29 : 28;
//  
//    //Mon , Tues or Wed
//    int dayyoubi = totalyear % 7;
//  
//    for (int month = JAN; month <= DEC; month++) {
//        // 月初め
//        int day = 1;
//        int count = 1;
//        int row = 0;
//        int controller = 0;
//
//        int holicount = 0; // 祝日のカウントをクリア
//        int moncount = 0; // 月曜日のカウントをクリア
//  
//            while (day <= mdays[month]) {
//                /*・行を0にする*/
//                if (count <= dayyoubi) {
//                    cal_tbl[month][row][controller] = 0;
//                    controller += 1;
//                }
//                
//                if (count > dayyoubi) {
//                    if (dayyoubi == MON) {
//                        moncount += 1;
//                    }
//                   
//                    cal_tbl[month][row][controller] = day;
//
//                    if (birthday(month, cal_tbl[month][row][controller]) == 1) {
//                        cal_tbl[month][row][controller] |= BIRTH_MARK;
//                    }
//
//                    //If Holiday , Add Holi Mark Bit
//                    if (holiday(month, cal_tbl[month][row][controller])== 1) {
//                        cal_tbl[month][row][controller] |= HOLI_MARK;
//                        if (dayyoubi == SUN) {
//                            cal_tbl[month][row][controller] |= TRANS_MARK;
//                        }
//                        holicount += 1;
//                    }
//                    //If Holiday , Add Holi Mark Bit
//                    else if (count_monday_holiday(moncount,month) == 1) {
//                       //Flag For One Time
//                        moncount += 1;
//                        cal_tbl[month][row][controller] |= HOLI_MARK;
//                        if (dayyoubi == SUN) {
//                            cal_tbl[month][row][controller] |= TRANS_MARK;
//                        }
//                        holicount += 1;
//                    }
//                    //If Holiday , Add Holi Mark Bit
//                    else if (haruday(month, cal_tbl[month][row][controller])==1) {
//                        cal_tbl[month][row][controller] |= HOLI_MARK;
//                        if (dayyoubi == SUN) {
//                            cal_tbl[month][row][controller] |= TRANS_MARK;
//                        }
//                        holicount += 1;
//                    }
//                    dayyoubi += 1;
//                    day = day + 1;
//                    controller += 1;
//
//                   
//                }
//                if (count % 7 == 0) {
//                   //Reseting To Sunday After One Row 
//                   dayyoubi = SUN;
//                   if (row < 7) {
//                       row = row + 1;
//                   }
//                  
//                }
//                if (controller > 6) {
//                    controller = 0;
//                }
//                count = count + 1;
//
//                
//                
//            }
//            moncount = 0;
//    }
//  
//}
//
//int totaldays(int year) {
//
//    int findyear = year - 1;
//    //累積日数
//    int totalday = findyear * 365;
//    totalday = totalday + (findyear / 4);
//    totalday = totalday - (findyear / 100);
//    totalday = (findyear / 400) + totalday;
//    return totalday;
//
//}
//
////Calculating Leap Year Step by Step
//int leapYear(int year)
//{   
//  
//    int leap=0;
//    if (year % 4 == 0) {
//
//        if (year % 100 == 0) {
//            if (year % 400 == 0) {
//                //Leap Year
//                leap= 1;
//            }
//            //Not Leap
//            leap= 0;
//        }
//        //Leap Year
//        leap= 1;
//    }
//    else {
//        //Not Leap Year
//        leap= 0;
//    }
//    return leap;
//}
//
//void red() {
//    printf("\033[1;31m");
//}
//void reset() {
//    printf("\033[0m");
//}
//void blue() {
//    printf("\033[1;34m");
//}
//
//void cyan() {
//    printf("\033[0;36m");
//}
//
//
//int birthday(int month, int day) {
//    month += 1;
//    if (month == 4 && day == 5) {
//        return 1;
//    }
//    return 0;
//}
//
//int count_monday_holiday(int mondaycount , int month) {
//    month += 1;
//    if (month == 1 && mondaycount == 2) {
//        return 1; //成人の日
//    }
//    else if (month == 7 && mondaycount == 3) {
//        return 1; //海の日
//    }
//    else if (month == 9 && mondaycount == 3) {
//        return 1; //敬老の日
//    }
//    else if (month == 10 && mondaycount == 2) {
//        return 1; //スポーツの日
//    }
//    else {
//        return 0;
//    }
//
//
//}
//
//int haruday(int month, int day) {
//    if (month == 3 && day == 20) {
//        return 1;
//    }
//    else {
//        return 0;
//    }
//}
//
//int holiday(int month, int day) {
//    month += 1;
//    if (month == 1 && day == 1) {
//        return 1;
//    }
//    else if (month == 2) {
//        if (day == 11) {
//            return 1;
//        }
//        else if (day == 23) {
//            return 1;
//        }
//        else {
//            return 0;
//        }
//    }
//    else if (month == 4 && day == 29) {
//        return 1;
//    }
//    else if (month == 5) {
//        if (day == 3) {
//            return 1;
//        }
//        else if (day == 4) {
//            return 1;
//        }
//        else if (day == 5) {
//            return 1;
//        }
//        else {
//            return 0;
//        }
//    }
//    else if (month == 8) {
//        if (day == 11) {
//            return 1;
//        }
//        else {
//            return 0;
//        }
//    }
//    else if (month == 11) {
//        if (day == 3) {
//            return 1;
//        }
//        else if (day== 23) {
//            return 1;
//        }
//        else {
//            return 0;
//        }
//    }
//    else {
//        return 0;
//    }
//
//}
//
//
////Getting Day Name
//char* getDay(int index) {
//    switch (index) {
//    case SUN:
//        return "日";
//        break;
//    case MON:
//        return "月";
//        break;
//    case TUE:
//        return "火";
//        break;
//    case WED:
//        return "水";
//        break;
//    case THU:
//        return "木";
//        break;
//    case FRI:
//        return "金";
//        break;
//    case SAT:
//        return "土";
//        break;
//
//    }
//}
//
////Getting Month Name
//char* getMonth(int month) {
//    switch (month) {
//    case JAN:
//        return "JANUARY";
//        break;
//
//    case FEB:
//        return "FEBURARY";
//        break;
//
//    case MAR:
//        return "MARCH";
//        break;
//
//    case APR:
//        return "APRIL";
//        break;
//
//    case MAY:
//        return "MAY";
//        break;
//
//    case JUN:
//        return "JUNE";
//        break;
//
//    case JUL:
//        return "JULY";
//        break;
//
//    case AUG:
//        return "AUGUST";
//        break;
//
//    case SEP:
//        return "SEPTEMBER";
//        break;
//
//    case OCT:
//        return "OCTOBER";
//        break;
//
//    case NOV:
//        return "NOVEMBER";
//        break;
//
//    case DEC:
//        return "DECEMBER";
//        break;
//
//    default:
//        return "No Months";
//        break;
//    }
//
//}
