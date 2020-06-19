#include "airportdb.h"

AirportDB::AirportDB(QObject *parent) : QObject(parent)
{
    loadDb();
}

bool AirportDB::addAirport(Airport airport) {
    if (mAirports.indexOf(airport) < 0) {
        mAirports.append(airport);
        saveDb();
        emit OnDbUpdated();
        return true;
    } else {
        return false;
    }
}

QList<Airport> AirportDB::getAirports() {
    return mAirports;
}

void AirportDB::loadDb() {
    QFile file("airports.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();

        QJsonObject jsonObject = jsonDoc.object();
        QJsonArray airportsArray = jsonDoc["airports"].toArray();

        mAirports.clear();
        for (int i = 0; i < airportsArray.size(); i++) {
            QJsonObject airportObject = airportsArray[i].toObject();
            mAirports.append(Airport(airportObject));
        }
    }
}

void AirportDB::saveDb() {
    QJsonArray airportsArray;
    foreach (Airport airport, mAirports) {
        airportsArray.append(airport.toJsonObject());
    }

    QJsonObject jsonObject;
    jsonObject["airports"] = airportsArray;

    QJsonDocument jsonDoc(jsonObject);

    QFile file("airports.json");
    file.open(QIODevice::WriteOnly);
    file.write(jsonDoc.toJson());
    file.close();
}
