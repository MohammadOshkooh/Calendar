#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>

using namespace std;


class Calendar {
private:

protected:
    int days_number_in_month[12];
    string month[12];

    int today;
    int this_month; /* شماره این ماه */
    int this_year; /* شماره این سال */

    int day_number_in_weekday; // 1,2,3,4,5,6,7 شماره هر روز هفته
    int first_day_month_in_weekday; // اولین روز ماه در چه روزی از هفته است

    int array[42]; //[6][7] .... for draw calendar

    int number_note=0;

    string fileName = "note.txt";

    string note_name = to_string(this_year) + "-" + to_string(this_month) + "-" + to_string(today);
    string hashh = "$#@sudo:" + note_name;
    string end_hashh = hashh + "end";
    string delete_hashh = hashh + "dalete";

    void create_days_array();

    void changeColor(int desiredColor);

    void writeFile(fstream &myFile, int count);

    void readFile(fstream &myFile, int count);

    int numberFileExist(fstream &myFile, string date);

    void deleteFile(fstream &myFile, int count);


public:
    void printCalendar();

    void nextDay();

    void previousDay();

    void write();
};


#endif // CALENDAR_H
