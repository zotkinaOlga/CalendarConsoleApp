#ifndef TRIP_H
#define TRIP_H
#include "Event.h"

/**
 * @class Trip is a child class of class Event and no has own variables.
 * The trip must last for at least one day and must not conflict with dates by itself.
 * Provide printing an Trip object and changing all variables.
 */
class Trip : public Event
{
public:
	/**
	 * Constructor with specific informations
	 * @param name
	 * @param startDate
	 * @param rep
	 * @param endDate at least a day later than the start time
	 * @param description
	 */
	Trip(const string& name, const Date& startDate, repetitionOfAnEvent rep, const Date& endDate, const string& description);

	/**
	 * Change 'repetition' to any value.
	 * Start date and end date must not overlap.
	 * @param newRepetition[in]
	 * @return true if the trip will not conflict with dates by itself and change 'repetition' or false if will be conflict and leave original argument
	 */
	bool changeRepetition(repetitionOfAnEvent newRepetition, ostream& os) override;

	/**
	 * Change 'date' and check that the trip will be longer that 1 day.
	 * @param otherDate[in]
	 * @return true if difference between 'date' and 'endDate' at least one day and change start date or false if not
	 */
	bool changeDate(const Date& otherDate, ostream& os) override;

	/**
	 * Change 'endDate' and check that 'date' more that 'otherDate' for at least 1 day.
	 * @param otherDate[in]
	 * @return true if the trip will be longer that 1 day and change 'endDate' or false if no and leave original end date
	 */
	bool changeEndDate(const Date& otherDate, ostream& os) override;

	/**
	 * Send variables 'name', 'date', 'endDate' and 'descriprion' of an object to ostream for printing in the format:
	 * "Trip: 'name'
	 *	Start date: day_of_week day month year hour:minute
	 *  End date: day_of_week day month year hour:minute
	 *  Description: 'description'".
	 * @param os[in, out] stream to which the data for printing is sent
	 */
	void print(ostream& os) const override;

	/**
	 * Send 'name' to stream for printing and color the output line blue.
	 * If 'name' is longer than 13 characters, cut up to 10 characters and append "..." to the end.
	 * If 'name' is shorter than 13 characters, increase the size to 13
	 * @param os[in, out] ostream to which the data for printing is sent
	 */
	void printName(ostream& os) const override;

	/**
	 * @return "End date" 
	 */
	string getEndDateAttribute() const override;
};

//----------------------------------------------------------

#endif // TRIP_H
