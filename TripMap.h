#ifndef TRIPMAP_H
#define TRIPMAP_H

#include <map>

#include "Trip.h"
/**
 * @class TripMap
 * change specific parameters of trip
 */
class TripMap {
public:
	/**
	* add trip
	* @param ptr shared_ptr trip
	*/
	void addTrip(const shared_ptr<Trip> ptr);

	/**
	 * find iterator trip
	 * @param tripName
	 * return iterator trip
	 */
	map<string, shared_ptr<Trip>>::iterator findIteratorTrip(const string& tripName);

	/**
	 * check if trip exist
	 * @param name
	 * return true in trip in map exist
	 */
	bool ifTripExist(const string& name);

    /**
     * overwrite event with new name if event exist
     * @param oldName
     * @param newName
     */
    void tryOverwriteName(const string& oldName, const string& newName);
    
	/**
	 * change country of trip
	 * @param tripName
	 * @param otherCountry
	 */
	void changeCountryOf(const string& tripName, const string& otherCountry);

	/**
	 * change end date of trip
	 * @param tripName
	 * @param newDate
	 * return false if changing was failed
	 */
	bool changeEndDateOf(const string& tripName, const Date& newDate);
private:
	map<string, shared_ptr<Trip>> tripByName;
};

#endif // TRIPMAP_H
