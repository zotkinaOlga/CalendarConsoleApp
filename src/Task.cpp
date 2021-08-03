#include "Task.h"
#include "constants.h"

Task::Task(const string& name, const Date& date, repetitionOfAnEvent newRepetition, const Date& deadline, const string& description) : Event(name, date, repetition, deadline, description){}

bool Task::changeDate(const Date& otherDate, ostream& os)
{
	if (otherDate >= endDate)
	{
		os << "The deadline comes before the start\n";
		return false;
	}
	date = otherDate;
	return true;
}

bool Task::changeEndDate(const Date& otherDate, ostream& os)
{
	if(otherDate <= date)
	{
		os << "The deadline comes before the start\n";
		return false;
	}
	endDate = otherDate;
	return true;
}

bool Task::moveDay(int moveDay, ostream& os)
{
	Date newStartDate(date.getYear(), date.getIntMonth() + 1, date.getDay() + moveDay, date.getHour(), date.getMinute());
	struct tm dateTm = newStartDate.getStructTm();
	struct tm deadlineTm = endDate.getStructTm();
	if (difftime(timegm(&dateTm), timegm(&deadlineTm)) < 1)
	{
		os << "The deadline comes before the start\n";
		return false;
	}
	date.setDay(date.getDay() + moveDay);
	return true;
}

void Task::print(ostream& os) const
{
	os << "Task: " << name << '\n'
		<< "Date: ";
	date.printDateWithTime(os);
	os << "Deadline: ";
	endDate.printDateWithTime(os);
	os << "Description: " << description << '\n';
}

void Task::printName(ostream& os) const
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

string Task::getEndDateAttribute() const
{
	return "Deadline";
}