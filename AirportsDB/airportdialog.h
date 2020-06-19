#ifndef AIRPORTDIALOG_H
#define AIRPORTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>

#include "data.h"

namespace Ui {
class AirportDialog;
}

class AirportDialog : public QDialog
{
    Q_OBJECT

public:
    enum eModes {
        AddAirport,
        DetailView,
        EditAirport
    };

public:
    explicit AirportDialog(QWidget *parent = nullptr);
    AirportDialog(QWidget *parent, eModes mode, Airport* airport);
    ~AirportDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AirportDialog *ui;
};

#endif // AIRPORTDIALOG_H
