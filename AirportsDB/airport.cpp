#include "airport.h"

Airport::Airport()
{

}

Airport::Airport(QJsonObject jsonObject) :
    Airport()
{
    mAltitude = jsonObject["altitude"].toInt();
    mFrequency = jsonObject["frequency"].toDouble();
    mICAO = jsonObject["icao"].toString();
    mName = jsonObject["name"].toString();
    mRwyIdent = jsonObject["rwyIdent"].toString();
    mRwyLength = jsonObject["rwyLength"].toInt();
    mRwySurface = (Airport::eRwySurfaces) jsonObject["rwySurface"].toInt();
}

bool Airport::operator==(const Airport &other) {
    return mICAO == other.mICAO;
}

QJsonObject Airport::toJsonObject() {
    QJsonObject res;
    res["altitude"] = mAltitude;
    res["frequency"] = mFrequency;
    res["icao"] = mICAO;
    res["name"] = mName;
    res["rwyIdent"] = mRwyIdent;
    res["rwyLength"] = mRwyLength;
    res["rwySurface"] = mRwySurface;
    return res;
}
