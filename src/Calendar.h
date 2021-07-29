#ifndef CALENDAR_H
#define CALENDAR_H

#include <sstream>      // std::ostringstream
#include <cmath> 
#include <fstream>
#include <iomanip>

#include "Birthday.h"
#include "EventMaps.h"
#include "MeetingMap.h"
#include "TripMap.h"

/**
 * @class Calendar
 * store events using objects that contain maps of these events sorted by name
 */
class Calendar
{
public:
	Calendar();

	/**
	 * add birthday
	 * @param name
	 * @param date
	 * return true if the birthday is successfully added
	 */
	bool addBirthday(const string& name, const Date& date, repetitionOfAnEvent rep);

	/**
	 * add meeting
	 * @param name
	 * @param date
	 * @param endTime
	 * @param place
	 * @param rep repetitionOfAnEvent
	 * return true if the meeting is successfully added
	 */
	bool addMeeting(const string& name, const Date& date, const Date& endTime, const string& place, repetitionOfAnEvent rep);

	/**
	 * add trip
	 * @param name
	 * @param startDate
	 * @param endDate
	 * @param country
	 * @param rep repetitionOfAnEvent
	 * return true if the trip is successfully added
	 */
	bool addTrip(const string& name, const Date& startDate, const Date& endDate, const string& country, repetitionOfAnEvent rep);

	/**
	 * find in map compared by name iterator of the event
	 * @param nameEvent that is finded
	 * return shared_ptr of the event
	 */
	const shared_ptr<Event> findEvent(const string& nameEvent);

	/**
	 * find in map compared by name iterator of the event and get its shared_ptr
	 * @param nameEvent
	 * return true if event was finded
	 */
	bool ifEventExist(const string& nameEvent);

	/**
	 * search an existing event in birtday, meeting and trip maps
	 * @param name of searching event
	 * return 1 if the event was finded in birthday map
	 * return 2 if the event was finded in meeting map
	 * return 3 if the event was finded in trip map
	 */
	int findInTypeMap(const string& name);

	/**
	 * delete event if it exists
	 * @param nameEvent
	 * return true if event was deleted
	 */
	bool deleteEvent(const string& nameEvent);

	/**
	 * change name of event
	 * @param oldName
	 * @param newName
	 * return false if an event with the same name already exists
	 */
	bool changeNameEvent(const string& oldName, const string& newName);

	/**
	 * change name of event
	 * @param nameEvent
	 * @param newDate
	 * return false if an event with the same name already exists
	 */
	bool changeDate(const string& nameEvent, const Date& newDate);

	/**
	 * change end time of meeting
	 * @param nameMeeting
	 * @param endTime
	 * return false if changing was failed
	 */
	bool changeEndTime(const string& nameMeeting, const Date& endTime);

	/**
	* change end date of trip
	* @param nameTrip
	* @param newDate
	* return false if changing was failed
	*/
	bool changeEndDate(const string& nameTrip, const Date& newDate);

	/**
	* change repetition
	* @param nameEvent
	* @param newRep
	* return false if changing was failed
	*/
	bool changeRepetition(const string& nameEvent, repetitionOfAnEvent newRep);

	/**
	 * change country of trip
	 * @param name
	 * @param newCountry
	 */
	void changeCountryOfTrip(const string& name, const string& newCountry);

	/**
	 * change place of meeting
	 * @param name
	 * @param newPlace
	 */
	void changePlaceOfMeeting(const string& name, const string& newPlace);

	/**
	 * move event for certain days
	 * @param nameEvent
	 * @param amountOfDays on which you need to move events
	 */
	void moveEventForDays(const string& nameEvent, int amountOfDays);

	/**
	 * search day that no has events
	 * @param date of start
	 * return the first date without events after the day
	 */
	Date searchTheEarestFreeDate(const Date& date);

	/**
	 * move event to the earest free date
	 * @param eventName for moving
	 */
	void moveEventToTheEarestFreeDate(const string& eventName);

	/**
	 * print the title with the name of the month
	 * @param month [0-11]
	 */
	void headerMonth(int month) const;

	/**
	 * print the title with wdays
	 */
	void headerWdays() const;

	/**
	 * print daily calendar
	 * @param date for which want to print the daily calendar
	 */
	void getDailyCalendar(const Date& date);

	/**
	 * print weekly calendat of events that start on the days of the week in which the date is, start of calendar is Sunday
	 * @param date for which want to print the weekly calendar
	 */
	void getWeeklyCalendar(const Date& date);

	/**
	 * print events that start on the days of the month in which the date is
	 * @param date for which want to print the monthly calendar
	 */
	void getMonthlyCalendar(const Date& date);
private:
	EventMaps calendarEvent;
	MeetingMap calendarMeetings;
	TripMap calendarTrips;

	/**
 * calculate how many spaces should be left and right so that the word with this lenghth is in the middle of a segment of a certain size
 * @param begin count of whitespace that will be left
 * @param end count of whitespace that will be right
 * @param lengthSegment
 * @param lengthWord
 */
	void getSizeWhitespaces(int& begin, int& end, int lengthSegment, int lengthWord) const;

	/**
	 * print a line separator
	 * @param size of line of '-'
	 */
	void hearderLine(int size) const;

	/**
	 * print whitespace size times
	 * @param size of segment with whitespaces
	 */
	void printWhitespace(int size) const;
};

#endif // CALENDAR_H
