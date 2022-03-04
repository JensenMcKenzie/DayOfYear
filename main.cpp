/*
dayOfYear.cpp -
Author: Jensen McKenzie
Module: 6
Project: Homework 6
Problem Statement: Create a DayOfYear class that turns a day of year, or a month/month day combination into a month/month day combination

Algorithm/Plan:
  1. Creat a DayOfYear class
    1a. Instance variables contain the day of year, and static constants for the months, month days, and total days for each month.
    1b. Create constructors for a day of year, and month/month day combination.
        1ba. Turn the month/month day combination into a day of year integer.
        1bb. Check the month/month day combination for invalid entries. Ex: February 29.
    1c. Overload the << operator to print the month/month day combination for a given day of year.
    1d. Overload the ++ and -- pre and postfix operators to correctly increment or decrement the given day of year.
  2. Create a tests for each of the above features, including the overloaded operators, and errors.
*/

#include <iostream>

using namespace std;

//DayOfYear class
class DayOfYear{
    //Instance variables for the day, and static constants for months, month days, and total days for each month
    private:
        int day;
        static const string months[];
        static const int monthDays[], totalDays[];
    public:
        //Constructor using a date, set the current date to the new one
        DayOfYear(int day){
            this->day = day;
        }

        //Constructor using a string for month and the day of the month
        DayOfYear(string month, int day){
            //Check the day of the month for validity
            for (int i = 0; i < 12; i++) {
                if (month == months[i]) {
                    if (day > monthDays[i] || day < 1){
                        cout << "Invalid day for month of " << month << ": " << day << endl;
                        exit(0);
                    }
                }
            }
            //Find the month in the array
            for (int i = 0; i < 12; i++){
                if (month == months[i]){
                    //Set the day to the day of the year corresponding to the month and day of the month
                    this->day = totalDays[i] - (monthDays[i] - day);
                    return;
                }
            }
            //Check the month for validity, if we haven't encountered it above, it is not in the list
            cout << "Invalid month name: " << month << endl;
            exit(0);
        }

        //Return the current day
        int getDay(){
            return day;
        }

        //Overloaded << operator
        friend ostream &operator<<(ostream &out, const DayOfYear &dayOfYear){
            //Loop through each of the totaldays, checking to see if the given day is less than the amount
            for (int i = 0; i < 12; i++){
                if (dayOfYear.day <= totalDays[i]){
                    //Print the date in Month DayOfMonth format
                    out << (i == 0 ? (months[i] + " " + to_string(dayOfYear.day)) : (months[i] + " " + to_string(dayOfYear.day - totalDays[i-1])));
                    break;
                }
            }
            //Return the output
            return out;
        }

        //Overloaded ++ prefix operator
        DayOfYear operator++(){
            //Check to see if we are on the last day
            if (day == 365){
                //Set the day to the first day
                day = 1;
            }else{
                //Increment the day
                day++;
            }
            //Return the caller object
            return *this;
        }

        //Overloaded ++ postfix operator
        DayOfYear operator++(int){
            //Create a copy of the caller object
            DayOfYear copy = *this;
            //Check to see if we are on the last day
            if (copy.day == 365){
                //Set the day to the first day
                copy.day = 1;
            }else{
                //Increment the day
                copy.day++;
            }
            //Return the modified copy of the caller object
            return copy;
        }

        //Overloaded -- prefix operator
        DayOfYear operator--(){
            //Check to see if we are on the first day
            if (day == 1){
                //Set the day to the last day
                day = 365;
            }else{
                //Decrement the day
                day--;
            }
            //Return the caller object
            return *this;
        }

        //Overloaded -- postfix operator
        DayOfYear operator--(int){
            //Create a copy of the caller object
            DayOfYear copy = *this;
            //Check to see if we are on the first day
            if (copy.day == 1){
                //Set the day to the last day
                copy.day = 365;
            }else{
                //Decrement the day
                copy.day--;
            }
            //Return the modified copy of the caller object
            return copy;
        }
};

//Initialize the constant static variables
const string DayOfYear::months [12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int DayOfYear::monthDays [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};
const int DayOfYear::totalDays [12] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

int main() {
    //Initialize test objects with day of year integers
    DayOfYear d1(15);
    DayOfYear d2(31);
    DayOfYear d3(59);
    DayOfYear d4(180);
    DayOfYear d5(360);
    //Test day number constructors
    cout << "Testing day number constructor:" << endl;
    cout << "Day 15 is: " << d1 << endl;
    cout << "Day 31 is: " << d2 << endl;
    cout << "Day 59 is: " << d3 << endl;
    cout << "Day 180 is: " << d4 << endl;
    cout << "Day 360 is: " << d5 << endl << endl;


    //Test month and day constructors
    d1 = * new DayOfYear("January",1);
    d2 = * new DayOfYear("March",4);
    d3 = * new DayOfYear("July",25);
    d4 = * new DayOfYear("December",31);
    cout << "Testing month and day constructor:" << endl;
    cout << "January 1 is day: " << d1.getDay() << endl;
    cout << "March 4 is day: " << d2.getDay() << endl;
    cout << "July 25 is day: " << d3.getDay() << endl;
    cout << "December 31 is day: " << d4.getDay() << endl << endl;

    //Test -- and ++ prefix
    cout << "Testing -- and ++ prefix:" << endl;
    cout << "Using January 1 (day " << d1.getDay() << "):" << endl;
    cout << "The original value: " << d1 << endl;
    cout << "Using prefix--    : " << --d1 << endl;
    cout << "After prefix--    : " << d1 << endl;
    cout << "Using March 4 (day " << d2.getDay() << "):" << endl;
    cout << "The original value: " << d2 << endl;
    cout << "Using prefix--    : " << ++d2 << endl;
    cout << "After prefix--    : " << d2 << endl << endl;

    //Test -- and ++ postfix
    cout << "Testing -- and ++ postfix:" << endl;
    cout << "Using July 25 (day " << d3.getDay() << "):" << endl;
    cout << "The original value: " << d3 << endl;
    cout << "Using postfix--    : " << d3-- << endl;
    cout << "After postfix--    : " << d3 << endl;
    cout << "Using December 31 (day " << d4.getDay() << "):" << endl;
    cout << "The original value: " << d4 << endl;
    cout << "Using postfix--    : " << d4++ << endl;
    cout << "After postfix--    : " << d4 << endl << endl;

    //Test invalid month day error
    cout << "Testing invalid month/day combinations:" << endl;
    d1 = * new DayOfYear("February", 30);
}
