#ifndef EVENTMAPS_H
#define EVENTMAPS_H

#include <map>
#include <set>

#include "Event.h"
#include "Task.h"
#include "Meeting.h"
#include "Trip.h"
/**
 * @class EventMaps
 * have event maps compaired by name and map of some types of repetition
 * there is a dictionary for each type of event repetition. When adding a new event, it is added to the dictionary sorted by name and the dictionary corresponding to the frequency of the event, sorted by date
 * store parameters which are tha same for all types of event
 */
class EventMaps
{
public:
	/**
	 * Add to 'eventByName' new element with key 'name' and value 'ptr'
	 * @param ptr
	 * @return false if event with the 'name' is already exist
	 */
	bool addEvent(const shared_ptr<Event> ptr);

	/**
	 * Get 'repetition' of an object pointed to by 'ptr' and add the event to one of the repetition maps
	 * @param ptr[in]
	 */
	void addEventRepMap(const shared_ptr<Event> ptr);

	/**
	 * Get 'name' and 'repetition' of an object pointed to by 'ptr' and remove Event with the 'name' from one of the repetition maps.
	 * @param ptr[in]
	 * @param date old date of event
	 * @param rep old repetition of event
	 */
	void eraseEventRepMap(const shared_ptr<Event> ptr, const Date& date, repetitionOfAnEvent rep);

	/**
	 * find iterator event
	 * @param name
	 * return iterator event
	 */
	map<string, shared_ptr<Event>>::const_iterator findIteratorEvent(const string& name) const;

	/**
	 * check if event exist
	 * @param name
	 * return true if event exist
	 */
	bool ifEventExist(const string& name) const;

	/**
	 * get all events for day
	 * @param date
	 * @param vec vector of shared_ptr events where shared_ptr event will be added
	 */
	void getAllEventsForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * add to vector events that have onetime repetition at or less that this date
	 * @param date
	 * @param vec vector of shared_ptr events where shared_ptr event will be added
	 */
	void oneTimeEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * add to vector events that have daily repetition at or less that this date
	 * @param date
	 * @param vec vector of shared_ptr events where shared_ptr event will be added
	 */
	void dailyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * add to vector events that have weekly repetition at or less that this date
	 * @param date
	 * @param vec vector of shared_ptr events where shared_ptr event will be added
	 */
	void weeklyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * add to vector events that have monthly repetition at or less that this date
	 * @param date
	 * @param vec vector of shared_ptr events where shared_ptr event will be added
	 */
	void monthlyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * add to vector events that have yearly repetition at or less that this date
	 * @param date
	 * @param vec vector of shared_ptr events where shared_ptr event will be added
	 */
	void yearlyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * change name of event
	 * @param eventName
	 * @param newName
	 */
	void changeNameOf(const string& eventName, const string& newName);

	/**
	 * change date of event
	 * @param eventName
	 * @param otherDate
	 * return false if changing was failed
	 */
	bool changeDateOf(const string& eventName, const Date& otherDate, ostream& os);

	/**
	 * change repetition of event
	 * @param eventName
	 * @param newRepetition
	 * return false if changing was failed
	 */
	bool changeRepetitionOf(const string& eventName, repetitionOfAnEvent newRepetition, ostream& os);

	bool changeEndDateOf(const string& eventName, const Date& newEndDate, ostream& os);

	void changeDescriptionOf(const string& eventName, const string& newDescription);

	/**
	 * move event
	 * @param eventName
	 * @param moveDay
	 */
	bool moveDayOf(const string& eventName, int moveDay, ostream& os);

	/**
	 * delete event
	 * @param eventName
	 * return true if event was deleted
	 */
	bool deleteEvent(const string& eventName);
private:
	struct byDateComparator
	{
		bool operator()(const Date& x, const Date& y)const
		{
			return x < y;
		}
	};

	struct byDateInverzeComparator
	{
		bool operator()(const Date& x, const Date& y) const
		{
			return x > y;
		}
	};

	struct byIntAndDateComparator
	{
		bool operator()(pair <int, Date> const x, pair <int, Date> const y)const
		{
			return x.first < y.first || (x.first == y.first && (x.second > y.second));
		}
	};

	struct byMonthDayAndDateComparator
	{
		bool operator()(pair <pair<int, int>, Date> const x, pair <pair<int, int>, Date> const y)const
		{
			return x.first.first < y.first.first || (x.first.first == y.first.first && x.first.second < y.first.second) || (x.first == y.first && x.first.second == y.first.second && x.second > y.second);
		}
	};

	multimap<Date, shared_ptr<Event>, byDateComparator> eventOneTime;
	multimap<pair<pair<int, int>, Date>, shared_ptr<Event>, byMonthDayAndDateComparator> eventYearly;
	multimap<pair<int, Date>, shared_ptr<Event>, byIntAndDateComparator> eventMonthly;
	multimap<pair<int, Date>, shared_ptr<Event>, byIntAndDateComparator> eventWeekly;
	multimap<Date, shared_ptr<Event>, byDateInverzeComparator> eventDaily;
	map<string, shared_ptr<Event>> eventByName;
};
#endif //EVENTMAPS_H
