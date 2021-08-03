#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include "Event.h"

/**
 * @class Task is a child class of class Event and has no variables of its own. 
 * Has a start date and date for which the task should be ready - deadline. 
 * The difference between the start date and the deadline must be at least one second.
 * Change the variables start date and end date (deadline), move the start day and send to stream 'name' or all object variables in a specific format.
 */
class Task :public Event
{
public:
	/**
	 * constructor Task
	 * @param name
	 * @param date
	 * @param newRepetioin
	 * @param deadline
	 * @param decription
	 */
	Task(const string& name, const Date& date, repetitionOfAnEvent newRepetition, const Date& deadline, const string& description);

	/**
	 * Change 'date' if the new start date is not later than the deadline.
	 * @param[in] otherDate
	 * @return 'true' if 'otherDate' is less that the 'endDate' or false if 'otherDate' is grather that the 'endDate'
	 */
	bool changeDate(const Date& otherDate, ostream& os) override;

	/**
	 * Change 'dateEnd' if the deadline is grather than the start date.
	 * @param[in] otherDate
	 * @return 'true' if 'otherDate' is grather that the 'startDate' or false if 'otherDate' is less that the 'startDate'
	 */
	bool changeEndDate(const Date& otherDate, ostream& os) override;

	/**
	 * Increase or decrease day of 'date' by a specific integer, but the final date must not be later than 'endDate'.
	 * @param moveDay[in] amount of days, can be positive or negative integer
	 * @return true if the final start date is less that the 'endDate' or false if the final start date is grather that the 'endDate'
	 */
	bool moveDay(int moveDay, ostream& os) override;

	/**
	 * Send all variables of an object to ostream for printing in the format:
	 * "Task: 'name'
	 *  Date: day_of_week day month year hour:minute
	 *  Deadline: day_of_week day month year hour:minute
	 *  Description: 'description'"
	 * @param os[in, out] stream to which the data for printing is sent
	 */
	void print(ostream& os) const override;

	/**
	 * Send 'name' to stream for printing and color the output line red.
	 * If 'name' is longer than 13 characters, cut up to 10 characters and append "..." to the end. 
	 * If 'name' is shorter than 13 characters, increase the size to 13 
	 * @param os[in, out] ostream to which the data for printing is sent
	 */
	void printName(ostream& os)const override;

	/**
	 * @return "Deadline"
	 */
	string getEndDateAttribute() const override;
};
#endif // BIRTHDAY_H