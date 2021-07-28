#ifndef EVENT_H
#define EVENT_H

#include<string>
#include <memory>

#include "Date.h"

/**
 * @enum repetitionOfAnEvent
 * represent types of repetition of event
 */
enum repetitionOfAnEvent
{
	daily,
	weekly,
	monthly,
	yearly,
	oneTime
};
/**
 * @class Event
 * parent class for 3 types of event, store the same event information, change the same parameters
 */
class Event
{
public:
	/**
	 * constructor for Meeting and Trip. can set a repetition of event
	 * @param name
	 * @param date
	 * @param repetition
	 */
	Event(const string& name, const Date& date, repetitionOfAnEvent repetition);
	/**
	 * constructor for Birthday. can not set a repetition of event, repetition is yearly always
	 * @param name
	 * @param date
	 */
	Event(const string& name, const Date& date);

	virtual ~Event();

	/**
	 * change name of event
	 * @param newName
	 */
	void changeName(const string& newName);

	/**
	 * change repetition of event
	 * @param newRepetition - enum type repetitionOfAnEvent
	 * return true always
	 */
	virtual bool changeRepetition(repetitionOfAnEvent newRepetition);

	/**
	 * a pure virtual function
	 * @param otherDate
	 */
	virtual bool changeDate(const Date& otherDate) = 0;

	/**
	 * a pure virtual function
	 * @param moveDay
	 */
	virtual void moveDay(int moveDay) = 0;

	/**
	 * a pure virtual function
	 * @param os
	 */
	virtual void Print(ostream& os)const = 0;

	/**
	 * a pure virtual function
	 * @param os
	 */
	virtual void printName(ostream& os)const = 0;

	/**
	 * getter of date
	 * return Date
	 */
	Date getDate()const;

	/**
	 * getter of name
	 * return name
	 */
	string getName()const;

	/**
	 * getter of repetition
	 * return repetitionOfAnEvent
	 */
	repetitionOfAnEvent getRepetition()const;
protected:
	string name; //must be unique
	Date date;
	repetitionOfAnEvent repetition;
};
#endif // EVENT_H
