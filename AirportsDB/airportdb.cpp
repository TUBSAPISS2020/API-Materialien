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

bool AirportDB::deleteAirport(Airport airport) {
    int index = mAirports.indexOf(airport);
    if (index >= 0) {
        mAirports.removeAt(index);
        saveDb();
        emit OnDbUpdated();
        return true;
    } else {
        return false;
    }
}

bool AirportDB::editAirport(Airport airportOld, Airport airportNew) {
    int index = mAirports.indexOf(airportOld);
    if (index >= 0) {
        mAirports.replace(index, airportNew);
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

const Airport* AirportDB::getAirport(QString sICAO) {
    int index = -1;

    for (int i = 0; i < mAirports.size(); i++) {
        if (mAirports.at(i).mICAO == sICAO) {
            index = i;
            break;
        }
    }

    if (index < 0) {
        return nullptr;
    } else {
        return &(mAirports.at(index));
    }
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
