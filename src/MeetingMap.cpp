#include "MeetingMap.h"

void MeetingMap::addMeeting(const shared_ptr<Meeting> ptr) {
	meetingByName.emplace(ptr->getName(), ptr);
}

map<string, shared_ptr<Meeting>>::iterator MeetingMap::findIteratorMeeting(const string& name)
{
	auto it = meetingByName.find(name);
	return it;
}

bool MeetingMap::ifMeetingExist(const string& name)
{
	return findIteratorMeeting(name)!=meetingByName.end();
}

void MeetingMap::tryOverwriteName(const string& oldName, const string& newName)
{
    auto it = findIteratorMeeting(oldName);
    if(it == meetingByName.end()) return;
    meetingByName.emplace(newName,it->second);
    meetingByName.erase(oldName);
}

bool MeetingMap::changeEndTimeOf(const string& name, const Date& newEndTime)
{
	auto it = findIteratorMeeting(name);
	return it->second->changeEndTime(newEndTime);
}

void MeetingMap::changePlaceOf(const string& name, const string& newPlace)
{
	auto it = findIteratorMeeting(name);
	it->second->setPlace(newPlace);
}
