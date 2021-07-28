#include "Meeting.h"
#include "konstanty.h"

Meeting::Meeting(const string& name, const Date& date, repetitionOfAnEvent repetition, const Date& endTime, const string& place) : Event(name, date,repetition), endTime(endTime), place(place)
{
}
bool Meeting::changeDate(const Date& newDate)
{
	Date newEndTimeForTest = newDate;
	newEndTimeForTest.setHour(endTime.getHour());
	newEndTimeForTest.setMinute(endTime.getMinute());
    struct tm forTestTm = newEndTimeForTest.getStructTm();
    struct tm newDateTm = newDate.getStructTm();
	if (difftime(timegm(&forTestTm), timegm(&newDateTm)) < secInTenMinutes) return false;
	date = newDate;
	endTime = newEndTimeForTest;
	return true;
}
void Meeting::moveDay(int moveDay)
{
	date = Date(date.getYear(),date.getIntMonth()+1,date.getDay()+moveDay,date.getHour(),date.getMinute());
	endTime = Date(endTime.getYear(), endTime.getIntMonth()+1, endTime.getDay() + moveDay, endTime.getHour(), endTime.getMinute());
}

void Meeting::Print(ostream& os)const
{
	os << "Meeting: " << name << '\n' 
		<< "Date: "; 
	date.printDate(os); 
	os << "End time: ";
    endTime.printTime(os);
    os << "Place: " << place;
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
	os << yellowColor << s_name ;
}

bool Meeting::changeEndTime(const Date& newEndTime)
{
	Date newEndTimeForTest = endTime;
	newEndTimeForTest.setHour(newEndTime.getHour());
	newEndTimeForTest.setMinute(newEndTime.getMinute());
    struct tm forTestTm = newEndTimeForTest.getStructTm();
    struct tm dateTm = date.getStructTm();
	if (difftime(timegm(&forTestTm), timegm(&dateTm)) < secInTenMinutes) return false;
	endTime = newEndTimeForTest;
	return true;
}

string Meeting::getPlace() const
{
	return place;
}

Date Meeting::getEndTime() const
{
	return endTime;
}

void Meeting::setPlace(const string& newPlace)
{
	place = newPlace;
}
