#include "Trip.h"
#include "constants.h"

Trip::Trip(const string& name, const Date& startDate, repetitionOfAnEvent rep, const Date& endDate, const string& country) :Event(name, startDate, rep), endDate(endDate), country(country){}

bool Trip::changeDate(const Date& otherDate)
{
	struct tm endTm = endDate.getStructTm();
	struct tm otherTm = otherDate.getStructTm();
	if (otherDate >= endDate || difftime(timegm(&endTm), timegm(&otherTm)) < secInDay)
	{
		return false;
	}
	date = otherDate;
	return true;
}

bool Trip::changeRepetition(repetitionOfAnEvent newRepetition)
{
	struct tm endTm = endDate.getStructTm();
	struct tm dateTm = date.getStructTm();
	auto timeDifference = difftime(timegm(&endTm), timegm(&dateTm));
	if ((newRepetition == yearly && timeDifference > secInYear)
		|| (newRepetition == monthly && timeDifference > secInTheSmallestMonth)
		|| (newRepetition == weekly && timeDifference > secInWeek)
		|| (newRepetition == daily && timeDifference > secInDay))
	{
		return false;
	}
	repetition = newRepetition;
	return true;
}

void Trip::moveDay(int moveDay)
{
	Date newStartTime(date.getYear(), date.getIntMonth() + 1, date.getDay() + moveDay, date.getHour(), date.getMinute());
	Date newEndTime(endDate.getYear(), endDate.getIntMonth() + 1, endDate.getDay() + moveDay, endDate.getHour(), endDate.getMinute());
	date = newStartTime;
	endDate = newEndTime;
}

void Trip::print(ostream& os)const
{
	os << "Trip: " << name << '\n'
		<< "Start date: ";
	date.printDate(os);
	os << "End date: ";
	endDate.printDate(os);
	os << "Country: " << country << '\n';
}

void Trip::printName(ostream& os) const
{
	string s_name = name;
	if (s_name.length() > 13)
	{
		s_name.resize(10);
		s_name += "...";
	}
	else
	{
		s_name.resize(13);
	}
	os << blueColor << s_name;
}

bool Trip::changeEndDate(const Date& otherDate)
{
	struct tm otherTm = otherDate.getStructTm();
	struct tm dateTm = date.getStructTm();
	if (difftime(timegm(&otherTm), timegm(&dateTm)) < secInDay)
	{
		return false;
	}
	endDate = otherDate;
	return true;
}

void Trip::setCountry(const string& otherCountry)
{
	country = otherCountry;
}

string Trip::getCountry() const
{
	return country;
}

Date Trip::getEndDate() const
{
	return endDate;
}
