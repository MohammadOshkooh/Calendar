#ifndef PERSIANCALENDAR_H
#define PERSIANCALENDAR_H

#include "Calendar.h"

class PersianCalendar : public Calendar
{
public:
    PersianCalendar();

private:
    int *gregorianToPersian(int gregorianYear, int gregorianMonth, int gregorianDay, int PersianDateOut[]);
};

#endif // PERSIANCALENDAR_H
