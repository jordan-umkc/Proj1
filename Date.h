#ifndef __DATE_H__
#define __DATE_H__

#include <stdexcept>
#include <iostream>
#include "StringTokenizer.h"
using namespace std;

const int DAYS[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
    private:
    int year;
    int month;
    int day;

public:

    Date(){ year = 1; month = 1; day = 1; }

    Date(int year, int month, int day) : year(year), month(month), day(day){
        if (!valid_date(year, month, day))
            throw std::invalid_argument(" The date is not valid");
    }

	string toString() const {
		return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
	}

	friend istream& operator >> (istream& in, Date& d)
	{
		string inDate;
		
		do {
			in >> inDate;
			String_Tokenizer dt(inDate, "/");
			d.setMonth(stoi(trim(dt.next_token())));
			d.setDay(stoi(trim(dt.next_token())));
			d.setYear(stoi(trim(dt.next_token())));
		} while (!valid_date(d.year, d.month, d.day));

		return in;
	}

    bool operator <(const Date other) const{
        if (year != other.year)
            return year < other.year;

        if (month != other.month)
            return month < other.month;

        return day < other.day;
    }

    static bool valid_date(int year, int month, int day){

        if (year>0 && month >= 1 && month <= 12 && day >= 1 && day <= 31){

            if (year % 4 == 0 && month == 2) // check for the leap year case
                return day <= 29;

            return day <= DAYS[month - 1];
        }
		return false;
    }

    void add_days(int days){
        int reminder = days;

        while (reminder > 0){

            int limit = year % 4 == 0 && month == 2 ? 29 : DAYS[month - 1];

            if (reminder + day <= limit){ // applies to all months
                day += reminder;
                reminder = 0;
            }
            else if (month == 12){ //treat December differently
                year++;
                month = 1;
                reminder -= limit - day;
                day = 0;
            }
            else { //applies to all other months
                month++;
                reminder -= limit - day;
                day = 0;
            }
        }

    }

    int operator - (Date other){ //difference in number of days
        int year_r = 0, month_r = 0, day_r = 0;

        if (this->operator<(other))
            throw std::invalid_argument("This date is < the given data");

        year_r = (year - other.year) * 365;
        int larger_month = month>other.month ? month : other.month;
        int smaller_month = month<other.month ? month : other.month;

        while (larger_month - smaller_month> 0){
            month_r += DAYS[larger_month - 1];
            larger_month--;
        }

        if (other.month > month)
            month_r *= -1;

        day_r = day - other.day;

        return day_r + month_r + year_r;

    }

    bool operator >(Date other){
        if (year != other.year)
            return year > other.year;

        if (month != other.month)
            return month > other.month;

        return day > other.day;
    }

    bool operator ==(const Date other) const{
        return year == other.year && month == other.month && day == other.day;
    }

	bool operator !=(const Date other) const{
		return !(*this == other);
	}

    bool operator <=(Date other){
        return this->operator<(other) || this->operator==(other);
    }

    bool operator >=(Date other){
        return this->operator>(other) || this->operator==(other);
    }

	static string trim(const string& the_string)
	{
		size_t p = the_string.find_first_not_of(" ");
		if (p == string::npos) return "";
		size_t q = the_string.find_last_not_of(" ");
		return the_string.substr(p, q - p + 1);
	}
    //we need to check if the date is valid though

    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }

    void setYear(int theYear) { year = theYear; }
    void setMonth(int theMonth) { month = theMonth; }
    void setDay(int theDay) { day = theDay; }

};
#endif