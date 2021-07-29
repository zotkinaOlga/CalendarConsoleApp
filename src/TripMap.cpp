#include "TripMap.h"

void TripMap::addTrip(const shared_ptr<Trip> ptr) {
	tripByName.emplace(ptr->getName(), ptr);
}

map<string, shared_ptr<Trip>>::const_iterator TripMap::findIteratorTrip(const string& tripName) const
{
	return tripByName.find(tripName);
}

bool TripMap::ifTripExist(const string& name) const
{
	return findIteratorTrip(name) != tripByName.end();
}

void TripMap::tryOverwriteName(const string& oldName, const string& newName)
{
	auto it = findIteratorTrip(oldName);
	if (it == tripByName.end())
	{
		return;
	}
	tripByName.emplace(newName, it->second);
	tripByName.erase(oldName);
}

void TripMap::changeCountryOf(const string& tripName, const string& otherCountry)
{
	findIteratorTrip(tripName)->second->setCountry(otherCountry);
}

bool TripMap::changeEndDateOf(const string& tripName, const Date& newDate)
{
	return findIteratorTrip(tripName)->second->changeEndDate(newDate);
}
