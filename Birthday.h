#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include "Event.h"

/**
 * @class Birthday
 * child class
 * no have special parameters
 */
class Birthday :public Event
{
public:
	/**
	 * constructor Birthday, repetition = yearly always
	 * @param name
	 * @param date
	 */
	Birthday(const string& name, const Date& date);

	/**
	 * change date of birthday
	 * @param otherDate
	 * return true always
	 */
	bool changeDate(const Date& otherDate) override;

	/**
	 * birthday may be only yearly. cannot change repetition of birthdays
	 * @param newRepetition
	 * return false always
	 */
	bool changeRepetition(repetitionOfAnEvent newRepetition) override;

	/**
	 * move birthday for some days
	 * @param moveDay amount of days to move the birthday
	 */
	void moveDay(int moveDay) override;

	/**
	 * print birthday
	 * @param os ostream where birthday printing is written
	 */
	void Print(ostream& os)const override;

	/**
	 * print and color name of birthday
	 * @param os ostream where birthday printing is written
	 */
	void printName(ostream& os)const override;
};
#endif // BIRTHDAY_H