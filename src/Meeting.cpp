#include "Meeting.h"
#include "constants.h"

Meeting::Meeting(const string& name, const Date& date, repetitionOfAnEvent repetition, const Date& endTime, const string& description)
	:Event(name, date, repetition, endTime, description){}

bool Meeting::changeDate(const Date& newDate, ostream& os)
{
	Date newEndTimeForTest = newDate;
	newEndTimeForTest.setHour(endDate.getHour());
	newEndTimeForTest.setMinute(endDate.getMinute());
	struct tm forTestTm = newEndTimeForTest.getStructTm();
	struct tm newDateTm = newDate.getStructTm();
	if (difftime(timegm(&forTestTm), timegm(&newDateTm)) < secInTenMinutes)
	{
		os << "Meeting is less then 10 minutes" << endl;
		return false;
	}
	date = newDate;
	endDate = newEndTimeForTest;
	return true;
}

bool Meeting::changeEndDate(const Date& newEndDate, ostream& os)
{
	Date newEndTimeForTest = endDate;
	newEndTimeForTest.setHour(newEndDate.getHour());
	newEndTimeForTest.setMinute(newEndDate.getMinute());
	struct tm forTestTm = newEndTimeForTest.getStructTm();
	struct tm dateTm = date.getStructTm();
	if (difftime(timegm(&forTestTm), timegm(&dateTm)) < secInTenMinutes)
	{
		os << "Meeting is less then 10 minutes" << endl;
		return false;
	}
	endDate = newEndTimeForTest;
	return true;
}

void Meeting::print(ostream& os) const
{
	os << "Meeting: " << name << '\n'
		<< "Date: ";
	date.printDateWithTime(os);
	os << "End time: ";
	endDate.printTime(os);
	os << "Description: " << description;
	os << '\n';
}

void Meeting::printName(ostream& os) const
{
	string s_name = name;
	if (s_name.length() > 13)
	{
		s_name.resize(10);
		s_name += "...";
	}
	else
		s_name.resize(13);
	os << yellowColor << s_name;
}

string Meeting::getEndDateAttribute() const
{
	return "End time";
}