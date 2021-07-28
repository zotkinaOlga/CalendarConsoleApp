#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <locale>
#include <ctime>
#include <cstring>
#include <chrono>
#include <tuple>
#define timegm _mkgmtime
using namespace std;

/**
 * @class Date
 * represent datum
 * use struct tm
 */
class Date
{
public:
    Date();
    
    /**
     * contructor Date with time 
     * @param year
     * @param month
     * @param day 
     * @param hour 
     * @param minute 
     */
    
	Date(int year, int month, int day, int hour = 0, int minute = 0);
    
    /**
     * conctructor Date: struct tm
     * @param t
     */
	Date(const tm& t);
    
    /**
     * operator== for Date
     * @param x
     */
	bool operator==(const Date& x) const;
    
    /**
     * operator< for Date
     * @param x
     */
	bool operator<(const Date& x)const;
    
    /**
     * operator<= for Date
     * @param x
     */
	bool operator<=(const Date& x)const;
    
    /**
     * operator> for Date
     * @param x
     */
	bool operator>(const Date& x) const;
    
    /**
     * operator>= for Date
     * @param x
     */
	bool operator>=(const Date& x) const;
	
    /**
     * set year
     * @param year
     */
	void setYear(int year);
    
    /**
     * set month
     * @param month
     */
	void setMonth(int month);
    
    /**
     * set day
     * @param day
     */
	void setDay(int day);
    
    /**
     * set hour
     * @param hour
     */
	void setHour(int hour);
    
    /**
     * set minute
     * @param minute
     */
	void setMinute(int minute);
	
    /**
     * return year
     */
	int getYear() const;
    
    /**
     * return string month
     */
	string getStringMonth() const;
    
    /**
     * return int month [0-11]
     */
	int getIntMonth() const;
    
    /**
     * return day
     */
	int getDay() const;
    
    /**
     * return hour
     */
	int getHour() const;
    
    /**
     * return minute
     */
	int getMinute()const;
    
    /**
     * return int wday [0-6]
     */
	int getIntWday() const;
    
    /**
     * return string wday
     */
	string getWday() const;
    
    /**
     * return struct tm
     */
	tm getStructTm() const;

	/**
	 * get Sunday in the week that the day is
	 * return a date that is Sunday in the week that the day is
     */
	Date getSunday() const;

	/**
	 * add to the day of the second, it changes the date and moves the date forward
	 * @param sec 
	 */
	void addSec(int sec);
	
	/**
	 * print date
	 * @param os ostream where date printing is written
	 */
	void printDate(ostream& os) const;
    
    /**
	 * print time
	 * @param os ostream where time printing is written
	 */
	void printTime(ostream& os) const;
private:
	struct tm ltm;
};
#endif // TIME_H
