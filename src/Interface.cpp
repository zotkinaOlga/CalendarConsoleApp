#include "Interface.h"
#include <iomanip>
#include "konstanty.h"
Interface::Interface()
{
}

void Interface::startAplication()
{
	Calendar calendar;
	while (true)
	{
		if (!processCommand(calendar))
			return;
	}
}

bool Interface::processCommand(Calendar& calendar)
{
	string type;
	MAIN_COMMAND command = mainMenu();
	if (command == COM_ADD)
	{
		addMenu(calendar);
	}
	else if (command == COM_DELETE)
	{
		deleteMenu(calendar);
	}
	else if (command == COM_MOVE)
	{
		moveMenu(calendar);
	}
	else if (command == COM_CHANGE)
	{
		string name = enterName(calendar);
		int type = calendar.findInTypeMap(name);
		switch (type)
		{
		case 1:
		{
			birthdayChangeMenu(name, calendar);
			break;
		}
		case 2:
		{
			meetingChangeMenu(name, calendar);
			break;
		}
		case 3:
		{
			tripChangeMenu(name, calendar);
			break;
		}
		}
	}
	else if (command == COM_SEARCH)
	{
		searchMenu(calendar);
	}
	else if (command == COM_PRINT)
	{
		printMenu(calendar);
	}
	else if (command == COM_EXPORT)
	{
		exportMenu(calendar);
	}
	else if (command == COM_IMPORT)
	{
		importMenu(calendar);
	}
	else return false; //quit command
	return true;
}

bool Interface::checkCommand(char command, char max)
{
	if (command < '0' || command > max)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Noknown command" << endl;
		return false;
	}
	return true;
}

bool Interface::checkCin(istream& cin)
{
	if (cin.fail()) {
		cout << "Parse failed" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

EVENT_TYPE Interface::enterTypeEvent()
{
	char type;
	while (true)
	{
		cout << endl << "Enter event`s type:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Birthday" << endl
			<< "2. Meeting" << endl
			<< "3. Trip" << endl;
		cin >> type;
		if (checkCin(cin) && checkCommand(type, '3')) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); return (EVENT_TYPE)(type - '0');
		}
	}
}

string Interface::enterName(Calendar& calendar)
{
	string name;
	cout << endl << "Enter event`s name: " << endl;
	getline(cin, name);
	while (!(calendar.ifEventExist(name)))
	{
		cout << "This event no exist" << endl
			<< endl << "Enter event`s name: " << endl;
		getline(cin, name);
	}
	return name;
}

Date Interface::enterDateWithTime(const string& typeDate)
{
	tm t = {};
	do
	{
		cout << endl << "Enter " << typeDate << " date (e.g. 20.02.2020 00:01):" << endl;
		t = {};
		cin >> get_time(&t, "%d.%m.%Y %R");
	} while (!checkCin(cin) || !ifTmValid(t));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Date(t);
}

Date Interface::enterDateWithoutTime(const string& typeDate)
{
	struct tm t = {};
	do
	{
		cout << endl << "Enter " << typeDate << " date (e.g. 20.02.2020):" << endl;
		t = {};
		cin >> get_time(&t, "%d.%m.%Y");
		t.tm_hour = 0;
		t.tm_min = 0;
	} while (!checkCin(cin) || !ifTmValid(t));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Date(t);
}

bool Interface::ifTmValid(struct tm t)
{
	struct tm tTest = {};
	tTest = t;
	timegm(&t);
	if (!(tTest.tm_year == t.tm_year && tTest.tm_mon == t.tm_mon && tTest.tm_mday == t.tm_mday))
	{
		cout << "Invalid date" << endl;
		return false;
	}
	return true;
}

Date Interface::enterEndTime(struct tm t)
{
	do
	{
		cout << endl << "Enter end hour and minute (e.g. 01:01):" << endl;
		cin >> get_time(&t, "%H:%M");
	} while (!checkCin(cin));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Date(t);
}

string Interface::enterString(const string& proPrint)
{
	string s;
	cout << endl << "Enter " << proPrint << endl;
	getline(cin, s);
	return s;
}

int Interface::enterAmountOfDay()
{
	int amountOfDay;
	while (true)
	{
		cout << endl << "Enter amount of day:" << endl;
		cin >> amountOfDay;
		if (checkCin(cin))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return amountOfDay;
		}
	}
}

repetitionOfAnEvent Interface::enterRepetition()
{
	char rep;
	while (true)
	{
		cout << endl << "Enter repetition: " << endl
			<< "0. Daily" << endl
			<< "1. Weekly" << endl
			<< "2. Monthly" << endl
			<< "3. Yearly" << endl
			<< "4. Onetime" << endl;
		cin >> rep;
		if (checkCin(cin) && checkCommand(rep, '4'))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return (repetitionOfAnEvent)(rep - '0');
		}
	}
}

repetitionOfAnEvent Interface::enterRepetitionTrip(const Date& startDate, const Date& endDate)
{
	while (true)
	{
		repetitionOfAnEvent newRepetition = enterRepetition();
		struct tm endTm = endDate.getStructTm();
		struct tm startTm = startDate.getStructTm();
		auto timeDifference = difftime(timegm(&endTm), timegm(&startTm));
		if ((newRepetition == yearly && timeDifference > secInYear)
			|| (newRepetition == monthly && timeDifference > secInTheSmallestMonth)
			|| (newRepetition == weekly && timeDifference > secInWeek)
			|| (newRepetition == daily && timeDifference > secInDay))
		{
			cout << "Trip conflicts with dates by itself" << endl;
		}
		else return newRepetition;
	}
}

MAIN_COMMAND Interface::mainMenu()
{
	char choice;
	while (true)
	{
		cout << endl
			<< "Enter what you want to do with the calendar:" << endl
			<< "0. Quit" << endl
			<< "1. Add event" << endl
			<< "2. Delete event" << endl
			<< "3. Change event" << endl
			<< "4. Print calendar" << endl
			<< "5. Move event for some days or to the earlest free date" << endl
			<< "6. Search event or the earlest free date" << endl
			<< "7. Export event" << endl
			<< "8. Import events" << endl;
		cin >> choice;
		if (checkCin(cin) && checkCommand(choice, '8')) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return (MAIN_COMMAND)(choice - '0');
		}
	}
}

void Interface::addMenu(Calendar& calendar)
{
	EVENT_TYPE type = enterTypeEvent();
	if (type == BIRTHDAY)
	{
		addBirthdayMenu(calendar);
	}
	else if (type == MEETING)
	{
		addMeetingMenu(calendar);
	}
	else if (type == TRIP)
	{
		addTripMenu(calendar);
	}
	else return;
}

string Interface::enterNameNewEvent(Calendar& calendar)
{
	string name;
	cout << endl << "Enter name of new event:" << endl;
	getline(cin, name);
	while (!checkCin(cin) || calendar.ifEventExist(name))
	{
		cout << "Event with this name is already exist" << endl
			<< endl << "Enter name of new event:" << endl;
		getline(cin, name);
	}
	return name;
}

void Interface::addBirthdayMenu(Calendar& calendar)
{
	string name = enterNameNewEvent(calendar);
	Date startDate(enterDateWithoutTime(""));
	calendar.addBirthday(name, startDate);
}

void Interface::addMeetingMenu(Calendar& calendar)
{
	string name = enterNameNewEvent(calendar);
	Date startDate(enterDateWithTime("start"));
	Date endTime = enterEndTime(startDate.getStructTm());
	struct tm startTm = startDate.getStructTm();
	struct tm endTm = endTime.getStructTm();
	while (difftime(timegm(&endTm), timegm(&startTm)) < secInTenMinutes)
	{
		cout << "Meeting lasts less then 10 minutes" << endl;
		endTime = enterEndTime(startDate.getStructTm());
		endTm = endTime.getStructTm();
	}
	calendar.addMeeting(name, startDate, endTime, enterString("place:"), enterRepetition());
}

void Interface::addTripMenu(Calendar& calendar)
{
	string name = enterNameNewEvent(calendar);
	Date startDate(enterDateWithTime("start"));
	Date endDate = enterDateWithTime("end");
	struct tm startTm = startDate.getStructTm();
	struct tm endTm = endDate.getStructTm();
	while (difftime(timegm(&endTm), timegm(&startTm)) < secInDay)
	{
		cout << "Start date is more then end time or trip is less then one day" << endl;
		Date endDate = enterDateWithTime("end");
		endTm = endDate.getStructTm();
	}
	calendar.addTrip(name, startDate, endDate, enterString("country:"), enterRepetitionTrip(startDate, endDate));
}

void Interface::deleteMenu(Calendar& calendar)
{
	calendar.deleteEvent(enterName(calendar));
}

void Interface::moveMenu(Calendar& calendar)
{
	MOVE_COMMAND moveCom = printMoveMenu();
	if (moveCom == MOVE_SD) calendar.moveEventForDays(enterName(calendar), enterAmountOfDay());
	else if (moveCom == MOVE_FD) calendar.moveEventToTheEarestFreeDate(enterName(calendar));
	else return;
}

MOVE_COMMAND Interface::printMoveMenu()
{
	char moveCom;
	do {
		cout << endl << "Enter how you want to move the event:" << endl
			<< "0. Return to main menu" << endl
			<< "1. For some days" << endl
			<< "2. To earest free date" << endl;
		cin >> moveCom;
	} while (!checkCin(cin) || !(checkCommand(moveCom, '2')));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return (MOVE_COMMAND)(moveCom - '0');
}

void Interface::birthdayChangeMenu(const string& name, Calendar& calendar)
{
	CHANGE_COMMAND changeCom = printBirthdayChangeMenu();
	if (changeCom == CHANGE_NAME)
	{
		changeName(name, calendar);
	}
	else if (changeCom == CHANGE_START_DATE) calendar.changeDate(name, enterDateWithoutTime(""));
	else return;
}

CHANGE_COMMAND Interface::printBirthdayChangeMenu()
{
	char changeCom;
	do
	{
		cout << endl << "You can change:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Name" << endl
			<< "2. Date" << endl;
		cin >> changeCom;
	} while (!checkCin(cin) || !checkCommand(changeCom, '2'));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return (CHANGE_COMMAND)(changeCom - '0');
}

void Interface::meetingChangeMenu(const string& name, Calendar& calendar)
{
	CHANGE_COMMAND changeCom = printMeetingChangeMenu();
	if (changeCom == CHANGE_NAME)
	{
		changeName(name, calendar);
	}
	else if (changeCom == CHANGE_START_DATE)
	{
		calendar.changeDate(name, enterDateWithTime("start"));
	}
	else if (changeCom == CHANGE_END)
	{
		tm t = {};
		Date endTime = enterEndTime(t);
		while (!calendar.changeEndTime(name, endTime))
		{
			cout << "Meeting is less then 10 minutes" << endl;
			t = {};
			endTime = enterEndTime(t);
		}
	}
	else if (changeCom == CHANGE_REPETITION)
	{
		calendar.changeRepetition(name, enterRepetition());
	}
	else if (changeCom == CHANGE_PLACE) calendar.changePlaceOfMeeting(name, enterString("new place:"));
	else return;
}

CHANGE_COMMAND Interface::printMeetingChangeMenu()
{
	char changeCom;
	do
	{
		cout << endl << "You can change:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Name" << endl
			<< "2. Start date" << endl
			<< "3. End time" << endl
			<< "4. Repetition" << endl
			<< "5. Place" << endl;
		cin >> changeCom;
	} while (!checkCin(cin) || !checkCommand(changeCom, '5'));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return (CHANGE_COMMAND)(changeCom - '0');
}

void Interface::tripChangeMenu(const string& name, Calendar& calendar)
{
	CHANGE_COMMAND changeCom = printTripChangeMenu();
	if (changeCom == CHANGE_NAME)
	{
		changeName(name, calendar);
	}
	else if (changeCom == CHANGE_START_DATE)
	{
		calendar.changeDate(name, enterDateWithTime("start"));
	}
	else if (changeCom == CHANGE_END)
	{
		Date date = enterDateWithTime("end");
		while (!calendar.changeEndDate(name, date))
		{
			cout << "Trip is less then 1 day" << endl;
			date = enterDateWithTime("end");
		}
	}
	else if (changeCom == CHANGE_REPETITION)
	{
		repetitionOfAnEvent newRep = enterRepetition();
		while (!calendar.changeRepetition(name, newRep))
		{
			cout << "Trip conflicts with dates by itself" << endl;
			newRep = enterRepetition();
		}
	}
	else if (changeCom == CHANGE_COUNTRY) calendar.changeCountryOfTrip(name, enterString("new country:"));
	else return;
}

CHANGE_COMMAND Interface::printTripChangeMenu()
{
	char changeCom;
	do
	{
		cout << endl << "You can change:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Name" << endl
			<< "2. Start date" << endl
			<< "3. End time" << endl
			<< "4. Repetition" << endl
			<< "5. Destination country" << endl;
		cin >> changeCom;
	} while (!checkCin(cin) || !checkCommand(changeCom, '5'));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return (CHANGE_COMMAND)(changeCom - '0');
}

void Interface::changeName(const string& oldName, Calendar& calendar)
{
	string newName = enterString("new name: ");
	while (!calendar.changeNameEvent(oldName, newName))
	{
		cout << "Event with this name is already exist" << endl;
		newName = enterString("new name: ");
	}
}

void Interface::searchMenu(Calendar& calendar)
{
	SEARCH_COMMAND searchCom = printSearchMenu();
	if (searchCom == SEARCH_EVENT)
	{
		string name = enterName(calendar);
		ostringstream oss;
		cout << endl;
		calendar.findEvent(name)->Print(oss);
		cout << oss.str();
	}
	else if (searchCom == SEARCH_FD)
	{
		Date freeDate = calendar.searchTheEarestFreeDate(enterDateWithoutTime(""));
		ostringstream oss;
		freeDate.printDate(oss);
		cout << "The earlest free day is " << oss.str() << endl;
	}
	else return;
}

SEARCH_COMMAND Interface::printSearchMenu()
{
	char searchCom;
	do
	{
		cout << endl << "You can search:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Event" << endl
			<< "2. The earest free date" << endl;
		cin >> searchCom;
	} while (!checkCin(cin) || (!checkCommand(searchCom, '2')));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return (SEARCH_COMMAND)(searchCom - '0');
}

void Interface::printMenu(Calendar& calendar)
{
	CALENDAR_TYPE typeCalendar = printPrintMenu();
	if (typeCalendar == C_DAILY)
	{
		Date date = enterDateWithoutTime("");
		calendar.getDailyCalendar(date);
	}
	else if (typeCalendar == C_WEEKLY)
	{
		Date date = enterDateWithoutTime("");
		calendar.headerMonth(date.getIntMonth());
		calendar.headerWdays();
		calendar.getWeeklyCalendar(date);
	}
	else if (typeCalendar == C_MONTHLY)
	{
		Date date = enterDateWithoutTime("");
		calendar.headerMonth(date.getIntMonth());
		calendar.headerWdays();
		calendar.getMonthlyCalendar(date);
	}
	else return;
}

CALENDAR_TYPE Interface::printPrintMenu()
{
	char typeCalendar;
	do
	{
		cout << endl << "Enter what type of calendar you want to print:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Daily" << endl
			<< "2. Weekly" << endl
			<< "3. Monthly" << endl;
		cin >> typeCalendar;
	} while (!checkCin(cin) || !checkCommand(typeCalendar, '3'));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return (CALENDAR_TYPE)(typeCalendar - '0');
}

void Interface::exportMenu(Calendar& calendar)
{
	string name = enterName(calendar);
	auto it = calendar.findEvent(name);
	stringstream fileName;
	ostringstream oss;
	fileName << name << ".txt";
	ofstream file(fileName.str());
	it->Print(oss);
	file << oss.str();
	file.close();
}

void Interface::importMenu(Calendar& calendar)
{
	string fileName = enterString("name of file for import events:");
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error opening file" << endl;
		return;
	}
	while (true)
	{
		string type;
		getline(file, type);
		if (type == birthdayType)
		{
			if (!importBirthday(calendar, file))
			{
				cout << "Error" << endl;
				break;
			}
		}
		else if (type == meetingType)
		{
			if (!importMeeting(calendar, file))
			{
				cout << "Error" << endl;
				break;
			}
		}
		else if (type == tripType)
		{
			if (!importTrip(calendar, file))
			{
				cout << "Error" << endl;
				break;
			}
		}
		else
		{
			if (!file.eof()) cout << "Error type of event" << endl;
			break;
		}
	}
	file.close();
}

bool Interface::importBirthday(Calendar& calendar, ifstream& file)
{
	string name, s_date;
	getline(file, name);
	getline(file, s_date);
	istringstream oss(s_date);
	struct tm t = {};
	oss >> get_time(&t, "%d.%m.%Y");
	if (oss.fail() || !ifTmValid(t)) return false;
	Date date(t);
	return calendar.addBirthday(name, date);
}

bool Interface::importMeeting(Calendar& calendar, ifstream& file)
{
	string name, s_date, s_endTime, place, repetition;
	getline(file, name);
	getline(file, s_date);
	istringstream oss(s_date);
	struct tm t = {};
	oss >> get_time(&t, "%d.%m.%Y %H:%M");
	if (oss.fail() || !ifTmValid(t)) return false;
	Date startDate(t);
	getline(file, s_endTime);
	istringstream end(s_endTime);
	struct tm endTm = t;
	end >> get_time(&endTm, "%H:%M");
	if (end.fail()) return false;
	struct tm startTm = startDate.getStructTm();
	if (difftime(timegm(&endTm), timegm(&startTm)) < secInTenMinutes) return false;
	Date endTime(endTm);
	getline(file, place);
	getline(file, repetition);
	return calendar.addMeeting(name, startDate, endTime, place, getRepetition(repetition));
}

bool Interface::importTrip(Calendar& calendar, ifstream& file)
{
	string name, s_date, dateEnd, country, repetition;
	getline(file, name);
	getline(file, s_date);
	istringstream oss(s_date);
	struct tm t = {};
	oss >> get_time(&t, "%d.%m.%Y %H:%M");
	if (oss.fail() || !ifTmValid(t)) return false;
	Date startDate(t);
	getline(file, dateEnd);
	istringstream end(dateEnd);
	struct tm endTm = {};
	end >> get_time(&endTm, "%d.%m.%Y %H:%M");
	if (end.fail() || !ifTmValid(endTm)) return false;
	struct tm startTm = startDate.getStructTm();
	if (difftime(timegm(&endTm), timegm(&startTm)) < secInDay) return false;
	Date endDate(endTm);
	getline(file, country);
	getline(file, repetition);
	return calendar.addTrip(name, startDate, endDate, country, getRepetition(repetition));
}

repetitionOfAnEvent Interface::getRepetition(const string& s)
{
	if (s == m_daily) return daily;
	else if (s == m_weekly) return weekly;
	else if (s == m_monthly) return monthly;
	else if (s == m_yearly) return yearly;
	else return oneTime;
}
