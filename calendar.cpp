#include "Calendar.h"
#include <conio.h>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <fstream>

using namespace std;

void Calendar::create_days_array() {
    int index = 0;
    for (int i = index; i < first_day_month_in_weekday; i++) {
        array[i] = -1;
        index++;
    }

    int counter = 1;
    for (int i = index; counter <= days_number_in_month[this_month - 1]; i++) {
        array[i] = counter;
        counter++;
        index++;
    }

    for (int i = index; i < 42; i++) {
        array[i] = -1;
        index++;
    }
    int c = 0;
    for (int i = 0; i < 7; ++i) {

        if (array[i] == -1)
            c++;
        if (c == 7)
            for (int j = 0; j < 7; j++) {
                array[j] = 0;
            }
    }
    c = 0;
    for (int i = 35; i < 42; ++i) {
        if (array[i] == -1)
            c++;
        if (c == 7)
            for (int j = 35; j < 42; j++) {
                array[j] = 0;
            }

    }

}

void Calendar::changeColor(int desiredColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}


void Calendar::writeFile(fstream &myFile, int count) {
    /* update hash */
    hashh = "$#@sudo:" + note_name;
    end_hashh = hashh + "end";

    string text;
    if (myFile) {
        cout << "Enter a text and end text, please press Enter and type 'save' and press Enter " << endl;
        cout << "date : " << note_name << endl;
        cout << "your text can contain Enter (new line)\n" << endl;
        myFile << hashh << endl;
        myFile << to_string(count + 1) << endl;
        getline(cin, text);
        while (text != "save") {
            myFile << text;
            myFile << "\n";
            getline(cin, text);
        }
        myFile << end_hashh << endl;
        cout << "................................" << endl;
        cout << "writing completed successfully" << endl;
        cout << "e : go to calendar" << endl;
    }

    myFile.close();
}

void Calendar::readFile(fstream &myFile, int count) {
    /* update hash */
    hashh = "$#@sudo:" + note_name;
    end_hashh = hashh + "end";

    string text;
    if (myFile)
        while (!myFile.eof()) {
            getline(myFile, text);
            if (text == hashh) {
                getline(myFile, text);
                if (text == to_string(count)) {
                    getline(myFile, text);
                    while (text != end_hashh) {
                        cout << text << endl;
                        getline(myFile, text);
                    }
                }
            }
        }
}

int Calendar::numberFileExist(fstream &myFile, string date) {
    string text;
    bool deleted = 0;
    int counter = 0;
    string hashh = "$#@sudo:" + date;
    if (myFile)
        while (!myFile.eof()) {
            getline(myFile, text);
            if (text == hashh) {
                getline(myFile, text);
                getline(myFile, text);
                if (text == delete_hashh)
                    deleted = 1;
                else
                    deleted = 0;
                if (text.length() != 0)
                    counter += 1;
            }
        }
    if (deleted == 1)
        return 0;

    return counter;
}

void Calendar::deleteFile(fstream &myFile, int count) {
    /* update hash */
    hashh = "$#@sudo:" + note_name;
    end_hashh = hashh + "end";

    string text;
    if (myFile) {
        myFile << hashh << endl;
        myFile << to_string(count + 1) << "\n";
        myFile << delete_hashh << endl;
        myFile << end_hashh << endl;
        cout << "delete successfully" << endl;
        cout << "e : go to calendar" << endl;
    }
    myFile.close();
}

void Calendar::printCalendar() {

    fstream myFile;

    create_days_array();
    cout << "first_day_month_in_weekday :" << first_day_month_in_weekday << endl;
    cout << "................................" << endl;
    cout << "       " << month[this_month - 1] << " , " << this_year << endl;
    cout << "................................" << endl;
    cout << ".  Su  Mo  Tu  We  Th  Fr  Sa  ." << endl;
    cout << ".  --------------------------  ." << endl;

    int days = days_number_in_month[this_month - 1]; // روز های باقی مانده ماه
    int counter = 0;

    cout << ".  ";

    for (int i = 0; i < 42; i++) {

        if (i % 7 == 0 && i != 0) {
            cout << "." << endl;
            if (array[i + 1] != 0)
                cout << ".  ";
        }


        if (array[i] == -1)
            cout << "    ";

        else if (array[i] == 0);

        else if (array[i] > 0 && 10 > array[i]) {
            myFile.open(fileName, ios::in);
            note_name = to_string(this_year) + "-" + to_string(this_month) + "-" + to_string(array[i]);
            number_note = numberFileExist(myFile, note_name);
            myFile.close();

            if (number_note > 0) {
                changeColor(12);
                if (array[i] == today)
                    changeColor(252);
            } else if (array[i] == today)
                changeColor(240);
            cout << "0" << array[i];
            changeColor(7);
            cout << "  ";
        } else {

            myFile.open(fileName, ios::in);
            note_name = to_string(this_year) + "-" + to_string(this_month) + "-" + to_string(array[i]);
            number_note = numberFileExist(myFile, note_name);
            myFile.close();

            if (number_note > 0) {
                changeColor(12);
                if (array[i] == today)
                    changeColor(252);
            } else if (array[i] == today)
                changeColor(240);

            cout << array[i];
            changeColor(7);
            cout << "  ";
        }

    }
    cout << "." << endl;
    cout << "................................" << endl;
    cout << endl << endl << endl;
    cout << "................................" << endl;
    cout << ".                              ." << endl;
    cout << ".     n : next day             ." << endl;
    cout << ".     p : previous day         ." << endl;
    cout << ".     s : write                ." << endl;
    cout << ".     b : change calender      ." << endl;
    cout << ".     q : exit                 ." << endl;
    cout << ".                              ." << endl;
    cout << "................................" << endl;
}

void Calendar::nextDay() {
    if (today < days_number_in_month[this_month - 1]) {
        today++;

    } else {
        first_day_month_in_weekday = (first_day_month_in_weekday + days_number_in_month[this_month - 1] % 7) % 7;
        if (this_month < 12) {
            this_month++;
            today = 1;
        } else if (this_month == 12) {
            this_year++;
            this_month = 1;
            today = 1;
        }
    }

    system("cls");

    printCalendar();
}

void Calendar::previousDay() {
    if (1 < today) {
        today--;
    } else {

        if (this_month > 1) {
            this_month--;
            today = days_number_in_month[this_month - 1];
        } else if (this_month == 1) {
            this_year--;
            this_month = 12;
            today = days_number_in_month[this_month - 1];
        }

        first_day_month_in_weekday = first_day_month_in_weekday - days_number_in_month[this_month - 1] % 7;
        cout << "first_day_month_in_weekday : " << first_day_month_in_weekday << endl;

        if (first_day_month_in_weekday < 0)
            first_day_month_in_weekday += 7;

    }

    system("cls");

    printCalendar();
}

void Calendar::write() {
    system("cls");

    /* update hash */
    note_name = to_string(this_year) + "-" + to_string(this_month) + "-" + to_string(today);
    string hashh = "$#@sudo:" + note_name;
    string end_hashh = hashh + "end";
    string delete_hashh = hashh + "dalete";


    string text;
    fstream myFile;
    myFile.open(fileName);

    if (!myFile) { /* دفعه اولی که فایل نوت وجود ندارد این اجرا میشود  */
        myFile.close();
        cout<<fileName<<endl;
        myFile.open(fileName, ios::out);
        writeFile(myFile, 0);
        myFile.close();
    } else {
        myFile.close();
        myFile.open(fileName, ios::in);
        number_note = numberFileExist(myFile, note_name);
        myFile.close();
        if (number_note > 0) {
            myFile.open(fileName, ios::in);
            cout << "a note is exist" << endl;
            cout << "note :.........................." << endl;
            readFile(myFile, number_note);
            cout << "................................" << endl;
            cout << "1 : Edit     2 : Delete   e:Exit" << endl;
            while (1) {
                char sw;
                if (kbhit()) {
                    sw = getch();
                }
                if (sw == '1') {
                    system("cls");
                    myFile.close();
                    myFile.open(fileName, ios::app);
                    writeFile(myFile, number_note);
                    myFile.close();

                } else if (sw == '2') {
                    system("cls");
                    myFile.close();
                    myFile.open(fileName, ios::app);
                    deleteFile(myFile, number_note);
                    myFile.close();
                } else if (sw == 'e') {
                    system("cls");
                    printCalendar();
                    break;
                }
                sw = ' ';
            }
        } else {
            myFile.close();
            myFile.open(fileName, ios::app);
            writeFile(myFile, 0);
            myFile.close();
        }
    }

}
