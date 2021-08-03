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

#define timegm _mkgmtime ///< for Windows

using namespace std;

/**
 * @class Date
 * Represent datum and use for it struct tm.
 * Print day of week, day, month, year, hour and minutes of the date or without time.
 * Contain overloding the comparison operators: equal to, less than, greater than, less than or equal to, greater than or equal to.
 */
class Date
{
public:
	Date();

	/**
	 * Contructor Date
	 * @param year
	 * @param month
	 * @param day
	 * @param hour
	 * @param minute
	 */

	Date(int year, int month, int day, int hour = 0, int minute = 0);

	/**
	 * Conctructor Date with only one parametr: struct tm.
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
	 * Add to the day of the second to change the date and move the date forward.
	 * @param sec[in] is a count of seconds to add
	 */
	void addSec(int sec);

	/**
	 * Send variables 'day of week', 'day', 'month' as a string, 'year' and 'hour' and 'minute' to ostream for printing in the format:
	 * "'day of week' 'day' 'month' 'year' 'hour':'minute'".
	 * @param os[in, out]
	 */
	void printDateWithTime(ostream& os) const;
	/**
	* Send variables 'day of week', 'day', 'month' as a string and 'year' to ostream for printing in the format:
	* "'day of week' 'day' 'month' 'year'".
	* @param os[in, out]
	*/
	void printDateWithoutTime(ostream& os) const;

	/**
	 * Send variables 'hour' and 'minute' to ostream for printing in the format:
	 * "'hour':'minute'".
	 * @param os[in, out]
	 */
	void printTime(ostream& os) const;

	void setYear(int year);

	void setMonth(int month);

	void setDay(int day);

	void setHour(int hour);

	void setMinute(int minute);

	int getYear() const;

	string getStringMonth() const;

	/**
	 * @return month written as an integer variable in the range [0-11]
	 */
	int getIntMonth() const;

	int getDay() const;

	int getHour() const;

	int getMinute()const;

	/**
	 * @return day of week written as an integer variable in the range [0-6]
	 */
	int getIntWday() const;

	string getWday() const;

	tm getStructTm() const;

	/**
	 * Get Sunday in the week.
	 * @return a date that is Sunday in the week
	 */
	Date getSunday() const;
private:
	struct tm ltm;
};
#endif // TIME_H
