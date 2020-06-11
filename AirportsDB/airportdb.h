#ifndef AIRPORTDB_H
#define AIRPORTDB_H

#include <QObject>
#include <QList>

#include "airport.h"

class AirportDB : public QObject
{
    Q_OBJECT
public:
    explicit AirportDB(QObject *parent = nullptr);

    void addAirport(Airport airport);
    QList<Airport> getAirports();

signals:
    void OnDbUpdated();

private:
    QList<Airport> mAirports;
};

#endif // AIRPORTDB_H
