#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <ctime>
#include <utility>
#include <algorithm>
#include <string>
#include <cstring>

#include "Calendar.h"

using namespace std;

enum MAIN_COMMAND{COMMAND_QUIT, COMMAND_ADD, COMMAND_DELETE, COMMAND_CHANGE, COMMAND_PRINT, COMMAND_MOVE, COMMAND_SEARCH, COMMAND_EXPORT, COMMAND_IMPORT};
enum EVENT_TYPE{EV_RETURN, BIRTHDAY, MEETING, TRIP};
enum CALENDAR_TYPE{C_RETURN, C_DAILY, C_WEEKLY, C_MONTHLY};
enum CHANGE_COMMAND{CH_RETURN, CHANGE_NAME, CHANGE_START_DATE, CHANGE_END, CHANGE_REPETITION, CHANGE_DESCRIPTION};
enum SEARCH_COMMAND{S_RETURN, SEARCH_EVENT, SEARCH_FD};
enum MOVE_COMMAND {M_RETURN, MOVE_SD, MOVE_FD};

/**
 * @class Interface
 * processe commands, work with the console - receive and write messages
 */
class Interface
{
public:
	Interface();

	/**
	 * call processCommand until it returns true
	 * create object of Calendar
	 */
	void startAplication();

	/**
	 * Process command of main menu
	 * @param calendar[in, out]
	 * @return false if command "quit"
	 */
	bool processCommand(Calendar& calendar);

	/**
	 * check main command
	 * @param command
	 * @param max number of command
	 * return false if command is failed
	 */
	bool checkCommand(char command, char max) const;

	/**
	 * check cin
	 * @param cin
	 * return false if cin is failed
	 */
	bool checkCin(istream& cin) const;

	/**
	 * get from console type of event
	 * return type of event
	 */
	EVENT_TYPE enterTypeEvent() const;

	/**
	 * get from console name of event
	 * @param calendar
	 * return name of event
	 */
	string enterName(Calendar& calendar) const;

	/**
	 * get from console date with time
	 * @param typeDate show the user which type of date is expected to be input
	 * return date
	 */
	Date enterDateWithTime(const string& typeDate) const;

	/**
	 * get from console date without time
	 * @param typeDate show the user which type of date is expected to be input
	 * return date
	 */
	Date enterDateWithoutTime(const string& typeDate) const;

	/**
	 * check if struct tm is valid
	 * @param t
	 * return true if tm is valid
	 */
	bool ifTmValid(tm t) const;

	/**
	 * get from console hour and minute
	 * @param t
	 * return Date endTime
	 */
	Date enterEndTime(struct tm t) const;

	/**
	 * get from console string
	 * @param forPrint show the user which string type parameter is expected to be input
	 * return string
	 */
	string enterString(const string& forPrint) const;

	/**
	 * get from console hour and minute
	 * return amount of day for moving event
	 */
	int enterAmountOfDay() const;

	/**
	 * get from console type of repetition of event
	 * return repetitionOfAnEvent of event
	 */
	repetitionOfAnEvent enterRepetition() const;

	/**
	 * print main menu and get from console main command
	 * return valid main command
	 */
	MAIN_COMMAND mainMenu() const;

	/**
	 * print add menu
	 * @param calendar
	 */
	void addMenu(Calendar& calendar);

	/**
	 * get from console new name
	 * @param calendar
	 */
	string enterNameNewEvent(Calendar& calendar) const;

	/**
	 * get from console parameters of task
	 * call finction which add task to calendar
	 * @param calendar
	 */
	void addTaskMenu(Calendar& calendar);

	/**
	 * get from console parameters of meeting
	 * call finction which add meeting to calendar
	 * @param calendar
	 */
	void addMeetingMenu(Calendar& calendar);

	/**
	 * get from console parameters of trip
	 * call finction which add trip to calendar
	 * @param calendar
	 */
	void addTripMenu(Calendar& calendar);

	/**
	 * print delete menu
	 * @param calendar
	 */
	void deleteMenu(Calendar& calendar);

	/**
	 * call function which print move menu
	 * call function which move event
	 * @param calendar
	 */
	void moveMenu(Calendar& calendar);

	/**
	 * print move menu and get from console move command
	 * return valid move command
	 */
	MOVE_COMMAND printMoveMenu() const;

	/**
	 * print task change menu
	 * @param name
	 * @param calendar
	 */
	void changeMenu(const string& name, Calendar& calendar);

	/**
	 * print change menu of task and get from console change command
	 * return valid change command
	 */
	CHANGE_COMMAND printChangeMenu(const shared_ptr<Event> ptr) const;

	/**
	 * change name of all types of event
	 * @param oldName
	 * @param calendar
	 */
	void changeName(const string& oldName, Calendar& calendar);

	void changeStartDate(const string& name, Calendar& calendar);

	void changeEndDate(const string& name, Calendar& calendar);

	void changeEndTime(shared_ptr<Event> itEvent, const string& name, Calendar& calendar);

	void changeEndWholeDate(const string& name, const string& endAttribute, Calendar& calendar);

	void changeRepetition(const string& name, Calendar& calendar);

	void changeDescription(const string& name, Calendar& calendar);

	/**
	 * search menu
	 * @param calendar
	 */
	void searchMenu(Calendar& calendar) const;

	/**
	 * print search menu and get from console search command
	 * return valid search command
	 */
	SEARCH_COMMAND printSearchMenu() const;

	void searchEvent(Calendar& calendar) const;

	void searchFreeDay(Calendar& calendar) const;

	/**
	 * call function which get a certain type of calendar
	 * call function which will print a certain type of calendar
	 * @param calendar
	 */
	void printMenu(Calendar& calendar) const;

	/**
	 * print menu with types of calendar and get from console type of calendar: daily, weekly, monthly
	 * return valid type of calendar
	 */
	CALENDAR_TYPE printPrintMenu() const;

	void printDailyCalendar(Calendar& calendar) const;

	void printWeeklyCalendar(Calendar& calendar) const;

	void printMonthlyCalendar(Calendar& calendar) const;

	/**
	 * print export menu and export an event to file that has name of the event
	 * @param calendar
	 */
	void exportMenu(Calendar& calendar) const;

	/**
	 * get name of file and type of event
	 * call import function for a certain type of event while file is not end
	 * @param calendar
	 */
	void importMenu(Calendar& calendar);

	/**
	 * import events only task type
	 * @param calendar
	 * @param file
     * return true if the task is successfully imported
	 */
	bool importTask(Calendar& calendar, ifstream& file);

	/**
	 * import meeting
	 * @param calendar
	 * @param file
     * return true if the meeting is successfully imported
	 */
	bool importMeeting(Calendar& calendar, ifstream& file);

	/**
	 * import trip
	 * @param calendar
	 * @param file
     * return true if the trip is successfully imported
	 */
	bool importTrip(Calendar& calendar, ifstream& file);

	/**
	 * determine what type of repetition is the string that entered the input
	 * @param s input string
	 * return repetitionOfAnEvent
	 */
	repetitionOfAnEvent getRepetition(const string& s) const;
};
#endif //CONSOLE_H

