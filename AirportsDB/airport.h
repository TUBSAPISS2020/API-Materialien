#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>
#include <QJsonObject>

class Airport
{
public:
    enum eRwySurfaces {
        Asphalt,
        Beton,
        Gras,
        Unkown,
    };

public:
    Airport();
    Airport(QJsonObject jsonObject);

    bool operator==(const Airport& other);

    QJsonObject toJsonObject();

    QString mICAO;
    QString mName;
    int mAltitude;
    double mFrequency;

    QString mRwyIdent;
    int mRwyLength;
    eRwySurfaces mRwySurface;
};

#endif // AIRPORT_H
