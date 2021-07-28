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

enum MAIN_COMMAND{COM_QUIT, COM_ADD, COM_DELETE, COM_CHANGE, COM_PRINT, COM_MOVE, COM_SEARCH, COM_EXPORT, COM_IMPORT};
enum EVENT_TYPE{EV_RETURN, BIRTHDAY, MEETING, TRIP};
enum CALENDAR_TYPE{C_RETURN, C_DAILY, C_WEEKLY, C_MONTHLY};
enum CHANGE_COMMAND{CH_RETURN, CHANGE_NAME, CHANGE_START_DATE, CHANGE_END, CHANGE_REPETITION, CHANGE_COUNTRY = 5, CHANGE_PLACE = 5};
enum SEARCH_COMMAND{S_RETURN, SEARCH_EVENT, SEARCH_FD};
enum MOVE_COMMAND {M_RETURN, MOVE_SD,MOVE_FD};

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
	 * process main command
	 * @param calendar
	 * return false if was command "quit"
	 */
	bool processCommand(Calendar& calendar);

	/**
	 * check main command
	 * @param command
	 * @param max number of command
	 * return false if command is failed
	 */
	bool checkCommand(char command, char max);

	/**
	 * check cin
	 * @param cin
	 * return false if cin is failed
	 */
	bool checkCin(istream& cin);

	/**
	 * get from console type of event
	 * return type of event
	 */
	EVENT_TYPE enterTypeEvent();

	/**
	 * get from console name of event
	 * @param calendar
	 * return name of event
	 */
	string enterName(Calendar& calendar);

	/**
	 * get from console date with time
	 * @param typeDate show the user which type of date is expected to be input
	 * return date
	 */
	Date enterDateWithTime(const string& typeDate);

	/**
	 * get from console date without time
	 * @param typeDate show the user which type of date is expected to be input
	 * return date
	 */
	Date enterDateWithoutTime(const string& typeDate);

	/**
	 * check if struct tm is valid
	 * @param t
	 * return true if tm is valid
	 */
	bool ifTmValid(tm t);

	/**
	 * get from console hour and minute
	 * @param t
	 * return Date endTime
	 */
	Date enterEndTime(struct tm t);

	/**
	 * get from console string
	 * @param proPrint show the user which string type parameter is expected to be input
	 * return string
	 */
	string enterString(const string& proPrint);

	/**
	 * get from console hour and minute
	 * return amount of day for moving event
	 */
	int enterAmountOfDay();

	/**
	 * get from console type of repetition of event
	 * return repetitionOfAnEvent of event
	 */
	repetitionOfAnEvent enterRepetition();

	/**
	 * get from console type of repetition of trip, check that the trip will no conflict with itself
	 * @param start date
	 * @param end date
	 * return repetitionOfAnEvent of trip
	 */
	repetitionOfAnEvent enterRepetitionTrip(const Date& start, const Date& end);

	/**
	 * print main menu and get from console main command
	 * return valid main command
	 */
	MAIN_COMMAND mainMenu();

	/**
	 * print add menu
	 * @param calendar
	 */
	void addMenu(Calendar& calendar);

	/**
	 * get from console new name
	 * @param calendar
	 */
	string enterNameNewEvent(Calendar& calendar);

	/**
	 * get from console parameters of birthday
	 * call finction which add birthday to calendar
	 * @param calendar
	 */
	void addBirthdayMenu(Calendar& calendar);

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
	MOVE_COMMAND printMoveMenu();

	/**
	 * change name of all types of event
	 * @param oldName
	 * @param calendar
	 */
	void changeName(const string& oldName, Calendar& calendar);

	/**
	 * print birtday change menu
	 * @param name
	 * @param calendar
	 */
	void birthdayChangeMenu(const string& name, Calendar& calendar);

	/**
	 * print change menu of birthday and get from console change command
	 * return valid change command
	 */
	CHANGE_COMMAND printBirthdayChangeMenu();

	/**
	 * print meeting change menu
	 * @param name
	 * @param calendar
	 */
	void meetingChangeMenu(const string& name, Calendar& calendar);

	/**
	 * print change menu of metting and get from console change command
	 * return valid change command
	 */
	CHANGE_COMMAND printMeetingChangeMenu();

	/**
	 * print trip change menu
	 * @param name
	 * @param calendar
	 */
	void tripChangeMenu(const string& name, Calendar& calendar);

	/**
	 * print change menu of trip and get from console change command
	 * return valid change command
	 */
	CHANGE_COMMAND printTripChangeMenu();

	/**
	 * search menu
	 * @param calendar
	 */
	void searchMenu(Calendar& calendar);

	/**
	 * print search menu and get from console search command
	 * return valid search command
	 */
	SEARCH_COMMAND printSearchMenu();

	/**
	 * call function which get a certain type of calendar
	 * call function which will print a certain type of calendar
	 * @param calendar
	 */
	void printMenu(Calendar& calendar);

	/**
	 * print menu with types of calendar and get from console type of calendar: daily, weekly, monthly
	 * return valid type of calendar
	 */
	CALENDAR_TYPE printPrintMenu();

	/**
	 * print export menu and export an event to file that has name of the event
	 * @param calendar
	 */
	void exportMenu(Calendar& calendar);

	/**
	 * get name of file and type of event
	 * call import function for a certain type of event while file is not end
	 * @param calendar
	 */
	void importMenu(Calendar& calendar);

	/**
	 * import birthday
	 * @param calendar
	 * @param file
     * return true if the birthday is successfully imported
	 */
	bool importBirthday(Calendar& calendar, ifstream& file);

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
	repetitionOfAnEvent getRepetition(const string& s);
};
#endif //CONSOLE_H

