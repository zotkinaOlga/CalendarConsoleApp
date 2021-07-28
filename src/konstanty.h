#include <string>
#include <vector>
using namespace std;

/**vectors of wdays and months*/
const vector<string> wday = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const vector<string> vectorMonth = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

/**constants represent colors*/
const string redColor = "\033[41m";
const string yellowColor = "\033[43m";
const string blueColor = "\033[46m";
const string clear = "\033[0m";

/**constants represent types events*/
const string birthdayType = "birthday";
const string meetingType = "meeting";
const string tripType = "trip";

/**constants represent repetition types*/
const string m_oneTime = "onetime";
const string m_daily = "daily"; //+ calendar type
const string m_weekly = "weekly";//+ calendar type
const string m_monthly = "monthly";//+ calendar type
const string m_yearly = "yearly";

/**constants represent change commands*/
const string s_name = "name";
const string s_startDate = "start date";
const string s_repetition = "repetition";
const string s_endTime = "end hours and minutes";
const string s_endDate = "end date";
const string s_place = "place";
const string s_country = "country";

/**constants represent amounts seconds in day, week atd*/
const  int secInDay = 86400;
const long int secInWeek = 604800;
const long int secInTwoWeeks = 604800 * 2;
const long long int secInTheSmallestMonth = 2419200;
const long long int secInYear = 31536000;
const int secInTenMinutes = 600;
