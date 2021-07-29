#include "Birthday.h"
#include "constants.h"

Birthday::Birthday(const string& name, const Date& date, repetitionOfAnEvent newRepetition) : Event(name, date, yearly){}

bool Birthday::changeDate(const Date& otherDate)
{
	date = otherDate;
	return true;
}

bool Birthday::changeRepetition(repetitionOfAnEvent newRepetition)
{
	return newRepetition == yearly;
}

void Birthday::moveDay(int moveDay)
{
	date.setDay(date.getDay() + moveDay);
}

void Birthday::print(ostream& os) const
{
	os << "Birthday: " << name << '\n'
		<< "Date: ";
	date.printDate(os);
	os << '\n';
}

void Birthday::printName(ostream& os) const
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
	os << redColor << s_name;
}
