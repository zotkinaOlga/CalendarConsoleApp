#include "Date.h"
#include "konstanty.h"

Date::Date()
{
}

Date::Date(int year, int month, int day, int hour, int minute)
{
	ltm.tm_year = year - 1900;
	ltm.tm_mon = month - 1;
	ltm.tm_mday = day;
	ltm.tm_hour = hour;
	ltm.tm_min = minute;
	ltm.tm_sec = 0;
	timegm(&ltm);
}

Date::Date(const tm& t)
{
	ltm = t;
	timegm(&ltm);
}

bool Date::operator==(const Date& x) const
{
	return std::make_tuple(ltm.tm_year, ltm.tm_mon, ltm.tm_mday, ltm.tm_hour, ltm.tm_min) == std::make_tuple(x.ltm.tm_year, x.ltm.tm_mon, x.ltm.tm_mday, x.ltm.tm_hour, x.ltm.tm_min);
}

bool Date::operator<(const Date& x) const
{
	return std::make_tuple(ltm.tm_year, ltm.tm_mon, ltm.tm_mday, ltm.tm_hour, ltm.tm_min) < std::make_tuple(x.ltm.tm_year, x.ltm.tm_mon, x.ltm.tm_mday, x.ltm.tm_hour, x.ltm.tm_min);
}

bool Date::operator>(const Date& x) const
{
	return !(*this < x) && !(*this == x);
}

bool Date::operator>=(const Date& x) const
{
	return !(*this < x) || (*this == x);
}

bool Date::operator<=(const Date& x) const
{
	return (*this < x) || (*this == x);
}

void Date::setYear(int year)
{
	ltm.tm_year = year - 1900;
}

void Date::setMonth(int month)
{
	ltm.tm_mon = month - 1;//1.position 0
	timegm(&ltm);
}

void Date::setDay(int day)
{
	ltm.tm_mday = day;
	timegm(&ltm);
}

void Date::setHour(int hour)
{
	ltm.tm_hour = hour;
	timegm(&ltm);
    
}

void Date::setMinute(int minute)
{
	ltm.tm_min = minute;
	timegm(&ltm);
    
}

int Date::getYear()const
{
	return ltm.tm_year + 1900;
}

string Date::getStringMonth() const
{
	return vectorMonth[ltm.tm_mon];
}

int Date::getIntMonth() const
{
	return ltm.tm_mon;
}

int Date::getDay() const
{
	return ltm.tm_mday;
}

int Date::getHour() const
{
	return ltm.tm_hour;
}

int Date::getMinute() const
{
	return ltm.tm_min;
}

int Date::getIntWday()const
{
	return ltm.tm_wday;
}

string Date::getWday()const
{
	return wday[ltm.tm_wday];
}

tm Date::getStructTm() const
{
	return ltm;
}

Date Date::getSunday() const
{
	Date sunday(*this);
	sunday.setDay(sunday.getDay() - (*this).getIntWday());
	return sunday;
}

void Date::addSec(int sec)
{
	ltm.tm_sec += sec;
	timegm(&ltm);
}

void Date::printDate(ostream& os) const
{
	os << put_time(&ltm, "%A %R %d %B %Y") << '\n';
}

void Date::printTime(ostream& os) const
{
	os << put_time(&ltm, "%R") << '\n';
}
