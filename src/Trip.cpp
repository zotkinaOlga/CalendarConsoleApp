#include "Trip.h"
#include "constants.h"

Trip::Trip(const string& name, const Date& startDate, repetitionOfAnEvent rep, const Date& endDate, const string& description) :Event(name, startDate, rep, endDate, description){}

bool Trip::changeRepetition(repetitionOfAnEvent newRepetition, ostream& os)
{
	struct tm endTm = endDate.getStructTm();
	struct tm dateTm = date.getStructTm();
	auto timeDifference = difftime(timegm(&endTm), timegm(&dateTm));
	if ((newRepetition == yearly && timeDifference > secInYear)
		|| (newRepetition == monthly && timeDifference > secInTheSmallestMonth)
		|| (newRepetition == weekly && timeDifference > secInWeek)
		|| (newRepetition == daily && timeDifference > secInDay))
	{
		os << "Trip conflicts with dates by itself";
		return false;
	}
	repetition = newRepetition;
	return true;
}

bool Trip::changeDate(const Date& otherDate, ostream& os)
{
	struct tm endTm = endDate.getStructTm();
	struct tm otherTm = otherDate.getStructTm();
	if (otherDate >= endDate || difftime(timegm(&endTm), timegm(&otherTm)) < secInDay)
	{
		os << "Start date is more then end time or trip is less then one day";
		return false;
	}
	date = otherDate;
	return true;
}

bool Trip::changeEndDate(const Date& otherDate, ostream& os)
{
	struct tm otherTm = otherDate.getStructTm();
	struct tm dateTm = date.getStructTm();
	if (difftime(timegm(&otherTm), timegm(&dateTm)) < secInDay)
	{
		os << "Start date is more then end time or trip is less then one day";
		return false;
	}
	endDate = otherDate;
	return true;
}

void Trip::print(ostream& os) const
{
	os << "Trip: " << name << '\n'
		<< "Start date: ";
	date.printDateWithTime(os);
	os << "End date: ";
	endDate.printDateWithTime(os);
	os << "Description: " << description << '\n';
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

string Trip::getEndDateAttribute() const
{
	return "End date";
}