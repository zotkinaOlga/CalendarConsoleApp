#ifndef MEETINGMAP_H
#define MEETINGMAP_H

#include <map>

#include "Meeting.h"
/**
 * @class MeetingMap
 * change specific parameters of meeting
 */
class MeetingMap
{
public:
	/**
	 * add meeting
	 * @param ptr shared_ptr meeting
	 */
	void addMeeting(const shared_ptr<Meeting> ptr);

	/**
	 * find iterator meeting
	 * @param name
	 * return iterator meeting
	 */
	map<string, shared_ptr<Meeting>>::iterator findIteratorMeeting(const string& name);

	/**
	 * check if meeting exist
	 * @param name
	 * return true if metting exist
	 */
	bool ifMeetingExist(const string& name);

    /**
     * overwrite event with new name if event exist
     * @param oldName
     * @param newName
     */
    void tryOverwriteName(const string& oldName, const string& newName);

	/**
	 * @param name
	 * @param newEndTime
	 * return false if changing was failed
	 */
	bool changeEndTimeOf(const string& name, const Date& newEndTime);

	/**
	 * change place of meeting
	 * @param name
	 * @param newPlace
	 */
	void changePlaceOf(const string& name, const string& newPlace);

private:
	map<string, shared_ptr<Meeting>> meetingByName;
};

#endif // MEETINGMAP_H
