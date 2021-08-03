#ifndef EVENT_H
#define EVENT_H

#include<string>
#include <memory>

#include "Date.h"

/**
 * @enum repetitionOfAnEvent
 * represent how often the event repeats
 */
enum repetitionOfAnEvent
{
	daily, ///< an event repeats every day 
	weekly, ///< an event repeats every week 
	monthly, ///< an event repeats every month
	yearly, ///< an event repeats every year
	oneTime ///< an event repeats once
};
/**
 * @class Event
 * A pure virtual class, parent class for 3 classes: Task, Meeting and Trip.
 * Change variable 'name' and 'description' for all classes, variable 'repetition' for classes Task and Meeting, 
 * increase or  'date' for some days for .
 * Value of variable 'name' must be unique.
 */
class Event
{
public:
	/**
	 * @param name
	 * @param date
	 * @param repetition
	 */
	Event(const string& name, const Date& date, repetitionOfAnEvent repetition, const Date &endDate, const string& description);

	virtual ~Event();

	/**
	 * Change 'name' to anyone value.
	 * Is used by all child classes.
	 * @param newName[in]
	 */
	void changeName(const string& newName);

	/**
	 * Change 'repetition' to anyone value. 
	 * Is used by child classes Task and Meeting.
	 * @param newRepetition[in]
	 * @return true always 
	 */
	virtual bool changeRepetition(repetitionOfAnEvent newRepetition, ostream& os);

	/**
	 * A pure virtual function for changing variable 'date'.
	 * @param otherDate[in]
	 * @param os[int, out]
	 * @return true or false
	 */
	virtual bool changeDate(const Date& otherDate, ostream& os) = 0;

	/**
	 * A pure virtual function for changing variable 'dateEnd'.
	 * @param otherDate[in]
	 * @param os[int, out]
	 * @return true or false
	 */
	virtual bool changeEndDate(const Date& otherDate, ostream& os) = 0;

	/**
	 * Virtual function for increasing or decreasing day of 'date' and 'endDate'. 
	 * Is used by child classes Meeting and Trip.
	 * @param moveDay[in]
	 * @param os[int, out]
	 * @return true always
	 */
	virtual bool moveDay(int moveDay, ostream& os);

	/**
	 * Change 'description' to anyone value.
	 * Is used by all child classes.
	 * @param newDescription[in]
	 */
	void changeDescription(const string& newDescription);

	/**
	 * A pure virtual function.
	 * Send all variables' names and values of an object to ostream for printing in certain format.
	 * @param os[in, out]
	 */
	virtual void print(ostream& os) const = 0;

	/**
	 * Send names of all class's variables to ostream.
	 * @param os[in, out]
	 */
	void printAttribute(ostream& os) const;

	/**
	 * A pure virtual function.
	 * Send 'name' to ostream for printing in certain format and color output in the console.
	 * @param os[in, out]
	 */
	virtual void printName(ostream& os) const = 0;

	Date getDate() const;

	string getName() const;

	repetitionOfAnEvent getRepetition() const;

	Date getEndDate() const;

	string getDescription() const;

	/**
	 * @return a specific name for every child class of variable 'endDate' 
	 */
	virtual string getEndDateAttribute() const = 0;
protected:
	string name;
	Date date;
	repetitionOfAnEvent repetition;
	Date endDate;
	string description;
};
#endif // EVENT_H
