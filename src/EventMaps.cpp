#include "EventMaps.h"

bool EventMaps::addEvent(const shared_ptr<Event> ptr)
{
	if (!eventByName.emplace(ptr->getName(), ptr).second)
	{
		return false;
	}
	addEventRepMap(ptr);
	return true;
}

void EventMaps::addEventRepMap(shared_ptr<Event> ptr)
{
	if (ptr->getRepetition() == oneTime)
	{
		eventOneTime.emplace(ptr->getDate(), ptr);
	}
	else if (ptr->getRepetition() == yearly)
	{
		eventYearly.emplace(make_pair(make_pair(ptr->getDate().getIntMonth(), ptr->getDate().getDay()), ptr->getDate()), ptr);
	}
	else if (ptr->getRepetition() == monthly)
	{
		eventMonthly.emplace(make_pair(ptr->getDate().getDay(), ptr->getDate()), ptr);
	}
	else if (ptr->getRepetition() == weekly)
	{
		eventWeekly.emplace(make_pair(ptr->getDate().getIntWday(), ptr->getDate()), ptr);
	}
	else
	{
		eventDaily.emplace(ptr->getDate(), ptr);
	}
}

void EventMaps::eraseEventRepMap(shared_ptr<Event> ptr, const Date& date, repetitionOfAnEvent rep)
{
	if (rep == oneTime)
	{
		auto it = eventOneTime.find(date);
		for (; it->second->getName() != ptr->getName(); it++);
		eventOneTime.erase(it);
	}
	else if (rep == yearly)
	{
		auto it = eventYearly.find(make_pair(make_pair(date.getIntMonth(), date.getDay()), date));
		for (; it->second->getName() != ptr->getName(); it++);
		eventYearly.erase(it);
	}
	else if (rep == monthly)
	{
		auto it = eventMonthly.find(make_pair(date.getDay(), date));
		for (; it->second->getName() != ptr->getName(); it++);
		eventMonthly.erase(it);
	}
	else if (rep == weekly)
	{
		auto it = eventWeekly.find(make_pair(date.getIntWday(), date));
		for (; it->second->getName() != ptr->getName(); it++);
		eventWeekly.erase(it);
	}
	else
	{
		auto it = eventDaily.find(date);
		for (; it->second->getName() != ptr->getName(); it++);
		eventDaily.erase(it);
	}
}

map<string, shared_ptr<Event>>::const_iterator EventMaps::findIteratorEvent(const string& name) const
{
	return eventByName.find(name);
}

bool EventMaps::ifEventExist(const string& name) const
{
	return findIteratorEvent(name) != eventByName.end();
}

void EventMaps::getAllEventsForDay(const Date& date, vector<shared_ptr<Event>>& vec) const
{
	oneTimeEventForDay(date, vec);
	dailyEventForDay(date, vec);
	weeklyEventForDay(date, vec);
	monthlyEventForDay(date, vec);
	yearlyEventForDay(date, vec);
}

void EventMaps::oneTimeEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const
{
	if (eventOneTime.empty())
	{
		return;
	}
	Date date1(date);
	date1.setHour(0);
	date1.setMinute(0);
	auto it1 = eventOneTime.lower_bound(date1);
	Date date2(date);
	date2.setHour(23);
	date2.setMinute(59);
	if (it1 != eventOneTime.end() && it1->second->getDate() < date1)
	{
		it1++;
	}
	while (it1 != eventOneTime.end() && it1->first <= date2)
	{
		vec.push_back(it1->second);
		it1++;
	}
}

void EventMaps::dailyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const
{
	if (eventDaily.empty())
	{
		return;
	}
	Date date1(date);
	date1.setHour(23);
	date1.setMinute(59);
	auto it1 = eventDaily.lower_bound(date1);
	if (it1 != eventDaily.end() && it1->second->getDate() > date1)
	{
		it1++;
	}
	while (it1 != eventDaily.end() && it1->second->getDate() <= date1)
	{
		vec.push_back(it1->second);
		it1++;
	}
}

void EventMaps::weeklyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const
{
	if (eventWeekly.empty())
	{
		return;
	}
	Date date1(date);
	date1.setHour(23);
	date1.setMinute(59);
	auto it1 = eventWeekly.lower_bound(make_pair(date1.getIntWday(), date1));
	if (it1 != eventWeekly.end() && it1->first.first > date1.getIntWday())
	{
		it1++;
	}
	while (it1 != eventWeekly.end() && it1->first.first == date1.getIntWday())
	{
		vec.push_back(it1->second);
		it1++;
	}
}

void EventMaps::monthlyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const
{
	if (eventMonthly.empty()) return;
	Date date1(date);
	date1.setHour(23);
	date1.setMinute(59);
	auto it1 = eventMonthly.lower_bound(make_pair(date1.getDay(), date1));
	if (it1 == eventMonthly.end())
	{
		return;
	}
	if (it1->second->getDate() > date1)
	{
		it1++;
	}
	while (it1 != eventMonthly.end() && it1->first.first == date1.getDay())
	{
		vec.push_back(it1->second);
		it1++;
	}
}

void EventMaps::yearlyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const
{
	if (eventYearly.empty())
	{
		return;
	}
	Date date1(date);
	date1.setHour(23);
	date1.setMinute(59);
	auto it1 = eventYearly.lower_bound(make_pair(make_pair(date1.getIntMonth(), date1.getDay()), date1));
	if (it1 == eventYearly.end())
	{
		return;
	}
	if (it1->first.first.second < date1.getDay() || it1->first.first.first < date1.getIntMonth() || it1->first.second>date1)
	{
		it1++;
	}
	while (it1 != eventYearly.end() && it1->first.first.first == date1.getIntMonth() && it1->first.first.second == date1.getDay())
	{
		vec.push_back(it1->second);
		it1++;
	}
}

bool EventMaps::changeDateOf(const string& eventName, const Date& otherDate)
{
	auto it = findIteratorEvent(eventName);
	Date oldDate = it->second->getDate();
	if (it->second->changeDate(otherDate))
	{
		auto itEvent = it->second;
		eraseEventRepMap(itEvent, oldDate, itEvent->getRepetition());
		addEventRepMap(itEvent);
		return true;
	}
	return false;
}

void EventMaps::changeNameOf(const string& eventName, const string& newName)
{
	auto it = findIteratorEvent(eventName);
	it->second->changeName(newName);
	eventByName.emplace(newName, it->second);
	eventByName.erase(it);
}

bool EventMaps::changeRepetitionOf(const string& eventName, repetitionOfAnEvent newRepetition)
{
	auto it = findIteratorEvent(eventName)->second;
	repetitionOfAnEvent oldRep = it->getRepetition();
	if (it->changeRepetition(newRepetition))
	{
		addEventRepMap(it);
		eraseEventRepMap(it, it->getDate(), oldRep);
		return true;
	}
	return false;
}

void EventMaps::moveDayOf(const string& eventName, int moveDay)
{
	auto it = findIteratorEvent(eventName)->second;
	Date oldDate = it->getDate();
	it->moveDay(moveDay);
	addEventRepMap(it);
	eraseEventRepMap(it, oldDate, it->getRepetition());
}

bool EventMaps::deleteEvent(const string& eventName)
{
	return eventByName.erase(findIteratorEvent(eventName)->first);
}
