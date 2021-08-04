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
 * This class contains map, where objects are sorted by 'name' with the value of shared_ptr to object of class Event with the appropriate name
 * and multimaps for each possible event type repetition, where objects are sorted by 'date' with the value of shared_ptr to object of class Event: 
 * 'eventOneTime' for events with repetition 'oneTime',
 * 'eventDaily' for events with repetition 'daily',
 * 'eventWeekly' for events with repetition 'weekly',
 * 'eventMonthly' for events with repetition 'monthly',
 * 'eventYearly' for events with repetition 'yearly'.
 * The class adds a new object of class Event to map 'eventByName' and the map corresponding to the value of the variable 'repetition', 
 * finds the Event in the maps relative to its 'name' or 'date', 
 * changes all the object variables and adds events that occurred on the specified day to the vector. 
 * When deletting an object, it is removed from map 'eventByName' and the map corresponding to the value of the variable 'repetition'.
 */
class EventMaps
{
public:
	/**
	 * Add to 'eventByName' new element with key 'name' and value 'ptr'.
	 * @param ptr[in]
	 * @return false if Event with the 'name' is already exist and true if Event with an unique 'name' was added
	 */
	bool addEvent(const shared_ptr<Event> ptr);

	/**
	 * Get 'repetition' of an object pointed to by 'ptr' and add Event to one of the repetition maps.
	 * @param ptr[in]
	 */
	void addEventRepMap(const shared_ptr<Event> ptr);

	/**
	 * Get 'name' of an object pointed to by 'ptr' and remove Event with the 'name' from one of the repetition maps.
	 * @param ptr[in]
	 * @param date[in]
	 * @param rep[in]
	 */
	void eraseEventRepMap(const shared_ptr<Event> ptr, const Date& date, repetitionOfAnEvent rep);

	/**
	 * Find Event in 'eventByName' by 'name'.
	 * @param name[in]
	 * return iterator is pointed to Event if Event was found or to end of the map
	 */
	map<string, shared_ptr<Event>>::const_iterator findIteratorEvent(const string& name) const;

	/**
	 * Check if Event with the 'name' was found in 'eventByName'.
	 * @param name[in]
	 * return false if iterator pointed to end of the map or true if to some other place in the map
	 */
	bool ifEventExist(const string& name) const;

	/**
	 * This function searches in multimaps of repetition all Events occurring on 'date' and adds the found Events to 'vec'.
	 * @param date[in]
	 * @param vec[in, out] 
	 */
	void getAllEventsForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * This function searches in 'eventOneTime' of repetition all Events occurring on 'date' and adds the found Events to 'vec'.
	 * @param date[in]
	 * @param vec[in, out]
	 */
	void oneTimeEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * This function searches in 'eventDaily' of repetition all Events occurring on 'date' and adds the found Events to 'vec'.
	 * @param date[in]
	 * @param vec[in, out]
	 */
	void dailyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * This function searches in 'eventWeekly' of repetition all Events occurring on 'date' and adds the found Events to 'vec'.
	 * @param date[in]
	 * @param vec[in, out]
	 */
	void weeklyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * This function searches in 'eventMonthly' of repetition all Events occurring on 'date' and adds the found Events to 'vec'.
	 * @param date[in]
	 * @param vec[in, out]
	 */
	void monthlyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * This function searches in 'eventYearly' of repetition all Events occurring on 'date' and adds the found Events to 'vec'.
	 * @param date[in]
	 * @param vec[in, out]
	 */
	void yearlyEventForDay(const Date& date, vector<shared_ptr<Event>>& vec) const;

	/**
	 * This function changes 'name' of Event, erases Event with 'eventName' from 'eventByName' and adds Event with 'newName' to 'eventByName'.
	 * @param eventName[in]
	 * @param newName[in]
	 */
	void changeNameOf(const string& eventName, const string& newName);

	/**
	 * This function changes 'date' of Event if 'date' is valid, erases Event with 'eventName' from one of the repetition multimap 
	 * and adds changed Event to this multimap by key 'otherDate'.
	 * @param eventName[in]
	 * @param otherDate[in]
	 * @param os[in, out]
	 * return false if 'date' was not valid
	 */
	bool changeDateOf(const string& eventName, const Date& otherDate, ostream& os);

	/**
	 * This function changes 'repetition' of Event with 'eventName', erases Event with 'eventName' from one of the repetition multimap 
	 * and adds changed Event to other multimap corresponding to 'newRepetition'.
	 * @param eventName[in]
	 * @param newRepetition[in]
	 * @param os[in, out]
	 * return false if changing was failed
	 */
	bool changeRepetitionOf(const string& eventName, repetitionOfAnEvent newRepetition, ostream& os);

	/**
	 * This function changes 'endDate' of Event if 'date' is valid
	 * @param eventName[in]
	 * @param newEndDate[in]
	 * @param os[in, out]
	 * return false if 'endDate' was not valid
	 */
	bool changeEndDateOf(const string& eventName, const Date& newEndDate, ostream& os);

	/**
	 * This function changes 'description' of Event to 'newDescription'
	 * @param eventName[in]
	 * @param newDescription[in]
	 */
	void changeDescriptionOf(const string& eventName, const string& newDescription);

	/**
	 * This function 
	 * @param eventName[in]
	 * @param moveDay[in]
	 * @param os[in, out]
	 * return false if 'date' or 'endDate' will not valid
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
			return x.first.first < y.first.first 
				|| (x.first.first == y.first.first && x.first.second < y.first.second) 
				|| (x.first == y.first && x.first.second == y.first.second && x.second > y.second);
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
