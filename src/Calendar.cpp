#include "Calendar.h"
#include "constants.h"

Calendar::Calendar(){}

bool Calendar::addTask(const string& name, const Date& date, const Date& deadline, const string& description, repetitionOfAnEvent rep)
{
	shared_ptr<Task> ptr(new Task(name, date, rep, deadline, description));
	return calendarEvent.addEvent(ptr);
}

bool Calendar::addMeeting(const string& name, const Date& startDate, const Date& endTime, const string& description, repetitionOfAnEvent rep)
{
	shared_ptr<Meeting> ptr(new Meeting(name, startDate, rep, endTime, description));
	return calendarEvent.addEvent(ptr);
}

bool Calendar::addTrip(const string& name, const Date& startDate, const Date& endDate, const string& description, repetitionOfAnEvent rep)
{
	shared_ptr<Trip> ptr(new Trip(name, startDate, rep, endDate, description));
	return calendarEvent.addEvent(ptr);
}

const shared_ptr<Event> Calendar::findEvent(const string& nameEvent)
{
	return calendarEvent.findIteratorEvent(nameEvent)->second;
}

bool Calendar::ifEventExist(const string& nameEvent)
{
	return calendarEvent.ifEventExist(nameEvent);
}
/*
int Calendar::findInTypeMap(const string& name)
{
	if (calendarTrips.ifTripExist(name))
	{
		return 3;
	}
	else if (calendarMeetings.ifMeetingExist(name))
	{
		return 2;
	}
	else
	{
		return 1;
	}
}*/

bool Calendar::deleteEvent(const string& nameEvent)
{
	return calendarEvent.deleteEvent(nameEvent);
}

bool Calendar::changeNameEvent(const string& oldName, const string& newName)
{
	if (ifEventExist(newName))
	{
		return false;
	}
	calendarEvent.changeNameOf(oldName, newName);
	return true;
}

bool Calendar::changeDate(const string& nameEvent, const Date& newDate, ostream& os)
{
	return calendarEvent.changeDateOf(nameEvent, newDate, os);
}

bool Calendar::changeEndDate(const string& name, const Date& newDate, ostream &os)
{
	return calendarEvent.changeEndDateOf(name, newDate, os);
}

bool Calendar::changeRepetition(const string& nameEvent, repetitionOfAnEvent newRepetition, ostream &os)
{
	return calendarEvent.changeRepetitionOf(nameEvent, newRepetition, os);
}

void Calendar::changeDescription(const string& name, const string& newDescription)
{
	calendarEvent.changeDescriptionOf(name, newDescription);
}

bool Calendar::moveEventForDays(const string& nameEvent, int amountOfDays, ostream& os)
{
	return calendarEvent.moveDayOf(nameEvent, amountOfDays, os);
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
	ostringstream oss;
	calendarEvent.moveDayOf(eventName, amountOfDays, oss);
}

void Calendar::getDailyCalendar(const Date& date, ostream& os)
{
	vector<shared_ptr<Event>> dailyEvents;
	calendarEvent.getAllEventsForDay(date, dailyEvents);
	sort(dailyEvents.begin(), dailyEvents.end(), [](const shared_ptr<Event>&x, const shared_ptr<Event>&y) {
		return x->getDate().getHour() < y->getDate().getHour()
			|| (x->getDate().getHour() == y->getDate().getHour() && x->getDate().getMinute() < y->getDate().getMinute());
	});
	hearderLine(20, os);
	cout << "|";
	printWhitespace(1, os);
	struct tm dateTm = date.getStructTm();
	os << put_time(&dateTm, "%d %b %Y %a");;
	printWhitespace(2, os);
	os << "|" << endl;
	hearderLine(20, os);
	for (size_t j = 0; j < dailyEvents.size(); j++)
	{
		os << clear << "|";
		dailyEvents[j]->printName(os);
		struct tm dateTm = dailyEvents[j]->getDate().getStructTm();
		int begin, end;
		getSizeWhitespaces(begin, end, 13, dailyEvents[j]->getName().length());
		printWhitespace(begin + end, os);
		os << put_time((&dateTm), "%R") << clear << "|" << endl;
	}
	os << clear;
	hearderLine(20, os);
}

void Calendar::getWeeklyCalendar(const Date& date, ostream& os)
{
	vector<vector<shared_ptr<Event>>> weekEvents;
	weekEvents.resize(7);
	Date day = date.getSunday();
	os << boldFront;
	for (size_t i = 0; i < 7; i++)
	{
		calendarEvent.getAllEventsForDay(day, weekEvents[i]);
		int begin, end;
		getSizeWhitespaces(begin, end, 10, to_string(day.getDay()).length());
		os << "|";
		printWhitespace(begin, os);
		os << day.getDay();
		printWhitespace(end, os);
		day.setDay(day.getDay() + 1);
	}
	os << "|" << clear << endl;
	hearderLine(78, os);
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
			else
			{
				s = "";
			}
			os << "|" << setfill(' ') << setw(10) << left << s;
		}
		os << "|" << endl;
	}
	hearderLine(78, os);
}

void Calendar::getMonthlyCalendar(const Date& date, ostream& os)
{
	Date start = date;
	start.setDay(1);
	start = start.getSunday();
	while (start.getIntMonth() <= date.getIntMonth() && !(date.getIntMonth() == 11 && start.getIntMonth() == 0))
	{
		getWeeklyCalendar(start, os);
		start.setDay(start.getDay() + 7);
	}
}


void Calendar::getSizeWhitespaces(int& begin, int& end, int lengthSegment, int lengthWord) const
{
	int WhitespaceSize = lengthSegment - lengthWord;
	begin = (WhitespaceSize / 2);
	end = WhitespaceSize - begin;
}

void Calendar::hearderLine(int size, ostream& os) const
{
	os << string(size, '-') << endl;
}

void Calendar::printWhitespace(int size, ostream& os) const
{
	os << string(size, ' ');
}

void Calendar::headerMonth(int month, ostream& os) const
{
	hearderLine(78, os);
	int begin, end;
	getSizeWhitespaces(begin, end, 76, vectorMonth[month].length());
	os << "|" << reversionFront;
	printWhitespace(begin, os);
	os << vectorMonth[month];
	printWhitespace(end, os);
	os << clear << "|" << endl;
}

void Calendar::headerWdays(ostream& os) const
{
	hearderLine(78, os);
	for (const auto& wd : wday)
	{
		int begin, end;
		getSizeWhitespaces(begin, end, 10, wd.length());
		os << "|";
		printWhitespace(begin, os);
		os << wd;
		printWhitespace(end, os);
	}
	os << "|" << endl;
	hearderLine(78, os);
}