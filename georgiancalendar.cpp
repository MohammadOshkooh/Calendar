#include "GeorgianCalendar.h"
#include <ctime>

GeorgianCalendar::GeorgianCalendar()
{
    string m[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September",
                    "October", "November", "December"};

    int d[12] = {31, 28, 31, 30, 31, 31, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < 12; ++i) {
        month[i] = m[i];
        days_number_in_month[i] = d[i];
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);

    today = ltm->tm_mday;
    this_month = 1 + ltm->tm_mon;
    this_year = ltm->tm_year;

    day_number_in_weekday = ltm->tm_wday; // 0,1,2,3,4,5,6
    first_day_month_in_weekday = day_number_in_weekday - (today % 7 - 1);

    if (first_day_month_in_weekday < 0)
        first_day_month_in_weekday += 7;

}
