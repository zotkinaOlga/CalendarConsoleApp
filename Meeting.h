#ifndef MEETING_H
#define MEETING_H

#include<set>
#include<algorithm>

#include "Event.h"
/**
 * @class Meeting
 * child class
 * have specific parameters: end time, place of meeting 
 */
class Meeting :public Event
{
public:
	/**
	 * constructor with specific informations
     * @param name
     * @param date
     * @param repetition
	 * @param endTime
     * @param place
	 */
	Meeting(const string& name, const Date& date, repetitionOfAnEvent repetition, const Date& endTime, const string& place);

	/**
	 * change date of the meeting
	 * @param newDate
	 * return true and change date if the meeting last 10 minutes or more
	 */
	bool changeDate(const Date& newDate) override;

	/**
	 * move event for some days: move start date and end time
	 * @param moveDay amount of days to move the event
	 */
	void moveDay(int moveDay) override;

	/**
	 * print meeting
	 * @param os ostream where meeting printing is written
	 */
	void Print(ostream& os)const override;

	/**
	 * print and color name of the meeting
	 * @param os ostream where the meeting printing is written
	 */
	void printName(ostream& os)const override;

	/**
	 * change end time of the meeting
	 * @param newEndTime
	 * return true and change end time if meeting will last 10 minutes or more
	 */
	bool changeEndTime(const Date& newEndTime);
    
	/**
     * getter place
     * return place
     */
    string getPlace() const;

    /**
     * getter endTime
     * return Date
     */
	Date getEndTime()const;
	
    /**
     * setter place
     * @param newPlace
     */
	void setPlace(const string& newPlace);
private:
    Date endTime;
	string place;
};
#endif // MEETING_H
//----------------------------------------------------------
