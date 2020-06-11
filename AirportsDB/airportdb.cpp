#include "airportdb.h"

AirportDB::AirportDB(QObject *parent) : QObject(parent)
{

}

void AirportDB::addAirport(Airport airport) {
    mAirports.append(airport);
    emit OnDbUpdated();
}

QList<Airport> AirportDB::getAirports() {
    return mAirports;
}
