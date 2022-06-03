#include <QCoreApplication>
#include <iostream>
#include <conio.h>

#include "Calendar.h"
#include "PersianCalendar.h"
#include "GeorgianCalendar.h"

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Calendar *my_calendar;
    my_calendar = new GeorgianCalendar;
    my_calendar->printCalendar();

    char sw = 0;
    bool georgian = true;
    bool persian = false;
    while (1) {
        if (kbhit()) {
            sw = getch();
        }

        if (sw == 'b') {

            if (persian == false) {
                system("cls");
                my_calendar = new PersianCalendar;
                georgian = false;
                persian = true;
                my_calendar->printCalendar();

            } else if (georgian == false) {
                system("cls");
                my_calendar = new GeorgianCalendar;
                georgian = true;
                persian = false;
                my_calendar->printCalendar();

            }

        }
        switch (sw) {
            case 'e':
                system("cls");
                my_calendar->printCalendar();
                break;
            case 'n':
                my_calendar->nextDay();
                break;
            case 'p':
                my_calendar->previousDay();
                break;
            case 's':
                my_calendar->write();
                break;

            case 'q':
                exit(0);
                break;
        }

        sw = ' ';
    }

    return a.exec();

}
