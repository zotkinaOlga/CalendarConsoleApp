#include "Interface.h"
#include "constants.h"

Interface::Interface(){}

void Interface::startAplication()
{
	Calendar calendar;
	while (true)
	{
		if (!processCommand(calendar))
		{
			return;
		}
	}
}

bool Interface::processCommand(Calendar& calendar)
{
	string type;
	MAIN_COMMAND command = mainMenu();
	if (command == COMMAND_ADD)
	{
		addMenu(calendar);
	}
	else if (command == COMMAND_DELETE)
	{
		deleteMenu(calendar);
	}
	else if (command == COMMAND_MOVE)
	{
		moveMenu(calendar);
	}
	else if (command == COMMAND_CHANGE)
	{
		string name = enterName(calendar);
		changeMenu(name, calendar);
	}
	else if (command == COMMAND_SEARCH)
	{
		searchMenu(calendar);
	}
	else if (command == COMMAND_PRINT)
	{
		printMenu(calendar);
	}
	else if (command == COMMAND_EXPORT)
	{
		exportMenu(calendar);
	}
	else if (command == COMMAND_IMPORT)
	{
		importMenu(calendar);
	}
	else
	{
		return false; //quit command
	}
	return true;
}

bool Interface::checkCommand(char command, char max) const
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

bool Interface::checkCin(istream& cin) const
{
	if (cin.fail()) 
	{
		cout << "Parse failed" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

EVENT_TYPE Interface::enterTypeEvent() const
{
	char type;
	while (true)
	{
		cout << endl << "Enter event`s type:" << endl
			<< "0. Return to main menu" << endl
			<< "1. Task" << endl
			<< "2. Meeting" << endl
			<< "3. Trip" << endl;
		cin >> type;
		if (checkCin(cin) && checkCommand(type, '3')) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			return (EVENT_TYPE)(type - '0');
		}
	}
}

string Interface::enterName(Calendar& calendar) const
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

Date Interface::enterDateWithTime(const string& typeDate) const
{
	tm t = {};
	do
	{
		cout << endl << "Enter " << typeDate << " (e.g. 20.02.2020 00:01):" << endl;
		t = {};
		cin >> get_time(&t, "%d.%m.%Y %R");
	} while (!checkCin(cin) || !ifTmValid(t));
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Date(t);
}

Date Interface::enterDateWithoutTime(const string& typeDate) const
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

bool Interface::ifTmValid(struct tm t) const
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

Date Interface::enterEndTime(struct tm t) const
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

string Interface::enterString(const string& forPrint) const
{
	string s;
	cout << endl << "Enter " << forPrint << endl;
	getline(cin, s);
	return s;
}

int Interface::enterAmountOfDay() const
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

repetitionOfAnEvent Interface::enterRepetition() const
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

MAIN_COMMAND Interface::mainMenu() const
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
		addTaskMenu(calendar);
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

string Interface::enterNameNewEvent(Calendar& calendar) const
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

void Interface::addTaskMenu(Calendar& calendar)
{
	string name = enterNameNewEvent(calendar);
	Date startDate(enterDateWithTime("start date"));
	Date endDate = enterDateWithTime("deadline");
	struct tm startTm = startDate.getStructTm();
	struct tm endTm = endDate.getStructTm();
	while (difftime(timegm(&endTm), timegm(&startTm)) < 1)
	{
		cout << "The deadline comes before the start" << endl;
		Date endDate = enterDateWithTime("deadline");
		endTm = endDate.getStructTm();
	}
	calendar.addTask(name, startDate, endDate, enterString("description:"), enterRepetition());
}

void Interface::addMeetingMenu(Calendar& calendar)
{
	string name = enterNameNewEvent(calendar);
	Date startDate(enterDateWithTime("start date"));
	Date endTime = enterEndTime(startDate.getStructTm());
	struct tm startTm = startDate.getStructTm();
	struct tm endTm = endTime.getStructTm();
	while (difftime(timegm(&endTm), timegm(&startTm)) < secInTenMinutes)
	{
		cout << "Meeting lasts less then 10 minutes" << endl;
		endTime = enterEndTime(startDate.getStructTm());
		endTm = endTime.getStructTm();
	}
	calendar.addMeeting(name, startDate, endTime, enterString("description:"), enterRepetition());
}

void Interface::addTripMenu(Calendar& calendar)
{
	string name = enterNameNewEvent(calendar);
	Date startDate(enterDateWithTime("start date"));
	Date endDate = enterDateWithTime("end date");
	struct tm startTm = startDate.getStructTm();
	struct tm endTm = endDate.getStructTm();
	while (difftime(timegm(&endTm), timegm(&startTm)) < secInDay)
	{
		cout << "Start date is more then end time or trip is less then one day" << endl;
		Date endDate = enterDateWithTime("date end");
		endTm = endDate.getStructTm();
	}
	auto timeDifference = difftime(timegm(&endTm), timegm(&startTm));
	repetitionOfAnEvent r = enterRepetition();
	while ((r == yearly && timeDifference > secInYear)
		|| (r == monthly && timeDifference > secInTheSmallestMonth)
		|| (r == weekly && timeDifference > secInWeek)
		|| (r == daily && timeDifference > secInDay))
	{
		cout << "Trip conflicts with dates by itself" << endl;
		r = enterRepetition();
	}
	calendar.addTrip(name, startDate, endDate, enterString("description:"), r);
}

void Interface::deleteMenu(Calendar& calendar)
{
	calendar.deleteEvent(enterName(calendar));
}

void Interface::moveMenu(Calendar& calendar)
{
	MOVE_COMMAND moveCom = printMoveMenu();
	ostringstream oss;
	string nameEvent = enterName(calendar);
	if (moveCom == MOVE_SD)
	{
		while (!calendar.moveEventForDays(nameEvent, enterAmountOfDay(), oss))
		{
			cout << oss.str();
		}
	}
	else if (moveCom == MOVE_FD)
	{
		calendar.moveEventToTheEarestFreeDate(nameEvent);
	}
	else
	{
		return;
	}
}

MOVE_COMMAND Interface::printMoveMenu() const
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

void Interface::changeMenu(const string& name, Calendar& calendar)
{
	CHANGE_COMMAND changeCom = printChangeMenu(calendar.findEvent(name));
	if (changeCom == CHANGE_NAME)
	{
		changeName(name, calendar);
	}
	else if (changeCom == CHANGE_START_DATE)
	{
		changeStartDate(name, calendar);
	}
	else if (changeCom == CHANGE_END)
	{
		changeEndDate(name, calendar);
	}
	else if (changeCom == CHANGE_REPETITION)
	{
		changeRepetition(name, calendar);
	}
	else if (changeCom == CHANGE_DESCRIPTION)
	{
		changeDescription(name, calendar);
	}
	else
	{
		return;
	}
}

CHANGE_COMMAND Interface::printChangeMenu(const shared_ptr<Event> ptr) const
{
	char changeCom;
	ostringstream oss;
	ptr->printAttribute(oss);
	do
	{
		cout << endl << "You can change:" << endl
			<< "0. Return to main menu" << endl
			<< oss.str();
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

void Interface::changeStartDate(const string& name, Calendar& calendar)
{
	ostringstream oss;
	Date dateS(enterDateWithTime("start date"));
	while (!calendar.changeDate(name, dateS, oss))
	{
		cout << oss.str();
		dateS = enterDateWithoutTime("start date");
	}
}

void Interface::changeEndDate(const string& name, Calendar& calendar)
{
	auto it = calendar.findEvent(name);
	string endAttribute = it->getEndDateAttribute();
	if (endAttribute == "End time")
	{
		changeEndTime(it, name, calendar);
	}
	else
	{
		changeEndWholeDate(name, endAttribute, calendar);
	}
}

void Interface::changeEndTime(shared_ptr<Event> itEvent, const string& name, Calendar& calendar)
{
	ostringstream oss;
	Date timeE = enterEndTime(itEvent->getDate().getStructTm());
	while (!calendar.changeEndDate(name, timeE, oss))
	{
		cout << oss.str();
		timeE = enterEndTime(itEvent->getDate().getStructTm());
	}
}

void Interface::changeEndWholeDate(const string& name, const string& endAttribute, Calendar& calendar)
{
	ostringstream oss;
	Date dateE = enterDateWithTime(endAttribute);
	while (!calendar.changeEndDate(name, dateE, oss))
	{
		cout << oss.str();
		dateE = enterDateWithTime(endAttribute);
	}
}

void Interface::changeRepetition(const string& name, Calendar& calendar)
{
	ostringstream oss;
	repetitionOfAnEvent r = enterRepetition();
	while (!calendar.changeRepetition(name, r, oss))
	{
		cout << oss.str();
		r = enterRepetition();
	}
}

void Interface::changeDescription(const string& name, Calendar& calendar)
{
	calendar.changeDescription(name, enterString("new description:"));
}

void Interface::searchMenu(Calendar& calendar) const
{
	SEARCH_COMMAND searchCom = printSearchMenu();
	if (searchCom == SEARCH_EVENT)
	{
		searchFreeDay(calendar);
	}
	else if (searchCom == SEARCH_FD)
	{
		searchFreeDay(calendar);
	}
	else
	{
		return;
	}
}

SEARCH_COMMAND Interface::printSearchMenu() const
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

void Interface::searchEvent(Calendar& calendar) const
{
	string name = enterName(calendar);
	ostringstream oss;
	cout << endl;
	calendar.findEvent(name)->print(oss);
	cout << oss.str();
}

void Interface::searchFreeDay(Calendar& calendar) const
{
	Date freeDate = calendar.searchTheEarestFreeDate(enterDateWithoutTime(""));
	ostringstream oss;
	freeDate.printDateWithoutTime(oss);
	cout << "The earlest free day is " << oss.str() << endl;
}

void Interface::printMenu(Calendar& calendar) const
{
	CALENDAR_TYPE typeCalendar = printPrintMenu();
	if (typeCalendar == C_DAILY)
	{
		printDailyCalendar(calendar);
	}
	else if (typeCalendar == C_WEEKLY)
	{
		printWeeklyCalendar(calendar);
	}
	else if (typeCalendar == C_MONTHLY)
	{
		printMonthlyCalendar(calendar);
	}
	else
	{
		return;
	}
}

CALENDAR_TYPE Interface::printPrintMenu() const
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

void Interface::printDailyCalendar(Calendar& calendar) const
{
	ostringstream oss;
	Date date = enterDateWithoutTime("");
	calendar.getDailyCalendar(date, oss);
	cout << oss.str();
}

void Interface::printWeeklyCalendar(Calendar& calendar) const
{
	ostringstream oss;
	Date date = enterDateWithoutTime("");
	calendar.headerMonth(date.getIntMonth(), oss);
	calendar.headerWdays(oss);
	calendar.getWeeklyCalendar(date, oss);
	cout << oss.str();
}

void Interface::printMonthlyCalendar(Calendar& calendar) const
{
	ostringstream oss;
	Date date = enterDateWithoutTime("");
	calendar.headerMonth(date.getIntMonth(), oss);
	calendar.headerWdays(oss);
	calendar.getMonthlyCalendar(date, oss);
	cout << oss.str();
}

void Interface::exportMenu(Calendar& calendar) const
{
	string name = enterName(calendar);
	auto it = calendar.findEvent(name);
	stringstream fileName;
	ostringstream oss;
	fileName << name << ".txt";
	ofstream file(fileName.str());
	it->print(oss);
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
			if (!importTask(calendar, file))
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
			if (!file.eof())
			{
				cout << "Error type of event" << endl;
			}
			break;
		}
	}
	file.close();
}

bool Interface::importTask(Calendar& calendar, ifstream& file)
{
	string name, s_date, deadline, description, repetition;
	getline(file, name);
	getline(file, s_date);
	istringstream oss(s_date);
	struct tm t = {};
	oss >> get_time(&t, "%d.%m.%Y %H:%M");
	if (oss.fail() || !ifTmValid(t)) return false;
	Date startDate(t);
	istringstream end(deadline);
	struct tm endTm = {};
	end >> get_time(&endTm, "%d.%m.%Y %H:%M");
	if (end.fail() || !ifTmValid(endTm)) return false;
	struct tm startTm = startDate.getStructTm();
	if (difftime(timegm(&endTm), timegm(&startTm)) < 1) return false;
	Date deadlineDate(endTm);
	getline(file, description);
	getline(file, repetition);
	return calendar.addTask(name, startDate, deadlineDate, description, getRepetition(repetition));
}

bool Interface::importMeeting(Calendar& calendar, ifstream& file)
{
	string name, s_date, s_endTime, description, repetition;
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
	getline(file, description);
	getline(file, repetition);
	return calendar.addMeeting(name, startDate, endTime, description, getRepetition(repetition));
}

bool Interface::importTrip(Calendar& calendar, ifstream& file)
{
	string name, s_date, dateEnd, description, repetition;
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
	getline(file, description);
	getline(file, repetition);
	return calendar.addTrip(name, startDate, endDate, description, getRepetition(repetition));
}

repetitionOfAnEvent Interface::getRepetition(const string& s) const
{
	if (s == m_daily)
	{
		return daily;
	}
	else if (s == m_weekly)
	{
		return weekly;
	}
	else if (s == m_monthly)
	{
		return monthly;
	}
	else if (s == m_yearly)
	{
		return yearly;
	}
	else
	{
		return oneTime;
	}
}