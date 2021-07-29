#ifndef TRIP_H
#define TRIP_H
#include "Event.h"

/**
 * @class Trip
 * child class
 * store specific parameters: end date of the trip, destination country
 * trip must last for at least one day and must not conflict with dates by itself
 */
class Trip : public Event
{
public:
	/**
	 * constructor with specific informations
	 * @param name
	 * @param startDate
	 * @param rep
	 * @param endDate
	 * @param country
	 */
	Trip(const string& name, const Date& startDate, repetitionOfAnEvent rep, const Date& endDate, const string& country);

	/**
	 * change the start date of the trip
	 * @param otherDate
	 * return true if difference between start date of the trip and end date of the trip at least one day and change start date
	 */
	bool changeDate(const Date& otherDate) override;

	/**
	 * change the repetition of the trip
	 * @param newRepetition
	 * return true if the trip will not conflict with dates by itself
	 */
	bool changeRepetition(repetitionOfAnEvent newRepetition) override;

	/**
	 * move the trip for some days, move start date and end date for some days
	 * @param moveDay amount of days to move the trip
	 */
	void moveDay(int moveDay) override;

	/**
	 * print the trip
	 * @param os ostream where the trip printing is written
	 */
	void print(ostream& os) const override;

	/**
	 * print and color name of the trip
	 * @param os ostream where the trip printing is written
	 */
	void printName(ostream& os) const override;

	/**
	 * change end date of the trip and check that the trip will be longer that 1 day
	 * @param otherDate
	 * return true if the trip will be longer that 1 day and change old end date
	 */
	bool changeEndDate(const Date& otherDate);

	/**
	 * getter country
	 * return country
	 */
	string getCountry()const;

	/**
	 * getter endDate
	 * return Date
	 */
	Date getEndDate()const;

	/**
	 * setter country
	 * @param otherCountry
	 */
	void setCountry(const string& otherCountry);

private:
	Date endDate;
	string country;
};

//----------------------------------------------------------

#endif // TRIP_H
