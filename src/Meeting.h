#ifndef MEETING_H
#define MEETING_H

#include<set>
#include<algorithm>

#include "Event.h"
/**
 * @class Meeting is a child class of class Event and no has own variables.
 * The difference in minutes between the start time and the end time must be at least 10 minutes.
 * The meeting takes description on a specific day and cannot spill over into another, so the end time is always less than 00:00.
 * Provide printing an Meeting's object and changing variables 'date' and 'endDate'.
 */
class Meeting :public Event
{
public:
	/**
	 * Constructor
	 * @param name
	 * @param date
	 * @param repetition
	 * @param endTime
	 * @param description
	 */
	Meeting(const string& name, const Date& date, repetitionOfAnEvent repetition, const Date& endTime, const string& description);

	/**
	 * Change 'date' of the meeting to other date.
	 * Check that the meeting with 'newDate' last 10 minutes or more.
	 * @param newDate[in]
	 * @param os[in, out]
	 * @return true and change date if 
	 */
	bool changeDate(const Date& newDate, ostream& os) override;

	/**
	 * Change 'endDate' of the meeting to other time in this day.
	 * @param newEndDate[in]
	 * @return true and change 'endDate' if the meeting with 'newEndDate' last 10 minutes or more or false if no and leave original end time
	 */
	bool changeEndDate(const Date& newEndDate, ostream& os);

	/**
	 * Send 'name', 'date', 'endDate' and 'description' to ostream for printing in the format:
	 * "Meeting: 'name' 
	 *	Date: day_of_week day month year hour:minute
	 *  End time: hour:minute
	 *  Description: 'description'".
	 * @param os[in, out] stream to which the data for printing is sent
	 */
	void print(ostream& os) const override;

	/**
	 * Send 'name' to stream for printing and color the output line yellow.
	 * If 'name' is longer than 13 characters, cut up to 10 characters and append "..." to the end.
	 * If 'name' is shorter than 13 characters, increase the size to 13.
	 * @param os[in, out] ostream to which the data for printing is sent
	 */
	void printName(ostream& os) const override;

	/**
	 * @return "End time" 
	 */
	string getEndDateAttribute() const override;
};
#endif // MEETING_H
//----------------------------------------------------------
