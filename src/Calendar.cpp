#include <iomanip>
#include "Calendar.h"
#include "konstanty.h"

bool comp(const shared_ptr<Event>& x, const shared_ptr<Event>& y) {
	return x->getDate().getHour() < y->getDate().getHour()
		|| (x->getDate().getHour() == y->getDate().getHour() && x->getDate().getMinute() < y->getDate().getMinute());
}

Calendar::Calendar()
{
}

bool Calendar::addBirthday(const string& name, const Date& date)
{
	shared_ptr<Birthday> ptr(new Birthday(name, date));
	return calendarEvent.addEvent(ptr);
}

bool Calendar::addMeeting(const string& name, const Date& startDate, const Date& endTime, const string& place, repetitionOfAnEvent rep)
{
	shared_ptr<Meeting> ptr(new Meeting(name, startDate, rep, endTime, place));
	calendarMeetings.addMeeting(ptr);
	return calendarEvent.addEvent(ptr);
}

bool Calendar::addTrip(const string& name, const Date& startDate, const Date& endDate, const string& country, repetitionOfAnEvent rep)
{
	shared_ptr<Trip> ptr(new Trip(name, startDate, rep, endDate, country));
	calendarTrips.addTrip(ptr);
	return calendarEvent.addEvent(ptr);
}

const shared_ptr<Event> Calendar::findEvent(const string& nameEvent)
{
	auto it = calendarEvent.findIteratorEvent(nameEvent);
	return it->second;
}

bool Calendar::ifEventExist(const string& nameEvent)
{
	return calendarEvent.ifEventExist(nameEvent);
}

int Calendar::findInTypeMap(const string& name)
{
	if (calendarTrips.ifTripExist(name)) return 3;
	else if (calendarMeetings.ifMeetingExist(name))return 2;
	else return 1;
}

bool Calendar::deleteEvent(const string& nameEvent)
{
	return calendarEvent.deleteEvent(nameEvent);
}

bool Calendar::changeNameEvent(const string& oldName, const string& newName)
{
	if (ifEventExist(newName)) return false;
	calendarEvent.changeNameOf(oldName, newName);
	calendarMeetings.tryOverwriteName(oldName, newName);
	calendarTrips.tryOverwriteName(oldName, newName);
	return true;
}

bool Calendar::changeDate(const string& nameEvent, const Date& newDate)
{
	return calendarEvent.changeDateOf(nameEvent, newDate);
}

bool Calendar::changeEndTime(const string& nameMeeting, const Date& endTime)
{
	return calendarMeetings.changeEndTimeOf(nameMeeting, endTime);
}

bool Calendar::changeEndDate(const string& nameTrip, const Date& newDate)
{
	return calendarTrips.changeEndDateOf(nameTrip, newDate);
}

bool Calendar::changeRepetition(const string& nameEvent, repetitionOfAnEvent newrep)
{
	return calendarEvent.changeRepetitionOf(nameEvent, newrep);
}

void Calendar::changeCountryOfTrip(const string& nameTrip, const string& newCountry)
{
	calendarTrips.changeCountryOf(nameTrip, newCountry);
}

void Calendar::changePlaceOfMeeting(const string& nameMeeting, const string& newPlace)
{
	calendarMeetings.changePlaceOf(nameMeeting, newPlace);
}

void Calendar::moveEventForDays(const string& nameEvent, int amountOfDays)
{
	calendarEvent.moveDayOf(nameEvent, amountOfDays);
}

Date Calendar::searchTheEarestFreeDate(const Date& date)
{
	Date freeDate(date);
	vector<shared_ptr<Event>> dayEvents;
	do
	{
		dayEvents.clear();
		freeDate.setDay(freeDate.getDay() + 1);
		calendarEvent.getAllEventsForDay(freeDate, dayEvents);
	} while (!dayEvents.empty());
	return freeDate;
}

void Calendar::moveEventToTheEarestFreeDate(const string& eventName)
{
	auto it = findEvent(eventName);
	Date startDate = it->getDate();
	struct tm startTm = startDate.getStructTm();
	Date freeDate = searchTheEarestFreeDate(startDate);
	struct tm freeTm = freeDate.getStructTm();
	int amountOfDays = ceil(difftime(mktime(&freeTm), mktime(&startTm)) / secInDay);
	calendarEvent.moveDayOf(eventName, amountOfDays);
}

void Calendar::getSizeWhitespaces(int& begin, int& end, int lengthSegment, int lengthWord) const
{
	int WhitespaceSize = lengthSegment - lengthWord;
	begin = (WhitespaceSize / 2);
	end = WhitespaceSize - begin;
}

void Calendar::hearderLine(int size) const
{
	cout << string(size, '-') << endl;
}

void Calendar::printWhitespace(int size) const
{
	cout << string(size, ' ');
}

void Calendar::headerMonth(int month) const
{
	hearderLine(78);
	int begin, end;
	getSizeWhitespaces(begin, end, 76, vectorMonth[month].length());
	cout << "|";
	printWhitespace(begin);
	cout << vectorMonth[month];
	printWhitespace(end);
	cout << "|" << endl;
}

void Calendar::headerWdays() const
{
	hearderLine(78);
	for (const auto& wd : wday)
	{
		int begin, end;
		getSizeWhitespaces(begin, end, 10, wd.length());
		cout << "|";
		printWhitespace(begin);
		cout << wd;
		printWhitespace(end);
	}
	cout << "|" << endl;
	hearderLine(78);
}

void Calendar::getDailyCalendar(const Date& date)
{
	vector<shared_ptr<Event>> dailyEvents;
	calendarEvent.getAllEventsForDay(date, dailyEvents);
	sort(dailyEvents.begin(), dailyEvents.end(), comp);
	hearderLine(20);
	cout << "|";
	printWhitespace(1);
	struct tm dateTm = date.getStructTm();
	cout << put_time(&dateTm, "%d %b %Y %a");;
	printWhitespace(2);
	cout << "|" << endl;
	hearderLine(20);
	for (size_t j = 0; j < dailyEvents.size(); j++)
	{
		ostringstream oss;
		dailyEvents[j]->printName(oss);
		struct tm dateTm = dailyEvents[j]->getDate().getStructTm();
		int begin, end;
		getSizeWhitespaces(begin, end, 13, dailyEvents[j]->getName().length());
		cout << clear << "|" << oss.str(); printWhitespace(begin + end);
		cout << put_time((&dateTm), "%R") << clear << "|" << endl;
	}
	cout << clear;
	hearderLine(20);
}

void Calendar::getWeeklyCalendar(const Date& date)
{
	vector<vector<shared_ptr<Event>>> weekEvents;
	weekEvents.resize(7);
	Date day = date.getSunday();
	for (size_t i = 0; i < 7; i++)
	{
		calendarEvent.getAllEventsForDay(day, weekEvents[i]);
		int begin, end;
		getSizeWhitespaces(begin, end, 10, to_string(day.getDay()).length());
		cout << "|";
		printWhitespace(begin);
		cout << day.getDay();
		printWhitespace(end);
		day.setDay(day.getDay() + 1);
	}
	cout << "|" << endl;
	hearderLine(78);
	size_t maxSize = 1;
	for (size_t i = 0; i < 7; i++)
	{
		if (weekEvents[i].size() > maxSize) maxSize = weekEvents[i].size();
	}
	for (size_t j = 0; j < maxSize; j++)
	{
		for (size_t i = 0; i < 7; i++)
		{
			string s;
			if (weekEvents[i].size() > j)
			{
				s = weekEvents[i][j]->getName();
				if (s.length() > 10)//cut a word if is longer then 10
				{
					s.resize(7);
					s += "...";
				}
			}
			else s = "";
			cout << "|" << setfill(' ') << setw(10) << left << s;
		}
		cout << "|" << endl;
	}
	hearderLine(78);
}

void Calendar::getMonthlyCalendar(const Date& date)
{
	Date start = date;
	start.setDay(1);
	start = start.getSunday();
	while (start.getIntMonth() <= date.getIntMonth())
	{
		getWeeklyCalendar(start);
		start.setDay(start.getDay() + 7);
		if (date.getIntMonth() == 11 && start.getIntMonth() == 0) break;
	}
}
