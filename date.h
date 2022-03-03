#include <iostream>
#include <ctime>
using namespace std;

int d, m, y, nowYear, nowMonth, nowDay;

void current_date()
{
    // current date/time based on current system
    time_t now = time(0);

    tm* ltm = localtime(&now);
    // various components of tm structure
    nowYear = 1900 + ltm->tm_year; //tm_year means years since 1900
    nowMonth = 1 + ltm->tm_mon; //tm_mon means months since January
    nowDay = ltm->tm_mday; //tm_mday means day of the month

}

bool isLeap(int y)
{
    if (y % 4 == 0) {
        if (y % 100 == 0) {
            if (y % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

bool validDate(int d, int m, int y)
{
    if ( y>=1000 && y<=3000 ){
        if ( m>=1 && m<=12){
            if ( (m==1||m==3||m==5||m==7||m==8||m==10||m==12) && (d>=1 && d<=31) )
                return true;
            else if ( (m==4||m==6||m==9||m==11) && (d>=1 && d<=30 ))
                return true;
            else if (isLeap(y) && d>=1 && d<=29 )
                return true;
            else if (!isLeap(y) && d>=1 && d<=28 )
                return true;
            else
                return false;
        }else
            return false;
    }else
        return false;
}

bool check_manufacture_date(int d, int m, int y)
{
    current_date();
    if (y<nowYear){
        return true;
    }else if ( y==nowYear && m<nowMonth ){
        return true;
    }else if ( y== nowYear && m==nowMonth && d<=nowDay)
        return true;
    else
        return false;
}

bool check_expired_date(int d, int m, int y)
{
    current_date();
    if (y>nowYear){
        return true;
    }else if ( y==nowYear && m>nowMonth ){
        return true;
    }else if ( y== nowYear && m==nowMonth && d>=nowDay)
        return true;
    else
        return false;
}

