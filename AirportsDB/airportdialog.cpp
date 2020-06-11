#include "airportdialog.h"
#include "ui_airportdialog.h"

AirportDialog::AirportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AirportDialog)
{
    ui->setupUi(this);
}

AirportDialog::~AirportDialog()
{
    delete ui;
}

void AirportDialog::on_buttonBox_accepted()
{
    Airport airport;
    airport.mICAO = ui->txtICAO->text();
    airport.mName = ui->txtName->text();
    airport.mAltitude = ui->sbAltitude->value();
    airport.mFrequency = ui->sbFrequency->value();

    airport.mRwyIdent = ui->txtRwyIdent->text();
    airport.mRwyLength = ui->sbRwyLength->value();
    airport.mRwySurface = (Airport::eRwySurfaces) ui->cbRwySurface->currentIndex();

    Data::airportDb.addAirport(airport);
}
