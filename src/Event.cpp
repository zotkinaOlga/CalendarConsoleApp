#include "Event.h"
#include "constants.h"

Event::Event(const string& name, const Date& date, repetitionOfAnEvent repetition, const Date& endDate, const string& description)
	: name(name), date(date), repetition(repetition), endDate(endDate), description(description){}

Event::~Event(){}

void Event::changeName(const string& newName)
{
	name = newName;
}

bool Event::changeRepetition(repetitionOfAnEvent newRepetition, ostream& os)
{
	repetition = newRepetition;
	return true;
}

bool Event::moveDay(int moveDay, ostream& os)
{
	date = Date(date.getYear(), date.getIntMonth() + 1, date.getDay() + moveDay, date.getHour(), date.getMinute());
	endDate = Date(endDate.getYear(), endDate.getIntMonth() + 1,
		endDate.getDay() + moveDay, endDate.getHour(), endDate.getMinute());
	return true;
}

void Event::changeDescription(const string& newDescription)
{
	description = newDescription;
}

void Event::printAttribute(ostream& os) const
{
	os << "1. Name" << endl
		<< "2. Start date" << endl 
		<< "3. " << getEndDateAttribute() << endl
		<< "4. Repetition" << endl
		<< "5. Description" << endl;
}

Date Event::getDate() const
{
	return date;
}
string Event::getName() const
{
	return name;
}
repetitionOfAnEvent Event::getRepetition() const
{
	return repetition;
}

Date Event::getEndDate() const
{
	return endDate;
}

string Event::getDescription() const
{
	return description;
}
