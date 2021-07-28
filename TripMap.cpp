#include "TripMap.h"

void TripMap::addTrip(const shared_ptr<Trip> ptr) {
	tripByName.emplace(ptr->getName(), ptr);
}

map<string, shared_ptr<Trip>>::iterator TripMap::findIteratorTrip(const string& tripName)
{
	auto it = tripByName.find(tripName);
	return it;
}

bool TripMap::ifTripExist(const string& name)
{
	return findIteratorTrip(name) != tripByName.end();
}

void TripMap::tryOverwriteName(const string& oldName, const string& newName)
{
    auto it = findIteratorTrip(oldName);
    if(it == tripByName.end()) return;
    tripByName.emplace(newName,it->second);
    tripByName.erase(oldName);
}

void TripMap::changeCountryOf(const string& tripName, const string& otherCountry)
{
	auto it = findIteratorTrip(tripName);
	it->second->setCountry(otherCountry);
}

bool TripMap::changeEndDateOf(const string& tripName, const Date& newDate)
{
	auto it = findIteratorTrip(tripName);
	return it->second->changeEndDate(newDate);
}
