#ifndef CALENDAR_H
#define CALENDAR_H

#include <sstream>      // std::ostringstream
#include <cmath> 
#include <fstream>
#include <iomanip>

#include "EventMaps.h"

/**
 * @class Calendar
 * store events using objects that contain maps of these events sorted by name
 */
class Calendar
{
public:
	Calendar();

	/**
	 * Add new object of class Task
	 * @param name[in]
	 * @param date[in]
	 * @param repetition[in]
	 * @param
	 * return true if the task is successfully added
	 */
	bool addTask(const string& name, const Date& date, const Date& deadline, const string& description, repetitionOfAnEvent rep);

	/**
	 * Add new object of class Meeting
	 * @param name[in]
	 * @param date[in]
	 * @param endTime[in]
	 * @param description[in]
	 * @param rep repetitionOfAnEvent[in]
	 * return true if the meeting is successfully added
	 */
	bool addMeeting(const string& name, const Date& date, const Date& endTime, const string& description, repetitionOfAnEvent rep);

	/**
	 * Add new object of class Trip
	 * @param name[in]
	 * @param startDate[in]
	 * @param endDate[in]
	 * @param description[in]
	 * @param rep repetitionOfAnEvent[in]
	 * @return true if the trip is successfully added
	 */
	bool addTrip(const string& name, const Date& startDate, const Date& endDate, const string& description, repetitionOfAnEvent rep);

	/**
	 * Find in map compared by name iterator of the event
	 * @param nameEvent that is finded
	 * @return shared_ptr of the event
	 */
	const shared_ptr<Event> findEvent(const string& nameEvent);

	/**
	 * Find in map compared by name iterator of the event and get its shared_ptr
	 * @param nameEvent
	 * @return true if event was finded
	 */
	bool ifEventExist(const string& nameEvent);

	/**
	 * Delete event with variable 'name' which is equel to 'nameEvent' from 'eventByName' if event with this name exists.
	 * @param nameEvent[in]
	 * @return true if event was found and so was successfully deleted
	 */
	bool deleteEvent(const string& nameEvent);

	/**
	 * Change 'name' of the event with variable 'name' == 'oldName' if the event was found in ''
	 * @param oldName[in]
	 * @param newName[in]
	 * @return false if an event with the same name already exists
	 */
	bool changeNameEvent(const string& oldName, const string& newName);

	/**
	 * change name of event
	 * @param nameEvent
	 * @param newDate
	 * return false if an event with the same name already exists
	 */
	bool changeDate(const string& nameEvent, const Date& newDate, ostream& os);

	/**
	* change end date 
	* @param name
	* @param newDate
	* return false if changing was failed
	*/
	bool changeEndDate(const string& name, const Date& newDate, ostream &os);

	/**
	* change repetition
	* @param nameEvent[in]
	* @param newRepetition[in]
	* return false if changing was failed
	*/
	bool changeRepetition(const string& nameEvent, repetitionOfAnEvent newRepetition, ostream& os);

	void changeDescription(const string& name, const string& newDescription);

	/**
	 * move event for certain days
	 * @param nameEvent
	 * @param amountOfDays on which you need to move events
	 */
	bool moveEventForDays(const string& nameEvent, int amountOfDays, ostream& os);

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
	void headerMonth(int month, ostream& os) const;

	/**
	 * print the title with wdays
	 */
	void headerWdays(ostream& os) const;

	/**
	 * print daily calendar
	 * @param date for which want to print the daily calendar
	 */
	void getDailyCalendar(const Date& date, ostream& os);

	/**
	 * print weekly calendat of events that start on the days of the week in which the date is, start of calendar is Sunday
	 * @param date for which want to print the weekly calendar
	 */
	void getWeeklyCalendar(const Date& date, ostream& os);

	/**
	 * print events that start on the days of the month in which the date is
	 * @param date for which want to print the monthly calendar
	 */
	void getMonthlyCalendar(const Date& date, ostream& os);
private:
	EventMaps calendarEvent;

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
	void hearderLine(int size, ostream& os) const;

	/**
	 * print whitespace size times
	 * @param size of segment with whitespaces
	 */
	void printWhitespace(int size, ostream&) const;
};

#endif // CALENDAR_H
