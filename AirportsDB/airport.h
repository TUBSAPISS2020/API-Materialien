#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

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

    QString mICAO;
    QString mName;
    int mAltitude;
    double mFrequency;

    QString mRwyIdent;
    int mRwyLength;
    eRwySurfaces mRwySurface;
};

#endif // AIRPORT_H
