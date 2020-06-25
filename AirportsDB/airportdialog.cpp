#include "airportdialog.h"
#include "ui_airportdialog.h"

AirportDialog::AirportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AirportDialog)
{
    ui->setupUi(this);
}

AirportDialog::AirportDialog(QWidget *parent, eModes mode, const Airport* airport) :
    AirportDialog(parent)
{
    if (airport != nullptr) {
        mOriginalAirport = airport;
        ui->txtICAO->setText(airport->mICAO);
        ui->txtName->setText(airport->mName);
        ui->sbAltitude->setValue(airport->mAltitude);
        ui->sbFrequency->setValue(airport->mFrequency);

        ui->txtRwyIdent->setText(airport->mRwyIdent);
        ui->sbRwyLength->setValue(airport->mRwyLength);
        ui->cbRwySurface->setCurrentIndex(airport->mRwySurface);
    }

    mMode = mode;
    switch (mode) {
    case eModes::AddAirport:
    case eModes::EditAirport:
        ui->buttonBox->button(QDialogButtonBox::Save)->setVisible(true);
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setVisible(true);
        ui->buttonBox->button(QDialogButtonBox::Close)->setVisible(false);
        break;
    case eModes::DetailView:
        ui->buttonBox->button(QDialogButtonBox::Save)->setVisible(false);
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setVisible(false);
        ui->buttonBox->button(QDialogButtonBox::Close)->setVisible(true);

        ui->txtICAO->setEnabled(false);
        ui->txtName->setEnabled(false);
        ui->sbAltitude->setEnabled(false);
        ui->sbFrequency->setEnabled(false);
        ui->txtRwyIdent->setEnabled(false);
        ui->sbRwyLength->setEnabled(false);
        ui->cbRwySurface->setEnabled(false);
        break;
    }
}

AirportDialog::~AirportDialog()
{
    delete ui;
}

void AirportDialog::on_buttonBox_accepted()
{
    Airport airport;
    airport.mICAO = ui->txtICAO->text().trimmed();
    airport.mName = ui->txtName->text().trimmed();
    airport.mAltitude = ui->sbAltitude->value();
    airport.mFrequency = ui->sbFrequency->value();

    airport.mRwyIdent = ui->txtRwyIdent->text().trimmed();
    airport.mRwyLength = ui->sbRwyLength->value();
    airport.mRwySurface = (Airport::eRwySurfaces) ui->cbRwySurface->currentIndex();

    if (airport.mICAO == "" && airport.mName == "" && airport.mRwyIdent == "") {
        QMessageBox msgBox;
        msgBox.setText("Ungültige Daten eingegeben. Bitte ICAO, Name und RwyIdent überprüfen.");
        msgBox.exec();
        return;
    }

    if (mMode == eModes::AddAirport) {
        if (Data::airportDb.addAirport(airport)) {
            this->close();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Flugplatz mit angegebenem ICAO Code schon vorhanden.");
            msgBox.exec();
        }
    } else {
        if (Data::airportDb.editAirport(*mOriginalAirport, airport)) {
            this->close();
        }
    }
}

void AirportDialog::on_buttonBox_rejected()
{
    this->close();
}
