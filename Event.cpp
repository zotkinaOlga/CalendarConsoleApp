#include "Event.h"
#include "konstanty.h"

Event::Event(const string& name, const Date& date, repetitionOfAnEvent repetition) : name(name), date(date), repetition(repetition)
{
}
Event::~Event()
{
}
Event::Event(const string& name, const Date& date) : name(name), date(date)
{
	repetition = oneTime;
}
void Event::changeName(const string& newName)
{
	name = newName;
}
bool Event::changeRepetition(repetitionOfAnEvent newRepetition)
{
	repetition = newRepetition;
	return true;
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
