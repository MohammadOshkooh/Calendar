#include "PersianCalendar.h"
#include <ctime>

PersianCalendar::PersianCalendar()
{
    string m[12] = {"Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar",
                    "Dey", "Bahman", "Esfand"};

    int d[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

    for (int i = 0; i < 12; ++i) {
        month[i] = m[i];
        days_number_in_month[i] = d[i];
    }


    time_t now = time(0);
    tm *ltm = localtime(&now);

    today = ltm->tm_mday;
    this_month = 1 + ltm->tm_mon;
    this_year = ltm->tm_year;
    int a[3];
    gregorianToPersian(this_year - 100 + 2000, this_month, today, a);
    today = a[2];
    this_month = a[1];
    this_year = a[0];
    day_number_in_weekday = ltm->tm_wday; // 0,1,2,3,4,5,6
    first_day_month_in_weekday = day_number_in_weekday - (today % 7 - 1);

    if (first_day_month_in_weekday < 0)
        first_day_month_in_weekday += 7;
}

int* PersianCalendar::gregorianToPersian(int gregorianYear, int gregorianMonth, int gregorianDay, int PersianDateOut[]) {
    int days;
    {
        int gregorianYear2;
        if (gregorianMonth > 2)
            gregorianYear2 = gregorianYear;
        else
            gregorianYear2 = gregorianYear + 1;

        int g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        days = 355666 + (365 * gregorianYear) + ((int) ((gregorianYear2 + 3) / 4)) -
               ((int) ((gregorianYear2 + 99) / 100)) + ((int) ((gregorianYear2 + 399) / 400)) + gregorianDay +
               g_d_m[gregorianMonth - 1];
    }
    int jy = -1595 + (33 * ((int) (days / 12053)));
    days %= 12053;
    jy += 4 * ((int) (days / 1461));
    days %= 1461;
    if (days > 365) {
        jy += (int) ((days - 1) / 365);
        days = (days - 1) % 365;
    }
    PersianDateOut[0] = jy;
    if (days < 186) {
        PersianDateOut[1]/*jm*/ = 1 + (int) (days / 31);
        PersianDateOut[2]/*jd*/ = 1 + (days % 31);
    } else {
        PersianDateOut[1]/*jm*/ = 7 + (int) ((days - 186) / 30);
        PersianDateOut[2]/*jd*/ = 1 + ((days - 186) % 30);
    }
    return PersianDateOut;
}
